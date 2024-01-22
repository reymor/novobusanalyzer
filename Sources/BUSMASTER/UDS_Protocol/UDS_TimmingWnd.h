#ifndef BUSMASTER_UDS_PROTOCOL_UDS_TIMMINGWND_H_
#define BUSMASTER_UDS_PROTOCOL_UDS_TIMMINGWND_H_

#include "UDS_Resource.h"

class CUDS_TimmingWnd : public CDialog {
  DECLARE_DYNAMIC(CUDS_TimmingWnd)

 public:
  CUDS_TimmingWnd(CWnd* pParent = NULL);
  virtual ~CUDS_TimmingWnd();

  enum { IDD = IDD_TIMMING_UDS };

 protected:
  // DDX/DDV Compatibility
  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
};

#endif  // BUSMASTER_UDS_PROTOCOL_UDS_TIMMINGWND_H_