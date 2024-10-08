//CesarEduardoIndaCeniceros_752964
//This file represent the user layer for send messages

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include <string.h>  // ForUse_strlen

#include "../Custom_ENET_Layer/protection.h"

// FunctionCallback_Data_BufferReceiveTerminal
void application_callback(uint8_t *data, uint32_t len)
{
    PRINTF((char*)data);
    PRINTF("\n\r");
}

int main(void) {

    // HAL_Layer
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    //EthernetLayerInit
    Custom_ENET_Layer_Init(application_callback);

    //MessagesToTransmit
    const char *messages[] = {
        "CesarEduardoIndaCeniceros752964",
        "Iteso Universidad Jesuita De Guadalajara",
        "Pikachu_Yo_Te_Elijo",
        "Me-convertire-En-Un-Maestro-Pokemon",
        "Confiare_En_El_Corazon_De_Las_Cartas",
        "Mis_Amigos_Nunca_Seran_Una_Perdida_De_Tiempo",
        "GOKU ERES EL NUMERO 1",
        "COMIENZA A TEMBLAR FREEZER POR QUE CONOCERAS AL SUPER SAIYATIN QUE TANTO HAS TEMIDO"
    };


    for (int i = 0; i < sizeof(messages)/sizeof(messages[0]); i++) {

        Custom_ENET_Layer_Transmit((uint8_t*)messages[i], strlen(messages[i]) + 1); // +1 to_include_null_factor
    }


    while (true) {

    };

    return 0;
}

