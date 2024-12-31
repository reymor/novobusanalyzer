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

/**
 * \file      Application/TraceWnd/UIThread.h
 * \brief     This is the interface file for CNotificWnd class
 * \author    Ratnadip Choudhury
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * This is the interface file for CNotificWnd class
 */

#ifndef BUSMASTER_APPLICATION_TRACEWND_UITHREAD_H_
#define BUSMASTER_APPLICATION_TRACEWND_UITHREAD_H_

// Interface file for class CNotificWnd
#include "NotificWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CUIThread thread

class CUIThread : public CWinThread {
    DECLARE_DYNCREATE(CUIThread)
protected:
    CUIThread();
    CNotificWnd* m_podTraceWinObj;
public:
    BOOL bCreateTraceWindow(CMDIFrameWnd*);
    void vUpdateWndCo_Ords(WINDOWPLACEMENT& wndPlacement, BOOL bLoadIntoTrace);
    // To display texts on the trace window
    void vAddString(CString omStr);
    // To know if the trace window is visible
    BOOL bIsTraceWindowVisible(void);
    HWND hGetHandleTraceWnd();

public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

protected:
    virtual ~CUIThread();
    // To update the window status from the configuration file
    afx_msg void vUpdateWinStatusFromCfg(UINT, LONG);
    // To process thread messages
    afx_msg void vWriteTextToTrace(UINT, LONG);
    afx_msg void vProcessThreadMsg(UINT, LONG);

    DECLARE_MESSAGE_MAP()
};

#endif // BUSMASTER_APPLICATION_TRACEWND_UITHREAD_H_
