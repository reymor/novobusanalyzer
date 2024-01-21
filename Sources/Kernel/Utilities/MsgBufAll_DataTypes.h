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
 * \file      MsgBufAll_DataTypes.h
 * \brief     Defines concrete class for data types of different buses.
 * \author    Ratnadip Choudhury
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Defines concrete class for data types of different buses.
 */
// clang-format on

#ifndef KERNEL_UTILITIES_MSGBUFALL_DATATYPES_H_
#define KERNEL_UTILITIES_MSGBUFALL_DATATYPES_H_

#include "Base_FlexRay_Buffer.h"
#include "DataTypes/J1939_DataTypes.h"
#include "MsgBufFSE.h"
#include "MsgBufVFSE.h"
#include "include/BaseDefs.h"
#include "include/Struct_CAN.h"
#include "include/Struct_LIN.h"

typedef CBaseMsgBufFSE<STCANDATA> CBaseCANBufFSE;
typedef CMsgBufFSE<STCANDATA> CCANBufFSE;
typedef CMsgBufFSE<STLINDATA> CLINBufFSE;
typedef CMsgBufVFSE<STJ1939_MSG> CJ1939BufVFSE;
typedef CBaseMsgBufFSE<STLINDATA> CBaseLINBufFSE;
typedef CBaseMsgBufFSE<s_FLXMSG> CBaseFLEXBufFSE;
typedef CMsgBufFSE<s_FLXMSG> CFLEXBufFSE;

#endif  // KERNEL_UTILITIES_MSGBUFALL_DATATYPES_H_