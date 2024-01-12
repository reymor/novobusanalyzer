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
 * \brief     Source script for NovoBusAnalyzer Clean Registry
 * \author    Saravanan K S
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions.  All rights reserved.
 * \date      27/03/2013
 *
 * Source script for NovoBusAnalyzer Clean Registry
 */

/**
 * \notice This file has been changed to rename from BusMaster to NovoBusAnalyzer
 * \date 12/01/2024
 */

!include "NSISHeaders.nsh"

RequestExecutionLevel user

; Title of this installation
Name "NovoBusAnalyzer Registry Cleanup"

; Do a CRC check when initializing setup
CRCCheck On

; Output filename
Outfile "NovoBusAnalyzer_Cleanup_Registry.exe"

SectionGroup "Main"

Section "NovoBusAnalyzer"
	IfFileExists Software\NovoBusAnalyzer_v${VERSION} bRegEntryMruExists
	 bRegEntryMruExists:
	 DeleteRegKey HKCU "Software\NovoBusAnalyzer_v${VERSION}\NovoBusAnalyzer"
	 DeleteRegKey HKCU "Software\NovoBusAnalyzer_v${VERSION}\Files"
	 DeleteRegKey HKCU "Software\NovoBusAnalyzer_v${VERSION}\MainWnd"
SectionEnd
SectionGroupEnd