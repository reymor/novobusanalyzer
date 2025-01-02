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
 * \file      IncludeHeaderDlg.h
 * \brief     This header file contains the defintion of class
 * \author    Ratnadip Choudhury
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * This header file contains the defintion of class
 */

#ifndef BUSMASTER_NODESIMEX_INCLUDEHEADERDLG_H_
#define BUSMASTER_NODESIMEX_INCLUDEHEADERDLG_H_

#include "NodeSimEx_resource.h"

class CIncludeHeaderDlg : public CDialog
{
private:
    CFunctionEditorDoc* m_pDoc;
    // Construction
public:
    CIncludeHeaderDlg(CFunctionEditorDoc* pDoc, CWnd* pParent = nullptr);   // standard constructor

    // Dialog Data
    enum { IDD = IDD_DLG_INCLUDE_HEADERS };
    CString m_omStrIncludeFilename;


protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:

    // Generated message map functions
    afx_msg void OnOk();
    afx_msg void OnBrowse();
    afx_msg void OnCancel();
    DECLARE_MESSAGE_MAP()
private:
};

#endif // BUSMASTER_NODESIMEX_INCLUDEHEADERDLG_H_