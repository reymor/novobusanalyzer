#ifndef BUSMASTER_UDS_PROTOCOL_UDS_SETTINGSWND_H_
#define BUSMASTER_UDS_PROTOCOL_UDS_SETTINGSWND_H_

#include "UDS_Resource.h"

class CUDS_SettingsWnd : public CDialog {
  DECLARE_DYNAMIC(CUDS_SettingsWnd)

 public:
  CUDS_SettingsWnd(CWnd* pParent = NULL);
  virtual ~CUDS_SettingsWnd();

  enum { IDD = IDM_UDS };

 protected:
  // DDX/DDV Compatibility
  virtual void DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
};

#endif  // BUSMASTER_UDS_PROTOCOL_UDS_SETTINGSWND_H_