#ifndef BUSMASTER_LDFEDITOR_MASTEREDITDLG_H_
#define BUSMASTER_LDFEDITOR_MASTEREDITDLG_H_

#include <QDialog>

#include "ICluster.h"
#include "ui_MasterEditDlg.h"

class MasterEditDlg : public QDialog {
  Q_OBJECT
 private:
  IEcu* m_pouMasterEcu;

 public:
  MasterEditDlg(IEcu* pouMasterEcu, QWidget* parent = 0);
  ~MasterEditDlg();

 private:
  void SetUpUi();

 private:
  Ui::Dialog ui;
 public slots:
  void OnOk();
  void OnCancel();
};

#endif  // BUSMASTER_LDFEDITOR_MASTEREDITDLG_H_
