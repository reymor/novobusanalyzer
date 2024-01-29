#ifndef BUSMASTER_LDFEDITOR_LDFCLUSTERPROPSDLG_H_
#define BUSMASTER_LDFEDITOR_LDFCLUSTERPROPSDLG_H_

#include <QDialog>

#include "ICluster.h"
#include "ui_LDFCLusterPropsDlg.h"

class LDFCLusterPropsDlg : public QDialog {
  Q_OBJECT
 private:
  ICluster* m_pCluster;

 public:
  LDFCLusterPropsDlg(ICluster* pCluster, QWidget* parent = 0);
  ~LDFCLusterPropsDlg();

 private:
  void vPrepareUi();
 private slots:
  void OnSelectOk();

 private:
  Ui::LDFCLusterPropsDlg ui;
};

#endif  // BUSMASTER_LDFEDITOR_LDFCLUSTERPROPSDLG_H_