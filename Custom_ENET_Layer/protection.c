#include "../Custom_ENET_Layer/protection.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_enet.h"
#include "stdlib.h"
#include "fsl_common.h"
#include "fsl_crc.h"
#include "aes.h"
#include "../Custom_ENET_Layer/ENET_Drivers/CMSIS_driver/Driver_ETH_MAC.h"
#include "../Custom_ENET_Layer/ENET_Drivers/fsl_enet_cmsis.h"
#include "../Custom_ENET_Layer/ENET_Drivers/fsl_enet_phy_cmsis.h"
#include "../Custom_ENET_Layer/ENET_Drivers/fsl_sysmpu.h"
#include "../Custom_ENET_Layer/ENET_Drivers/mdio/fsl_enet_mdio.h"
#include "../Custom_ENET_Layer/ENET_Drivers/phy/fsl_phy.h"
#include "../Custom_ENET_Layer/ENET_Drivers/phy/fsl_phyksz8081.h"
#include "../Custom_ENET_Layer/ENET_Drivers/RTE_Device.h"

uint8_t g_frame[ENET_DATA_LENGTH + 14];
volatile uint32_t g_testTxNum  = 0;
uint8_t source_macAddr[6]           = SOURCE_MAC_ADDRESS;
uint8_t destination_macAddr[6]      = DESTINATION_MAC_ADDRESS;
volatile uint32_t g_rxIndex    = 0;
volatile uint32_t g_rxCheckIdx = 0;
volatile uint32_t g_txCheckIdx = 0;
uint8_t flagReception = 0;

receive_cb_function *User_ENET_Receive_Cb;

// CRC32 variables
CRC_Type *base = CRC0;
uint32_t checksum32;

// AES128 variables
uint8_t key[] = AES128_KEY;
uint8_t iv[] = AES128_IV;
struct AES_ctx ctx;


mdio_handle_t mdioHandle = {.ops = &enet_ops};
phy_handle_t phyHandle   = {.phyAddr = RTE_ENET_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &phyksz8081_ops};


uint32_t ENET0_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_CoreSysClk);
}


uint32_t Compute_Padding(uint8_t *data, uint32_t len)
{
	uint32_t len_wo_padding = len;

	// Eliminate padding only when the size is the minimum
	if(len == 60){
		for(uint8_t i=len-1; i>0;i--)
		{
			if(data[i]!=0)
			{
				break;
			}
			len_wo_padding--;
		}
	}

	return len_wo_padding;
}


static void aes128_init()
{
	// Init_AES context
	AES_init_ctx_iv(&ctx, key, iv);

}


static uint32_t aes128_encrypt(uint8_t *data, uint32_t len, uint8_t *output_array)
{
	uint32_t padded_len = len + (16 - (len%16));

	aes128_init();

	// Copy data to final array
	memcpy(output_array, data, len);

	// Encrypt the data
	AES_CBC_encrypt_buffer(&ctx, output_array, padded_len);

	return padded_len;
}

static void InitCrc32(CRC_Type *base, uint32_t seed) //Pointerto_CRC_Type
{
    crc_config_t config; //SaveParameters

    config.polynomial         = 0x04C11DB7U; //PolynomialStandar
    config.seed               = seed;
    config.reflectIn          = true;
    config.reflectOut         = true;
    config.complementChecksum = true;
    config.crcBits            = kCrcBits32;
    config.crcResult          = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

uint32_t ComputeCRC32(uint8_t *testData, uint32_t size)
{
	InitCrc32(base, 0xFFFFFFFFU);
	CRC_WriteData(base, (uint8_t *)&testData[0], size);
	return CRC_Get32bitResult(base);
}


uint8_t verifyDataCRC(uint8_t *data, uint32_t size)
{
	uint8_t status = CRC_NOT_OK;
	uint32_t dataCRC32 = 0;
	uint32_t computedCRC32 = 0;

	uint32_t length = data[12] << 8 | data[13];

	// Extract data CRC32
	dataCRC32 |= data[length + 14 -4] << 24;
	dataCRC32 |= data[length + 14 -3] << 16;
	dataCRC32 |= data[length + 14 -2] << 8;
	dataCRC32 |= data[length + 14 -1];

	// Compute CRC for data. Subtract 14 for the header and 4 for the CRC32
	computedCRC32 = ComputeCRC32(&data[14], length - 4);

	// Compare the CRC32s
	if(computedCRC32 == dataCRC32)
	{
		status = CRC_OK;
	}

	return status;
}


static uint32_t ENET_BuildBroadCastFrame(uint8_t *data, uint32_t len)
{
	uint32_t data_len = 0;

	// Clean the output frame
	memset(&g_frame[0], 0, sizeof(g_frame));

    // Copy destination MAC address
    memcpy(&g_frame[0], &destination_macAddr[0], 6U);

    // Copy source MAC address
    memcpy(&g_frame[6], &source_macAddr[0], 6U);

    // Encode the message using AES128
    data_len = aes128_encrypt(data, len, &g_frame[14]);

	// Disable interrupts in the CRC32 computation to prevent
	//  data corruption if a frame is received in the process
	__disable_irq();

	// Add CRC32
	uint32_t dataCRC32 = ComputeCRC32(&g_frame[14], data_len);

	// Enable all interrupts again
	__enable_irq();

    // Copy CRC frame to output array
    g_frame[data_len + 14] = (dataCRC32 >> 24) & 0xFFU;
    g_frame[data_len + 15] = (dataCRC32 >> 16) & 0xFFU;
    g_frame[data_len + 16] = (dataCRC32 >> 8) & 0xFFU;
    g_frame[data_len + 17] = dataCRC32 & 0xFFU;

    // Add byte length of CRC32 to the data length
    data_len += 4;

    // Set data length in EtherType field
    g_frame[12] = (data_len >> 8) & 0xFFU;
    g_frame[13] = data_len & 0xFFU;


    return (data_len + 14);
}


void Custom_ENET_Layer_Receive_Cb(uint32_t event)
{
	uint32_t size;
	uint32_t len;
	uint32_t data_len;
	uint8_t *data;
	uint8_t prueba[400];
	//uint32_t len_wo_padding;

	if (event == ARM_ETH_MAC_EVENT_RX_FRAME)
	{

		/* Get the Frame size */
		size = EXAMPLE_ENET.GetRxFrameSize();
		/* Call ENET_ReadFrame when there is a received frame. */
		if (size != 0)
		{
			/* Received valid frame. Deliver the rx buffer with the size equal to length. */
			data = (uint8_t *)malloc(size);
			if (data)
			{
				len = EXAMPLE_ENET.ReadFrame(data, size);
				if (size == len)
				{

					// Compute length without padding
					//len_wo_padding = Compute_Padding(data, len);

					if (data[0] != 0xFF) {
						// Verify the data with CRC32
						if( verifyDataCRC(data, size) == CRC_OK)
						{
							// Subtract the MAC header and the CRC32 size
							data_len = (data[12] << 8 | data[13]) - 4;

							// Restart the_ecryption_module
							aes128_init();

							memset(prueba, 0, sizeof(prueba));
							memcpy(&prueba[0], &data[14], data_len);

							// Decode the message
							AES_CBC_decrypt_buffer(&ctx, prueba, data_len);

							PRINTF("Decrypted: %s\r\n", prueba);

							flagReception = 1;

							// Extract the decrypted data len from the EtherType field
							//data_len = (data[12] << 8) + data[13];

							// Call the user receive callback
							//User_ENET_Receive_Cb(&data[14], data_len);
						}
						else
						{
							PRINTF("If it gets here, CRC32 is incorrect!\r\n");
						}
					}
				}
				free(data);
			}
		}
	}


}


void Custom_ENET_Layer_Init(receive_cb_function cb_func)
{
	// Save user's receive callback
	if(cb_func != NULL)
	{
		User_ENET_Receive_Cb = cb_func;
	}

    ARM_ETH_LINK_INFO linkInfo;

    //Disable_SYSMPU
    SYSMPU_Enable(SYSMPU, false);

    mdioHandle.resource.base        = ENET;
    mdioHandle.resource.csrClock_Hz = ENET0_GetFreq();

    PRINTF("\r\nENET example start.\r\n");

    //InitENETModule
    EXAMPLE_ENET.Initialize(Custom_ENET_Layer_Receive_Cb);
    EXAMPLE_ENET.PowerControl(ARM_POWER_FULL);
    EXAMPLE_ENET.SetMacAddress((ARM_ETH_MAC_ADDR *)source_macAddr);

    PRINTF("Wait for PHY init...\r\n");
    while (EXAMPLE_ENET_PHY.PowerControl(ARM_POWER_FULL) != ARM_DRIVER_OK)
    {
        PRINTF("PHY Auto-negotiation failed, please check the cable connection and link partner setting.\r\n");
    }

    EXAMPLE_ENET.Control(ARM_ETH_MAC_CONTROL_RX, 1);
    EXAMPLE_ENET.Control(ARM_ETH_MAC_CONTROL_TX, 1);
    PRINTF("Wait for PHY link up...\r\n");
    do
    {
        if (EXAMPLE_ENET_PHY.GetLinkState() == ARM_ETH_LINK_UP)
        {
            linkInfo = EXAMPLE_ENET_PHY.GetLinkInfo();
            EXAMPLE_ENET.Control(ARM_ETH_MAC_CONFIGURE, linkInfo.speed << ARM_ETH_MAC_SPEED_Pos |
                                                            linkInfo.duplex << ARM_ETH_MAC_DUPLEX_Pos |
                                                            ARM_ETH_MAC_ADDRESS_BROADCAST);
            break;
        }
    } while (1);

#if defined(PHY_STABILITY_DELAY_US) && PHY_STABILITY_DELAY_US
    /* Wait a moment for PHY status to be stable. */
    SDK_DelayAtLeastUs(PHY_STABILITY_DELAY_US, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
#endif


    // Initialize the CRC module
    InitCrc32(base, 0xFFFFFFFFU);

    // Init the AES128 module
    aes128_init();

}


void Custom_ENET_Layer_Transmit(uint8_t *data, uint32_t len)
{
	uint32_t BroadCastFrame_Size=0;
	flagReception = 0;

	SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); //DelayForSeeTheMessages

	// Assembly output frame
	BroadCastFrame_Size = ENET_BuildBroadCastFrame(data, len);

	/* Send a multicast frame when the PHY is link up. */
	if (EXAMPLE_ENET.SendFrame(&g_frame[0], BroadCastFrame_Size > 60 ? BroadCastFrame_Size : 60, ARM_ETH_MAC_TX_FRAME_EVENT) == ARM_DRIVER_OK)
	{
		while(flagReception == 0) {
			SDK_DelayAtLeastUs(500, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
		}
	}
	else
	{
		PRINTF(" \r\nTransmit frame failed!\r\n");
	}

}
