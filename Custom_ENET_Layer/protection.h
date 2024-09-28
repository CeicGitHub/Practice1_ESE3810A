//CesarEduardoIndaCeniceros_752964

#ifndef PROTECTION_H_
#define PROTECTION_H_

#include "board.h"	//Clocks,GPIO,Ports

#include "../Custom_ENET_Layer/protection_cfg.h" //Drivers,MAC,AES128KEY

typedef void receive_cb_function(uint8_t *data, uint32_t len);

/* CRC macro definitions */
#define CRC_OK				1
#define CRC_NOT_OK			0

#define STATUS_OK				1
#define STATUS_NOT_OK			0


/* Custom layer initialization function */
void Custom_ENET_Layer_Init(receive_cb_function cb_func);
/* Custom layer transmit function */
void Custom_ENET_Layer_Transmit(uint8_t *data, uint32_t len);


#endif /* PROTECTION_H_ */
