/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// clang-format off
/**
 * \file      MsgBufLINVFSE.h
 * \brief     Defines and implements the template class for circular queue
 * \author    Ratnadip Choudhury
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Defines and implements the template class for circular queue
 */
// clang-format on

#ifndef KERNEL_UTILITIES_MSGBUFLINVFSE_H_
#define KERNEL_UTILITIES_MSGBUFLINVFSE_H_

#include "BaseMsgBufAll.h"
#include "Error.h"

const int SIZE_APP_LIN_BUFFER = 5000;

/* This is the concrete template class of a circular queue where each entry is
of fixed size. Implemented as a template class so as to cater to any data type.
Here SMSGBUFFER is the data type in operation. */
template <typename SMSGBUFFER>
class CMsgBufLINVFSE {
 protected:
  SMSGBUFFER m_asMsgBuffer[SIZE_APP_LIN_BUFFER];  // The data buffer
  CRITICAL_SECTION m_CritSectionForGB;            // To make it thread safe

  int m_nIndexRead;          // Current read index
  int m_nIndexWrite;         // Current write index
  int m_nMsgCount;           // Number of message entries
  int m_nMsgSize;            /* At the beginning we need to
store size of a message entry. This information will be used frequently */
  HANDLE m_hNotifyingEvent;  // Event to be signalled when
                             // there is at least one message

 public:
  // Short explanation on each member function is present in the base class.
  // That's why information are not repeated unnecessarily.

  CMsgBufLINVFSE();
  ~CMsgBufLINVFSE();

  int ReadFromBuffer(SMSGBUFFER* psMsgBuffer, __int64 nSlotId);
  int ReadFromBuffer(SMSGBUFFER* psMsgBuffer, int nIndex);
  int WriteIntoBuffer(const SMSGBUFFER* psMsg, __int64 nSlotId, int& nIndex);
  int WriteIntoBuffer(const SMSGBUFFER* psMsg);
  int GetBufferLength(void) const;
  void vClearMessageBuffer(void);
  HANDLE hGetNotifyingEvent(void) const;
  void vDoSortBuffer(int nField, bool bAscending);
  void vDoSortIndexMapArray();
  void nGetMapIndexAtID(int nIndex, __int64& nMapIndex);

 private:
  CMap<__int64, __int64, int, int> m_omIdIndexMap;
};

/******************************************************************************
  Function Name    :  CMsgBufLINVFSE
  Input(s)         :  -
  Output           :  -
  Functionality    :  Standard constructor
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  1.12.2009
  Modification date:
  Modification By  :
******************************************************************************/
template <typename SMSGBUFFER>
CMsgBufLINVFSE<SMSGBUFFER>::CMsgBufLINVFSE() {
  m_nMsgSize = sizeof(SMSGBUFFER);
  vClearMessageBuffer();
  InitializeCriticalSection(&m_CritSectionForGB);
  m_hNotifyingEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
}

/******************************************************************************
  Function Name    :  ~CMsgBufLINVFSE
  Input(s)         :  -
  Output           :  -
  Functionality    :  Destructor
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  1.12.2009
  Modification date:
  Modification By  :
******************************************************************************/
template <typename SMSGBUFFER>
CMsgBufLINVFSE<SMSGBUFFER>::~CMsgBufLINVFSE() {
  CloseHandle(m_hNotifyingEvent);
  m_hNotifyingEvent = nullptr;
  DeleteCriticalSection(&m_CritSectionForGB);
}

/******************************************************************************
  Function Name    :  vClearMessageBuffer
  Input(s)         :  void
  Output           :  void
  Functionality    :  Clears the message buffer and resets the indices.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  1.12.2009
  Modification date:
  Modification By  :
******************************************************************************/
template <typename SMSGBUFFER>
void CMsgBufLINVFSE<SMSGBUFFER>::vClearMessageBuffer(void) {
  memset((BYTE*)m_asMsgBuffer, 0, SIZE_APP_LIN_BUFFER * m_nMsgSize);
  m_omIdIndexMap.RemoveAll();
  m_nIndexRead = 0;
  m_nIndexWrite = 0;
  m_nMsgCount = 0;
}

/******************************************************************************
  Function Name    :  ReadFromBuffer
  Input(s)         :  psMsg - The target message entry. An [out] parameter.
  Output           :  EMPTY_APP_BUFFER if buffer is empty; else CALL_SUCCESS.
  Functionality    :  Reads a message entry and advances the read index. On
                      successful reading operation the present entry is
                      invalidated to make room for a new entry.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  1.12.2009
  Modification date:
  Modification By  :
******************************************************************************/
template <typename SMSGBUFFER>
int CMsgBufLINVFSE<SMSGBUFFER>::ReadFromBuffer(SMSGBUFFER* psMsg, int nIndex) {
  HRESULT nResult = S_OK;

#ifdef _DEBUG
  ASSERT(psMsg != nullptr);
  ASSERT(!(m_nIndexRead > SIZE_APP_LIN_BUFFER));
#endif

  // Lock the buffer
  EnterCriticalSection(&m_CritSectionForGB);

  // Check entry indexed by m_nIndexRead. If this particular entry
  if (m_nMsgCount == 0) {
    nResult = EMPTY_APP_BUFFER;
  } else if (nIndex >= SIZE_APP_LIN_BUFFER) {
    nResult = ERR_INVALID_INDEX;
  } else {
    INT TempIndex = m_nIndexRead + nIndex;
    if (m_nIndexRead + nIndex >= SIZE_APP_LIN_BUFFER) {
      TempIndex -= SIZE_APP_LIN_BUFFER;
    }
    *psMsg = m_asMsgBuffer[TempIndex];
  }
  // Unlock the buffer
  LeaveCriticalSection(&m_CritSectionForGB);

  return nResult;
}

template <typename SMSGBUFFER>
int CMsgBufLINVFSE<SMSGBUFFER>::ReadFromBuffer(SMSGBUFFER* psMsg,
                                               __int64 nSlotId) {
  HRESULT nResult = CALL_SUCCESS;
  int nIndex;

#ifdef _DEBUG
  ASSERT(psMsg != nullptr);
  ASSERT(!(m_nIndexRead > SIZE_APP_LIN_BUFFER));
#endif

  // Lock the buffer
  EnterCriticalSection(&m_CritSectionForGB);

  // Check entry indexed by m_nIndexRead. If this particular entry
  if (m_nMsgCount == 0) {
    nResult = EMPTY_APP_BUFFER;
  } else {
    if (m_omIdIndexMap.Lookup(nSlotId, nIndex)) {
      *psMsg = m_asMsgBuffer[nIndex];
    } else {
      nResult = ERR_INVALID_SLOT;
    }
  }
  // Unlock the buffer
  LeaveCriticalSection(&m_CritSectionForGB);

  return nResult;
}

/******************************************************************************
  Function Name    :  WriteIntoBuffer
  Input(s)         :  psMsg - The source message entry. An [in] parameter.
  Output           :  ERR_FULL_APP_BUFFER if buffer is full; else CALL_SUCCESS.
  Functionality    :  Writes a message entry and advances the write index.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  1.12.2009
  Modification date:
  Modification By  :
******************************************************************************/
template <typename SMSGBUFFER>
int CMsgBufLINVFSE<SMSGBUFFER>::WriteIntoBuffer(const SMSGBUFFER* psMsg,
                                                __int64 nSlotId, int& nIndex) {
  int nResult = CALL_SUCCESS;

#ifdef _DEBUG
  ASSERT(psMsg != nullptr);
  ASSERT(!(m_nIndexWrite > SIZE_APP_LIN_BUFFER));
#endif
  // Lock the buffer
  EnterCriticalSection(&m_CritSectionForGB);
  // Check for buffer overflow
  if (m_nMsgCount == SIZE_APP_LIN_BUFFER) {
    nResult = ERR_FULL_APP_BUFFER;
  } else {
    if (m_omIdIndexMap.Lookup(nSlotId, nIndex)) {
      m_asMsgBuffer[nIndex] = *psMsg;
    } else {
      nIndex = m_nMsgCount;
      m_asMsgBuffer[m_nMsgCount] = *psMsg;
      m_omIdIndexMap[nSlotId] = m_nMsgCount;
      ++m_nMsgCount;
    }
    SetEvent(m_hNotifyingEvent);
  }

  LeaveCriticalSection(&m_CritSectionForGB);  // Unlock the buffer

  return nResult;
}
template <typename SMSGBUFFER>
int CMsgBufLINVFSE<SMSGBUFFER>::WriteIntoBuffer(const SMSGBUFFER* psMsg) {
  int nResult = CALL_SUCCESS;

#ifdef _DEBUG
  ASSERT(psMsg != nullptr);
  ASSERT(!(m_nIndexWrite > SIZE_APP_LIN_BUFFER));
#endif
  // Lock the buffer
  EnterCriticalSection(&m_CritSectionForGB);
  // Check for buffer overflow
  if (m_nMsgCount == SIZE_APP_LIN_BUFFER) {
    m_asMsgBuffer[m_nIndexRead] = *psMsg;
    m_nIndexRead++;
    if (m_nIndexRead == SIZE_APP_LIN_BUFFER) {
      m_nIndexRead = 0;
    }
    nResult = ERR_FULL_APP_BUFFER;
  } else {
    m_asMsgBuffer[m_nMsgCount] = *psMsg;
    ++m_nMsgCount;
    SetEvent(m_hNotifyingEvent);
  }

  LeaveCriticalSection(&m_CritSectionForGB);  // Unlock the buffer

  return nResult;
}
/******************************************************************************
  Function Name    :  GetBufferLength
  Input(s)         :  void
  Output           :  Number of message entries (int)
  Functionality    :  Returns the number of unread entries in the queue.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  1.12.2009
  Modification date:
  Modification By  :
******************************************************************************/
template <typename SMSGBUFFER>
int CMsgBufLINVFSE<SMSGBUFFER>::GetBufferLength(void) const {
  return m_nMsgCount;
}

/******************************************************************************
  Function Name    :  hGetNotifyingEvent
  Input(s)         :  void
  Output           :  The notifying event handle (HANDLE)
  Functionality    :  Returns handle of the event that gets signalled when
                      a message entry is added.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  1.12.2009
  Modification date:
  Modification By  :
******************************************************************************/
template <typename SMSGBUFFER>
HANDLE CMsgBufLINVFSE<SMSGBUFFER>::hGetNotifyingEvent(void) const {
  return m_hNotifyingEvent;
}

/******************************************************************************
  Function Name    :  vDoSortBuffer
  Input(s)         :  nField - The field to be used as the sorting key.
  Output           :  -
  Functionality    :  Reorders the list according to the sorting key specified.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Ratnadip Choudhury
  Date Created     :  21-06-2010
  Modification date:
  Modification By  :
******************************************************************************/

template <typename SMSGBUFFER>
void CMsgBufLINVFSE<SMSGBUFFER>::vDoSortBuffer(int /*nField*/,
                                               bool /*bAscending*/) {}

// clang-format off
/******************************************************************************
  Function Name    :  vDoSortIndexMapArray
  Input(s)         :
  Output           :  -
  Functionality    :  Reorders the Index Map Array according to the order specified.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Arunkumar K
  Date Created     :  28-06-2010
  Modification date:
  Modification By  :
******************************************************************************/
// clang-format on
template <typename SMSGBUFFER>
void CMsgBufLINVFSE<SMSGBUFFER>::vDoSortIndexMapArray() {
  for (int nCnt = 0; nCnt < m_omIdIndexMap.GetCount(); nCnt++) {
    __int64 nSlotID = SMSGBUFFER::GetSlotID(m_asMsgBuffer[nCnt]);
    m_omIdIndexMap.SetAt(nSlotID, nCnt);
  }
}

// clang-format off
/******************************************************************************
  Function Name    :  nGetMapIndexAtID
  Input(s)         :  nIndex - The Index at which the SlotID needs to be pickef from.
  Output           :  -
  Functionality    :  Returns the Slot ID of the index specified in m_omIdIndexMap.
  Member of        :  CMsgBufLINVFSE
  Friend of        :  -
  Author(s)        :  Arunkumar K
  Date Created     :  28-06-2010
  Modification date:
  Modification By  :
******************************************************************************/
// clang-format on
template <typename SMSGBUFFER>
void CMsgBufLINVFSE<SMSGBUFFER>::nGetMapIndexAtID(int nIndex,
                                                  __int64& nMapIndex) {
  POSITION pos = m_omIdIndexMap.GetStartPosition();
  int nLocalIndex = 0;
  __int64 nSlotID;
  while (pos != nullptr) {
    m_omIdIndexMap.GetNextAssoc(pos, nSlotID, nLocalIndex);
    if (nIndex == nLocalIndex) {
      nMapIndex = nSlotID;
      return;
    }
  }
}

#endif  // KERNEL_UTILITIES_MSGBUFLINVFSE_H_