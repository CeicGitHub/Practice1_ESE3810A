/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2021 NXP. Not a Contribution.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _FSL_ENET_CMSIS_H_
#define _FSL_ENET_CMSIS_H_

#include "fsl_common.h"
#include "fsl_enet.h"

#include "../../Custom_ENET_Layer/ENET_Drivers/CMSIS_driver/Driver_ETH.h"
#include "../../Custom_ENET_Layer/ENET_Drivers/CMSIS_driver/Driver_ETH_MAC.h"
#include "../../Custom_ENET_Layer/ENET_Drivers/RTE_Device.h"

/* ENET Driver state flags */
#define ENET_FLAG_UNINIT     (0U)
#define ENET_FLAG_INIT       (1U << 0)
#define ENET_FLAG_POWER      (1U << 1)
#define ETH_MAC_EVENT_OTHERS (ARM_ETH_MAC_EVENT_TIMER_ALARM + 1U)

extern ARM_DRIVER_ETH_MAC Driver_ETH_MAC0;

extern uint32_t ENET0_GetFreq(void);

#endif
