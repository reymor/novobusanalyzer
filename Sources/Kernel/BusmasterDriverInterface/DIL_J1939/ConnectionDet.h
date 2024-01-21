// clang-format off
/******************************************************************************
  Project       :  Frame_McNet
  FileName      :  ConnectionDet.h
  Description   :  Keep details of each connenction
  $Log:   X:/Archive/Sources/DIL_J1939/ConnectionDet.h_v  $
 *
 *    Rev 1.3   15 Apr 2011 18:48:34   CANMNTTM
 * Added RBEI Copyright information.
 *
 *    Rev 1.2   29 Dec 2010 19:32:38   CANMNTTM
 * Connection mode for both transmission and reception added.
 *
 *    Rev 1.1   23 Dec 2010 16:52:20   CANMNTTM
 * Macro MAX_MSG_LEN_J1939
 *  instead of MAX_DATA_LEN_J1939 wherever applicable.
 *
 *    Rev 1.0   06 Dec 2010 18:47:20   rac2kor
 *
 *
 *    Rev 1.3   12 Jan 2010 14:22:46   mcnetpl
 * Bugfixing
 *
 *    Rev 1.2   04 Jan 2010 14:46:12   mcnetpl
 *
 *
 *    Rev 1.1   07 Dec 2009 12:58:04   mcnetpl
 * Bugfix
 *
 *    Rev 1.0   02 Dec 2009 17:53:04   mcnetpl
 * Initial version

  Author(s)     :  Anish Kumar
  Date Created  :  15/09/2009
  Modified By   :
  Copyright (c) 2011, Robert Bosch Engineering and Business Solutions.  All rights reserved.
******************************************************************************/
// clang-format on

#ifndef KERNEL_BUSMASTERDRIVERINTERFACE_DIL_J1939_CONNECTIONDET_H_
#define KERNEL_BUSMASTERDRIVERINTERFACE_DIL_J1939_CONNECTIONDET_H_

#include "J1939DriverDefines.h"
#include "J1939_UtilityFuncs.h"

class CConnectionDet {
 private:
  eCON_STATUS m_eConStatus;

 public:
  // Only for long message
  BYTE m_byCurrPacket;
  BYTE m_byMaxPacketWOC2S;
  BYTE m_byTxAckSeqNo;
  BYTE m_byRxSeqNo;

  BYTE m_RxLongData[MAX_DATA_LEN_J1939];  // RX long data storage
  BYTE m_BCRXLongData[MAX_DATA_LEN_J1939];
  BYTE m_TxLongData[MAX_DATA_LEN_J1939];  // TX long data storage
  UINT m_unTXLongDataLen;
  UINT m_unRXLongDataLen;
  UINT m_unRxTotalPackets;
  UINT m_unRxLastFrameLen;
  UINT64 m_unTimeStamp;
  HANDLE m_hDataAckWait;
  HANDLE m_hDataRxWait;
  HANDLE m_hClear2SendWait;
  HANDLE m_hBCDataRXWait;
  // Dummy handle just to wait till the delay expires instead of implementing
  // timer function
  HANDLE m_hDataDelayWait;
  UINT32 m_unPGN;

  // All broadcast
  UINT64 m_BCTimeStamp;
  BYTE m_BCRxSeqVar;
  BYTE m_BCTotalPackets;
  eCON_MODE m_eRxConMode;
  eCON_MODE m_eTxConMode;
  UINT32 m_BCPGN;
  UINT m_BCRXLongDataLen;
  UINT m_BCLastFrameLen;

 public:
  BYTE m_bySrcAddress;   // Tx msg id for this connection
  BYTE m_byDestAddress;  // Rx msg id for this connection

  BYTE m_byResult;
  UINT m_unNextPacket;

 public:
  CConnectionDet(BYTE bySrcAddress, BYTE byDestAddress);
  ~CConnectionDet();
  BOOL bIsMsgRxForThisConnection(UINT32 unExtId);
  void vInitializeMemberVar();
  void vSetConStatus(eCON_STATUS eConStatus);
  eCON_STATUS eGetConStatus(void);
};

#endif  // KERNEL_BUSMASTERDRIVERINTERFACE_DIL_J1939_CONNECTIONDET_H_