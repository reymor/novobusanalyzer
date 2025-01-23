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
 * \file      GraphConfiguration.h
 * \brief     Interface file for CGraphConfiguration class
 * \author    Raja N
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Interface file for CGraphConfiguration class
 */

#ifndef BUSMASTER_APPLICATION_GRAPHCONFIGURATION_H_
#define BUSMASTER_APPLICATION_GRAPHCONFIGURATION_H_

// For Graph Parameter Class definition
#include "GraphParameters.h"

class CGraphConfiguration : public CDialog {
public:
    // Local instance of View Style parameter
    CGraphParameters m_omGraphParams;
    ETYPE_BUS m_eBusType;
    // standard constructor
    CGraphConfiguration(CWnd* pParent = nullptr);

    // Dialog Data
    enum { IDD = IDD_DLG_GRAPH_WINDOW_CONF };
    CColorSelector   m_omAxisColor;
    CColorSelector   m_omFrameColor;
    CColorSelector   m_omGridColor;
    CColorSelector   m_omPlotColor;
    int     m_nYGridCount;
    int     m_nXGridCount;
    int     m_nUpdateRate;
    int     m_nBufferSize;
    int     m_omFrameType;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    afx_msg void OnSetDefault();
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
private:
    // To set the values of the object in to UI control
    void vSetValues(CGraphParameters omParam);
public:
    int m_nLineDisplay;
};

#endif // BUSMASTER_APPLICATION_GRAPHCONFIGURATION_H_
