/**
 * \file      UDS_NegRespMng.h
 * \brief     Interface file for CUDS_NegRespMng class
 * \author    Sanchez Marin Maria Alejandra
 * Designer:  Bentea Radu Mihai
 * Interface file for the Negative Response Description
 */

#ifndef BUSMASTER_UDS_PROTOCOL_UDS_NEGRESPMNG_H_
#define BUSMASTER_UDS_PROTOCOL_UDS_NEGRESPMNG_H_

// clang-format off
#include "afxwin.h"
// clang-format on

#include "UDSWnd_Defines.h"
#include "UDS_Protocol.h"
#include "UDS_Resource.h"

extern int BytesShown_Line;
extern int initialByte;
extern CString CurrentService;

/** This variable is used to know if a message has been sent from the UDSMainWnd
 */
extern bool FSending;

/** Variable used to control if a message received should be shown */
// if it's TRUE the message should not be sent
extern bool FDontShow;
// This variable is used to check if the response corresponds to my request
extern long Font_Color;

class CUDS_NegRespMng {
 public:
  CUDS_NegRespMng(CUDS_Protocol* pEngine);
  ~CUDS_NegRespMng(void);
  CString VerifyNegResponse(unsigned char value);
  CString evaluateResp(unsigned char arrayMsg[], int Byte2Init);
};

#endif  // BUSMASTER_UDS_PROTOCOL_UDS_NEGRESPMNG_H_