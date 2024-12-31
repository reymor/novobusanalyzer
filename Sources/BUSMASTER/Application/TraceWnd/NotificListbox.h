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
 * \file      Application/TraceWnd/NotificListbox.h
 * \brief     Interface file for CNotificListbox class
 * \author    Ravikumar Patil
 * \copyright Copyright (c) 2011, Robert Bosch Engineering and Business Solutions. All rights reserved.
 *
 * Interface file for CNotificListbox class
 */

#ifndef BUSMASTER_APPLICATION_TRACEWND_NOTIFICLISTBOX_H_
#define BUSMASTER_APPLICATION_TRACEWND_NOTIFICLISTBOX_H_

class CNotificListbox : public CListBox {
public:
    CNotificListbox();
    virtual ~CNotificListbox();

protected:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTraceWndClear();
    afx_msg void OnTraceWndDelete();

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnNotificwndSelectall();
    afx_msg void OnNotificwndCopytoclipboard();
};

#endif // BUSMASTER_APPLICATION_TRACEWND_NOTIFICLISTBOX_H_
