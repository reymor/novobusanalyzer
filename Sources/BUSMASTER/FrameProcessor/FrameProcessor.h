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
 * \file      FrameProcessor.h
 * \brief     Definition file for CFrameProcessorApp class.
 * \author    Ratnadip Choudhury
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Definition file for CFrameProcessorApp class.
 */

#ifndef BUSMASTER_FRAMEPROCESSOR_FRAMEPROCESSOR_H_
#define BUSMASTER_FRAMEPROCESSOR_FRAMEPROCESSOR_H_

class CFrameProcessorApp : public CWinApp
{
    // Overrides
public:
    CFrameProcessorApp();
    ~CFrameProcessorApp();

    // To be used by the read thread
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
    virtual int ExitInstance();
};

#endif // BUSMASTER_FRAMEPROCESSOR_FRAMEPROCESSOR_H_