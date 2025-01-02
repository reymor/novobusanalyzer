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
 * \file      MsgFilterConfigPage.h
 * \brief     Interface file for CMsgFilterConfigPage class
 * \author    Raja N
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Interface file for CMsgFilterConfigPage class
 */

#pragma once


#include "DataTypes\MainSubEntry.h"

struct filterDetails
{
    bool mISValidSettings;
    std::map<std::string, bool> mFitersApplied;
    std::list<std::string> mFiltersConfigured;
};
class CMsgFilterConfigPage : public CPropertyPage
{
    DECLARE_DYNCREATE(CMsgFilterConfigPage)
    std::string mCaption;
    filterDetails* mFilterDetails;
    // Construction
public:
    // Standard constructor
    CMsgFilterConfigPage();

    CMsgFilterConfigPage(std::string caption, filterDetails*, HWND hMsgWnd);
    // Standard destructor
    ~CMsgFilterConfigPage();

    // Dialog Data
    enum { IDD = IDD_DLG_MSG_DISPLAY_FILTER };
    CListCtrl   m_omLstcFilterList;
public:
    virtual void OnOK();
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    // Implementation
protected:
    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnBtnConfigure();
    DECLARE_MESSAGE_MAP()
private:
    // To create image list
    BOOL bCreateImageList();
    // To create filter list UI
    void vCreateFilterUIList();
    // To init filter list UI
    void vInitFilterUIList();
    // To craete filter data structures
    void vInitFilterDataList();
    // To update the filter list with UI changes
    void vUpdateDataFromUI();

    void populateFilterConfiguration(CMainEntryList& DestList);
    void updateFilterConfiguration(CMainEntryList& DestList);
private:
    // Image list for the filter items
    CImageList m_omImageList;
    HWND m_hMsgWnd; //Msg window handle
    const void* m_psFilterConfigured;
    std::map<std::string, bool> mUpdatedFilters;

};
