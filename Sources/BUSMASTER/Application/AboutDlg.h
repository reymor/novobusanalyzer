#ifndef BUSMASTER_APPLICATION_ABOUTDLG_H_
#define BUSMASTER_APPLICATION_ABOUTDLG_H_

#include "resource.h"
#include "Utility/FFListCtrl.h"

class CAboutDlg : public CDialog {
    DECLARE_MESSAGE_MAP()
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListComponents(NMHDR *pNMHDR, LRESULT *pResult);
    CAboutDlg();
    enum { IDD = IDD_ABOUTBOX };
	CFFListCtrl m_lstComponents;
};

#endif // BUSMASTER_APPLICATION_ABOUTDLG_H_
