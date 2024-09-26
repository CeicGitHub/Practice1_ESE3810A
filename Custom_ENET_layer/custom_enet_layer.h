

#ifndef CUSTOM_ENET_LAYER_H_
#define CUSTOM_ENET_LAYER_H_

#include "board.h"

#include "../Custom_ENET_layer/custom_enet_layer_config.h"


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






#endif /* CUSTOM_ENET_LAYER_H_ */
