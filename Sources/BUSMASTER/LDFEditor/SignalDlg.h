#ifndef BUSMASTER_LDFEDITOR_SIGNALDLG_H_
#define BUSMASTER_LDFEDITOR_SIGNALDLG_H_

#include <QDialog>

#include "ICluster.h"
#include "ui_SignalDlg.h"

#define defEcuIndex 0
#define defSignalIndex 1
#define defCodingIndex 2
#define defTotalElement 3

class SignalDlg : public QDialog {
  Q_OBJECT

 private:
  UID_ELEMENT m_unExistingCoidngUid;
  ICluster* m_pLdfCluster;
  bool m_bEditMode;
  ISignal** m_pSignal;
  QString m_strCurrentPublisher;
  std::map<std::string, UID_ELEMENT> m_ouElementMap[eAllElement];
  int m_nActualLength;
 private slots:
  void onSelectionOk();
  void onSelecetionCancel();

 public:
  SignalDlg(ICluster* pouCluster, ISignal** pSignal, bool bNew,
            QWidget* parent = nullptr);
  ~SignalDlg();

 private:
  void vPrepareUiForEditMode();
  void vPrepareUiForNewMode();
  void vPrepareValidations();
  void vFillElementList();
  void vFillSignalDetails();

 private:
  Ui::SignalDlg ui;
};

#endif  // BUSMASTER_LDFEDITOR_SIGNALDLG_H_
