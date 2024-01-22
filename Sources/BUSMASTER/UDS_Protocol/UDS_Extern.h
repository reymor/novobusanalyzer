/**
 * \file      UDS_Extern.h
 * \author     Sanchez Marin Maria Alejandra
 * Designer:    Bentea Radu Mihai
 */

#ifndef BUSMASTER_UDS_PROTOCOL_UDS_EXTERN_H_
#define BUSMASTER_UDS_PROTOCOL_UDS_EXTERN_H_

#include "CANDriverDefines.h"
#include "UDS_Protocol.h"

#if defined USAGEMODE
#undef USAGEMODE
#endif

#if defined USAGE_EXPORT
#define USAGEMODE __declspec(dllexport)
#else
#define USAGEMODE __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
USAGEMODE HRESULT UDS_Initialise();
// Function to show main window
USAGEMODE HRESULT DIL_UDS_ShowWnd(HWND hParent, int TotalChannels);
USAGEMODE HRESULT EvaluateMessage(STCAN_MSG Mensaje);
USAGEMODE HRESULT UpdateChannelUDS(HWND hParent);
USAGEMODE HRESULT DIL_UDS_ShowSettingWnd(HWND hParent);
USAGEMODE HRESULT TX_vSetDILInterfacePtrUDS(void* ptrDILIntrf);
USAGEMODE HRESULT DIL_MainPanel(HWND hParent, int TotalChannels);

#ifdef __cplusplus
}
#endif

#endif  // BUSMASTER_UDS_PROTOCOL_UDS_EXTERN_H_