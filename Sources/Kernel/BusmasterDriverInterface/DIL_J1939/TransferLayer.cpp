// clang-format on
/******************************************************************************
  Project       :  Auto-SAT_Tools
  FileName      :  TransferLayer.cpp
  Description   :
  $Log:   X:/Archive/Sources/DIL_J1939/TransferLayer.cpv  $

      Rev 1.3   07 Jun 2011 11:11:18   CANMNTTM


      Rev 1.2   15 Apr 2011 18:48:38   CANMNTTM
   Added RBEI Copyright information.

      Rev 1.1   13 Dec 2010 16:37:06   CANMNTTM
   Nodes are made independent of channel.
   Now nodes can send message in any channel.

      Rev 1.0   06 Dec 2010 18:47:22   rac2kor


  Author(s)     :  Pradeep Kadoor
  Date Created  :  23/11/2010
  Modified By   :
  Copyright (c) 2011, Robert Bosch Engineering and Business Solutions.  All
rights reserved.
******************************************************************************/

#include "DIL_J1939_stdafx.h"
// clang-format on

#include "BaseDIL_CAN.h"
#include "J1939_UtilityFuncs.h"
#include "NetworkMgmt.h"
#include "NodeConManager.h"
#include "TransferLayer.h"

//  Forward declarations
class CConnectionDet;

const int nSIZE_OF_BYTE = sizeof(BYTE);
/**************************************************************
 ************************************************************** */
CTransferLayer::CTransferLayer() { m_pIDIL_CAN = nullptr; }

/**************************************************************
 ************************************************************** */
CTransferLayer::~CTransferLayer(void) {}

/**************************************************************
 ************************************************************** */
CTransferLayer& CTransferLayer::ouGetTransLayerObj() {
  static CTransferLayer ouTransferLayerObj;
  return ouTransferLayerObj;
}

/**************************************************************
 ************************************************************** */
LONG CTransferLayer::lTConnectReq(short /*sConNumber*/, char /*cBlockSize*/,
                                  eCON_MODE /*eSMmode*/) {
  return 0L;
}

/**************************************************************
 ************************************************************** */
void CTransferLayer::vTConnectCon(short /*sConNumber*/,
                                  eCON_STATUS /*ConStatus*/,
                                  char /*cBlockSize*/,
                                  eCON_MODE /*eServiceMode*/) {}

/**************************************************************
 ************************************************************** */
void CTransferLayer::vTConnectInd(short /*sConNumber*/, char /*cBlockSize*/,
                                  BOOL /*bIsSMEnhance*/) {}

/**************************************************************
 ************************************************************** */
void CTransferLayer::vTDisconnectInd(short /*sConNumber*/,
                                     eREASON /*eReason*/) {}

/**************************************************************
 ************************************************************** */
void CTransferLayer::vTLongDataCon(short /*sConNumber*/,
                                   char /*cTransferResult*/) {}

/**************************************************************
 ************************************************************** */
void CTransferLayer::vTBroadDataInd(short /*sBroadcastCANId*/,
                                    short /*sDataLength*/, BYTE* /*pbData*/) {}

/**************************************************************
 ************************************************************** */
void CTransferLayer::vTConTestCon(short /*sConNumber*/,
                                  char /*cConnectionStatus*/,
                                  char /*cBlockSize*/, char /*cServiceMode*/) {
  // Confirm the connection request
}

void CTransferLayer::vTransmitCANMsg(DWORD dwClientID, UINT unID,
                                     UCHAR ucDataLen, BYTE* pData,
                                     UINT unChannel) {
  STCAN_MSG sMsgCAN = {'\0'};

  sMsgCAN.m_unMsgID = unID;
  sMsgCAN.m_ucDataLen = ucDataLen;
  memcpy(sMsgCAN.m_ucData, pData, ucDataLen);
  sMsgCAN.m_ucChannel = (UCHAR)unChannel;
  sMsgCAN.m_ucRTR = 0;
  sMsgCAN.m_ucEXTENDED = 1;
  m_pIDIL_CAN->DILC_SendMsg(dwClientID, sMsgCAN);
}

void CTransferLayer::vSetIDIL_CAN(CBaseDIL_CAN* pIDIL_CAN) {
  m_pIDIL_CAN = pIDIL_CAN;
}