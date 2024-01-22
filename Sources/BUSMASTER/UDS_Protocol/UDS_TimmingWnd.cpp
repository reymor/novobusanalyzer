// UDS_TimmingWnd.cpp: archivo de implementaci�n

// clang-format off
#include "stdafx.h"
// clang-format on

#include "UDS_TimmingWnd.h"

#include "UDS_Resource.h"

IMPLEMENT_DYNAMIC(CUDS_TimmingWnd, CDialog)

CUDS_TimmingWnd::CUDS_TimmingWnd(CWnd* pParent)
    : CDialog(CUDS_TimmingWnd::IDD, pParent) {}

CUDS_TimmingWnd::~CUDS_TimmingWnd() {}

void CUDS_TimmingWnd::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUDS_TimmingWnd, CDialog)
END_MESSAGE_MAP()