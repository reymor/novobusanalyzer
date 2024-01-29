#ifndef BUSMASTER_LDFEDITOR_SIGNALGROUPDLG_H_
#define BUSMASTER_LDFEDITOR_SIGNALGROUPDLG_H_

#include <QDialog>

#include "ICluster.h"
#include "ui_SignalGroupDlg.h"

class SignalGroupDlg : public QDialog {
  Q_OBJECT
 private:
  ICluster* m_pLdfCluster;
  bool m_bEditMode;
  ISignalGroup** m_pSignalGroup;
  QString m_strCurrentPublisher;
  std::map<std::string, UID_ELEMENT> m_ouExistingNameMap;
  int m_nActualLength;

 private slots:
  void onSelectionOk();

 public:
  SignalGroupDlg(ICluster* pouCluster, ISignalGroup** pouEcu, bool bNew,
                 QWidget* parent);
  ~SignalGroupDlg();

 private:
  void vPrepareUiForEditMode();
  void vPrepareUiForNewMode();
  void vPrepareValidations();
  void vFillExistingNameList();
  int nValidate();

 private:
  Ui::SignalGroupDlg ui;
};

#endif  // BUSMASTER_LDFEDITOR_SIGNALGROUPDLG_H_
