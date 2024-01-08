// CAN_RUSOKU.h : main header file for the CAN_RUSOKU DLL
//

#pragma once

#include "BaseDIL_CAN_Controller.h"
#include "DIL_Interface/HardwareListingCAN.h"

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

// CCANRUSOKUApp
// See CAN_RUSOKU.cpp for the implementation of this class
//

class _RCAN_cfg : public IChangeRegisters
{
public:
    long handle;
    char szLocation[MAX_PATH + 1];
    DWORD dwMode;
    void* vSpeed;
    //VSCAN_BTR btr;
    //VSCAN_CODE_MASK codeMask;
    BOOL bDualFilter;
    BOOL bTimestamps;
    BOOL bDebug;
    int InvokeAdavancedSettings(PSCONTROLLER_DETAILS pControllerDetails, UINT nCount, UINT) override;
    DOUBLE vValidateBaudRate(DOUBLE, int, UINT) override;
    //std::string GetBaudRate(int speed);
};

class CCANRUSOKUApp : public CWinApp
{
public:
	CCANRUSOKUApp();

// Overrides
public:
	virtual BOOL InitInstance();
    virtual BOOL ExitInstance();

	DECLARE_MESSAGE_MAP()
};


void DebugPrintf(LPCSTR fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    //wchar_t dbg_out[4096];
    char dbg_out[4096];
    //vswprintf_s(dbg_out, sizeof(dbg_out), fmt, argp);
    vsprintf_s(dbg_out, sizeof(dbg_out), fmt, argp);
    va_end(argp);
    OutputDebugStringA(dbg_out);
}

/**
 * Channel information
 */
struct CChannel
{
    /* Kvaser channel details */
    int     m_nChannel;
    char    m_strName[512];
    char    m_strSerialNumber[16]; //GS    
    DWORD   m_dwHwType;
    LONG    m_hnd;
    int     m_nHwIndex;
    int     m_nHwChannel;
    int     m_nIsOnBus;
    int     m_nDriverMode;
    int     m_nTxAck;

    /* To store baud rate information */
    USHORT  m_usClock;
    USHORT  m_usSampling;
    UINT    m_unBaudrate;

    /* Bit Timing */
    USHORT  m_usBaudRate; /*BTR0,BTR1*/
    BYTE    m_bCNF1;
    BYTE    m_bCNF2;
    BYTE    m_bCNF3;

    /* Acceptance Filter information for standard and extended envelopes*/
    SACC_FILTER_INFO     m_sFilter[2];

    /** Programmed warning limit of this channel */
    UCHAR m_ucWarningLimit;

    /** Tx Error counter value */
    UCHAR m_ucTxErrorCounter;

    /** Rx Error counter value */
    UCHAR m_ucRxErrorCounter;

    /** Peak Tx Error counter value */
    UCHAR m_ucPeakTxErrorCounter;

    /** Peak Rx Error counter value */
    UCHAR m_ucPeakRxErrorCounter;

    /** Tx Error Handler execution state */
    BOOL m_bTxErrorExecuted;

    /** Rx Error Handler execution state */
    BOOL m_bRxErrorExecuted;

    // Init members with default value
    CChannel()
    {
        m_nIsOnBus = 0;
        //m_nDriverMode = canDRIVER_NORMAL;
        m_nChannel = -1;
        m_hnd = -1;
        m_nTxAck = 0; // Default is TxAck off

        // Baud Rate
        m_usBaudRate = defBAUD_RATE;

        // Programmed warning limit of this channel
        m_ucWarningLimit = defWARNING_LIMIT_INT;

        // Tx Error counter value
        m_ucTxErrorCounter = 0;

        // Rx Error counter value
        m_ucRxErrorCounter = 0;

        // Peak Tx Error counter value
        m_ucPeakTxErrorCounter = 0;

        // Peak Rx Error counter value
        m_ucPeakRxErrorCounter = 0;

        // Tx Error Handler execution state
        m_bTxErrorExecuted = FALSE;

        // Rx Error Handler execution state
        m_bRxErrorExecuted = FALSE;
    }
};

