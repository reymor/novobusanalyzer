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
 * @brief Concrete class definition for the application service layer
 * @authors Ratnadip Choudhury, Anish Kumar
 * @copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Concrete class definition for the application service layer
 */

#ifndef BUSMASTER_APPLICATION_APPSERVICES_IMPL_H_
#define BUSMASTER_APPLICATION_APPSERVICES_IMPL_H_

#include "DataTypes/BaseAppServices.h"

class CAppServices_Impl : public CBaseAppServices {
public:
    CAppServices_Impl();
    virtual ~CAppServices_Impl();

    BOOL bWriteToTrace(char* pcTraceStr);

    CUIThread* m_podUIThread;
};

#endif // BUSMASTER_APPLICATION_APPSERVICES_IMPL_H_
