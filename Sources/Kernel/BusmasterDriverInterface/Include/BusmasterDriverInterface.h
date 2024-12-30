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
// clang-format off
/**
* \file      DIL_Interface/DIL_Interface_extern.h
* \brief     Declaration file for the exported function used to get the
* \author    Pradeep Kadoor
* \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
*
* Declaration file for the exported function used to get the
*/
// clang-format on

#ifndef KERNEL_BUSMASTERDRIVERINTERFACE_BUSMASTERDRIVERINTERFACE_H_
#define KERNEL_BUSMASTERDRIVERINTERFACE_BUSMASTERDRIVERINTERFACE_H_

#include "IBusService.h"
#include "ProtocolsDefinitions.h"

#include <Windows.h>

#if defined BUSMASTERDRIVERINTERFACE_EXPORTS
#define USAGEMODE __declspec(dllexport)
#else
#define USAGEMODE __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {  // only need to export C interface if used by C++ source code
#endif

/*  Exported function list */
USAGEMODE HRESULT GetDilInterface(ETYPE_BUS eBusType,
                                  IBusService** ppvInterface);
typedef HRESULT (*pDIL_GetInterface)(ETYPE_BUS eBusType,
                                     IBusService** ppvInterface);
#ifdef __cplusplus
}
#endif

#endif  // KERNEL_BUSMASTERDRIVERINTERFACE_BUSMASTERDRIVERINTERFACE_H_