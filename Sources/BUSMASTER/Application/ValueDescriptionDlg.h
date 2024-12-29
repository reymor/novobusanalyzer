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
 * \file      ValueDescriptionDlg.h
 * \brief     This header file contains the defintion of class
 * \author    Amarnath Shastry
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * This header file contains the defintion of class
 */

#ifndef BUSMASTER_APPLICATION_VALUEDESCRIPTIONDLG_H_
#define BUSMASTER_APPLICATION_VALUEDESCRIPTIONDLG_H_

/////////////////////////////////////////////////////////////////////////////
// CValueDescriptionDlg dialog

#include "Utility/RadixEdit.h"

class CValueDescriptionDlg: public CDialog {
public:
    CValueDescriptionDlg(const SDBPARAMS& sDbParams,
                            eMODES eMode,
                            CString omStrMessageCode,
                            CString omStrSgName,
                            INT nIndex,
                            CWnd* pParent = nullptr );

    // Dialog Data
    enum { IDD = IDD_DLG_VALUE_DESCRIPTOR };
    CString m_omStrDescriptor;
    CString m_omStrValue;
    CRadixEdit m_ounSigValue;

    CString bSignalType;

    // Overrides
    // ClassWizard generated virtual function overrides
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:

    // Generated message map functions
    afx_msg void OnClickedOk();
    afx_msg void OnCancel();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
private:
    SDBPARAMS m_sDbParams;
    CString m_omStrPrevSignalVal;
    CString m_omStrPrevDesc;
    BOOL m_bMode;
    CString m_omStrSgName;
    CString m_omStrMessageCode;
    BOOL m_bIsCanceled;
    INT m_nIndex;
    BOOL bIsDataModified(); //KSS
};

#endif // BUSMASTER_APPLICATION_VALUEDESCRIPTIONDLG_H_
