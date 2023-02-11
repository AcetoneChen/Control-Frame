//
// Created by 25396 on 2023/2/11.
//

#include "CommuType.h"

/*CAN类------------------------------------------------------------------*/
/**
 * @brief CAN通信的初始化，主要是CAN通信的相关配置
 */
void CAN::CANInit() {
    HAL_CAN_Start(&hcan1);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);

    CAN_FilterTypeDef canFilterTypeDef;

    canFilterTypeDef.FilterMode = CAN_FILTERMODE_IDMASK;
    canFilterTypeDef.FilterScale = CAN_FILTERSCALE_32BIT;
    canFilterTypeDef.FilterIdHigh = 0x0000;
    canFilterTypeDef.FilterIdLow = 0x0000;
    canFilterTypeDef.FilterMaskIdHigh = 0x0000;
    canFilterTypeDef.FilterMaskIdLow = 0x0000;
    canFilterTypeDef.FilterFIFOAssignment = CAN_RX_FIFO0;
    canFilterTypeDef.FilterActivation = ENABLE;
    canFilterTypeDef.FilterBank = 0;
    canFilterTypeDef.SlaveStartFilterBank = 0;

    HAL_CAN_ConfigFilter(&hcan1, &canFilterTypeDef);
    HAL_CAN_ConfigFilter(&hcan2, &canFilterTypeDef);
}

/**
 * @brief CAN类的构造函数
 */
CAN::CAN() {
    can_ID = 0x280;
    ctrlType = SPEED_Single;
}

CAN::CAN(COMMU_INIT_t *_init) {
    can_ID = _init->_id;
    ctrlType = _init->ctrlType;

}

/**
 * @brief CAN类的析构函数
 */
CAN::~CAN() = default;

/**
 * @brief can消息包发送任务
 * @callergraph void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 *              in Device.cpp
 */
void CAN::CANPackageSend() {
    CAN_TxHeaderTypeDef txHeaderTypeDef;
    uint32_t box;

    txHeaderTypeDef.StdId = 0x280;
    txHeaderTypeDef.DLC = 0x08;
    txHeaderTypeDef.IDE = CAN_ID_STD;
    txHeaderTypeDef.RTR = CAN_RTR_DATA;
    txHeaderTypeDef.TransmitGlobalTime = DISABLE;

    HAL_CAN_AddTxMessage(&hcan1, &txHeaderTypeDef, canmessage, &box);
}

/**
 * @brief can中断处理函数，用于电调返回数据的接受
 * @param hcan
 */
void CAN::Rx_Handle(CAN_HandleTypeDef *hcan) {
    uint8_t canBuf[8];
    CAN_RxHeaderTypeDef rx_header;
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, canBuf);
    if (hcan == &hcan1) {
        memcpy(dict[rx_header.StdId], canBuf, sizeof(canBuf));
    }

}

void CAN::ID_Bind_Rx(uint8_t *RxMessage) {
    dict.insert(std::pair<uint16_t, uint8_t *>(can_ID, RxMessage));
}

void CAN::FOURID_Bind_Rx(uint16_t *canIDs, uint8_t (*RxMessage)[8]) {

    dict.insert(std::pair<uint16_t, uint8_t *>(canIDs[0], RxMessage[0]));
    dict.insert(std::pair<uint16_t, uint8_t *>(canIDs[1], RxMessage[1]));
    dict.insert(std::pair<uint16_t, uint8_t *>(canIDs[2], RxMessage[2]));
    dict.insert(std::pair<uint16_t, uint8_t *>(canIDs[3], RxMessage[3]));
}


/*RS485类------------------------------------------------------------------*/
/**
 * @brief RS485类的构造函数
 */
RS485::RS485(uint16_t _id) {
    rs485_ID = _id;
    ctrlType = DIRECT;
}

/**
 * @brief RS485类的析构函数
 */
RS485::~RS485() = default;

/**
 * @brief RS485消息包发送任务
 */
void RS485::RS485PackageSend() {
    static uint8_t rsmotorIndex = 0;
    rsmotorIndex %= 4;
    HAL_UART_Transmit_IT(&huart1, rsmessage[rsmotorIndex], 11);

    rsmotorIndex++;
}


