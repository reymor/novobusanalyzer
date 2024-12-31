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
 * \file      Application/TraceWnd/NotificWnd.h
 * \brief     This file contain the definition CNotificWnd class. The user can
 * \author    Ravikumar Patil
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * This file contain the definition CNotificWnd class. The user can
 */

#ifndef BUSMASTER_APPLICATION_TRACEWND_NOTIFICWND_H_
#define BUSMASTER_APPLICATION_TRACEWND_NOTIFICWND_H_

//Definition of CNotificListbox class
#include "NotificListbox.h"
#include "Application/MDIChildBase.h"   // For Common MDI base class

typedef struct tagNOTIFICWNDPARAMS {
    WINDOWPLACEMENT     m_sWndPlacement;
    BYTE                m_bSetFlag_Disp;
    BYTE                m_bSetFlag_Log;
} NOTIFICWNDPARAMS, *PNOTIFICWNDPARAMS;

class CNotificWnd : public CMDIChildBase
{
    DECLARE_DYNCREATE(CNotificWnd)
public:
    CNotificWnd();
    virtual ~CNotificWnd();
public:
    // Set the font of window
    BOOL bCreateNotificWindow(CMDIFrameWnd* pomParentWnd);
    // To display a string into trace window
    void vDisplayString(const CString& omStr);
protected:
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnClose();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    DECLARE_MESSAGE_MAP()
private:
    CCriticalSection m_omCriticalSection;
    UINT_PTR m_unTimer;

    // Add string items to the list box of output window
    void vAddString(CString omStr);
    // Set the content of list box.
    void vSaveWinStatus(WINDOWPLACEMENT sWinCurrStatus);
    void vGetWinStatus(WINDOWPLACEMENT& sWinCurrStatus);
    VOID vSetWindowFont();
    CFont m_omNewFont;
    CSize m_omSizeMaxTxtExtent;
    CNotificListbox m_omListBox;
    NOTIFICWNDPARAMS m_sNotificWndParams;
    LRESULT DoConfigOperation(WPARAM WParam, LPARAM LParam);
    void vSaveNotificWndConfig();
    UINT unGetStoreNFBufferSize();
    void vLoadNotificWndConfig();
    void SaveNFDataIntoBuffer(BYTE* DesBuffer);
    void CopyNFDataFromBuffer(BYTE* SrcBuffer);
    BOOL bIsConfigChanged();

public:
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
};

#endif // BUSMASTER_APPLICATION_TRACEWND_NOTIFICWND_H_
