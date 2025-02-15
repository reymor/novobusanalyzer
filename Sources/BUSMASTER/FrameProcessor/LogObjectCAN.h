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
 * \file      LogObjectCAN.h
 * \brief     Definition file for CLogObjectCAN class.
 * \author    Ratnadip Choudhury
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Definition file for CLogObjectCAN class.
 */

#ifndef BUSMASTER_FRAMEPROCESSOR_LOGOBJECTCAN_H_
#define BUSMASTER_FRAMEPROCESSOR_LOGOBJECTCAN_H_

#include "DataTypes/Log_Datatypes.h"
#include "DataTypes/Filter_Datatypes.h"
#include "BaseLogObject.h"
#include "include/BaseDefs.h"


class CLogObjectCAN : public CBaseLogObject
{
private:
    // The filter object
    SFILTERAPPLIED_CAN m_sFilterApplied;

    // To format the header
    void vFormatHeader(CString& omHeader, ETYPE_BUS eBus = CAN);

    // To format the footer
    void vFormatFooter(CString& omFooter);

    bool bToBeLogged(SFRAMEINFO_BASIC_CAN& CANInfo_Basic);

protected:
    // To copy specific data pertaining to the conrete class.
    void Der_CopySpecificData(const CBaseLogObject* pouLogObjRef);
    // Set configuration data - concrete class specific logics
    BYTE* Der_SetConfigData(BYTE* pvDataStream);
    virtual int Der_SetConfigData(xmlNodePtr);
    // Get configuration data - concrete class specific logics
    BYTE* Der_GetConfigData(BYTE* pvDataStream) const;
    void Der_GetConfigData(xmlNodePtr pNodePtr) const;
    // To get the total buffer size - concrete class specific logics
    UINT Der_unGetBufSize(void) const;

public:

    CStringArray        m_omListDBFiles;
    SCONTROLLER_DETAILS*    m_pasControllerDetails;
    int                 m_nNumChannels;

    CLogObjectCAN(CString omVersion);    // Overloaded constructor
    ~CLogObjectCAN();   // Destructor

    // Log a CAN data object
    bool bLogData(const SFORMATTEDDATA_CAN&);

    // Enable / disable filter
    void EnableFilter(bool bEnable);

    // Get the filter info structure
    void GetFilterInfo(SFILTERAPPLIED_CAN& sFilterInfo) const;
    // Set the filter info structure
    void SetFilterInfo(const SFILTERAPPLIED_CAN& sFilterInfo);

    // Get the list of database files associated
    void Der_GetDatabaseFiles(CStringArray& omList);
    // Set the list of database files associated
    void Der_SetDatabaseFiles(const CStringArray& omList);

    // Set the baud rate details for each channel
    void Der_SetChannelBaudRateDetails(void* controllerDetails,
                                       int nNumChannels);
    // To get the channel baud rate info for each channel
    void Der_GetChannelBaudRateDetails(void* controllerDetails,
                                       int& nNumChannels);
};

#endif // BUSMASTER_FRAMEPROCESSOR_LOGOBJECTCAN_H_