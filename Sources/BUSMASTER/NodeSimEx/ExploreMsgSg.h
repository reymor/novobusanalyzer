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
 * \file      ExploreMsgSg.h
 * \brief     This header file contains the defintion of class
 * \author    Amarnath Shastry
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * This header file contains the defintion of class
 */

#ifndef BUSMASTER_NODESIMEX_EXPLOREMSGSG_H_
#define BUSMASTER_NODESIMEX_EXPLOREMSGSG_H_

#include "HashDefines.h"
#include "GlobalObj.h"

class CExploreMsgSg : public CDialog
{
    // Construction
public:
    // Holds selected message name
    CString m_omStrMessageName;

    // Holds selected item, message or signal
    CString m_omStrSelectedItemText;

    // Overrided constructor
    CExploreMsgSg(CFunctionEditorDoc* pDoc,
                  CMsgNameMsgCodeListDataBase& odMsgNameCodeListDb,
                  BOOL bCheckRequired,
                  eMESSAGEFROM,
                  eSELTYPE,
                  CGlobalObj* pGlobalObj,
                  CWnd* pParent = nullptr);

    // Dialog Data
    enum { IDD = IDD_MSG_SG_DLG };
    CListBox    m_omSignalListBox;
    CListCtrl   m_omMsgList;
    BOOL    m_bWantStructure;
    CGlobalObj* m_pGlobalObj;

public:
    void vSetFrameList(IBMNetWorkGetService* ouClusterConfig, ETYPE_BUS eBus);

    // Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
protected:

    // Generated message map functions
    afx_msg void OnDblclkListMsgs(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkListSignals();
    afx_msg void OnSelect();
    virtual BOOL OnInitDialog();
    afx_msg void OnCbtnCancel();
    afx_msg void OnItemchangedLstcMsgs(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickLstcMsgs(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

    virtual void vPopulateMsgList(std::map<std::string, unsigned int>& mapMsgNameAndCode);
    virtual void vPopulateSignalList(INT unChannelNum, DWORD dwMsgCode, std::list<std::string>& lstSignalNames);
    void vPopulateListBox(CListBox& omListBox, const std::list<std::string> lstItems);
    virtual void vGetMsgList(ETYPE_BUS eBus, int nChannel, std::map<std::string, unsigned int>& mapMsgNameAndCode);
    virtual void vGetSignalList(ETYPE_BUS eBus, int nChannel, DWORD dwMsgCode, std::list<std::string>& lstSigNames);


    // enum to indicate whether to
    // select message or signal
    eSELTYPE m_eSelectType;

private:
    CFunctionEditorDoc* m_pDoc;
    CMsgNameMsgCodeListDataBase& m_odMsgNameCodeListDb;         //CAPL_DB_NAME_CHANGE
    // Dialog class may be called by any window
    eMESSAGEFROM m_eWindow;
    // Flag to enable check box option
    BOOL m_bCheckRequired;

    // Store last selected message item
    int m_nMsgIndex;
    //Get Signal Names from Message Id
    void vGetSigNamesFromMsgCode(DWORD dwMsgCode, CStringList& omSignalNames);
    void vFillMsgList(ETYPE_BUS eBus,std::list<IFrame*>& lstMsgNames);
    void vFillPduList(ETYPE_BUS eBus,std::list<IPdu*>& lstMsgNames);
    void vFillSignalList();


    void vPopulateListCtrl(CListCtrl& omListCtrl,const std::map<std::string,unsigned int>& mapNames,bool bSetItemData);

    void vPopulateChannel(int nChannelCount);
    int nGetChannelCount(ETYPE_BUS eBus);
    int nGetSelChannel();
    void SetHorizExtentListBox(CListBox& omListBox);
    void vResizeDialog();

    IBMNetWorkGetService* m_ouClusterConfig;
    ETYPE_BUS m_eBus;
    bool m_bIsPduFound;
};

#endif // BUSMASTER_NODESIMEX_EXPLOREMSGSG_H_