#ifndef BUSMASTER_LDFEDITOR_SPORADICFRAMEEDITDLG_H_
#define BUSMASTER_LDFEDITOR_SPORADICFRAMEEDITDLG_H_

#include <QDialog>

#include "Defines.h"
#include "ICluster.h"
#include "ui_SporadicFrameEditDlg.h"

class SporadicFrameEditDlg : public QDialog {
  Q_OBJECT
 public:
  SporadicFrameEditDlg(IFrame** pouFrame, eMode ouMode, QWidget* parent = 0);
  ~SporadicFrameEditDlg(void);

 private:
  IFrame** m_pouFrame;
  eMode m_ouMode;
  std::map<std::string, std::string> m_strFrameNames;
  ICluster* m_pLdfCluster;

 private:
  void vPrepareUIForEditMode();
  void vAddFrameToTable(IFrame* pFrame,
                        std::map<UID_ELEMENT, UID_ELEMENT> ouSelectedElements);
  int nValidateValues();

 private:
  Ui::SporadicFrameEditDlg ui;
  void vPrepareValidations();
  void vFillElementList();
 private slots:
  void OnButtonClickOk();
};

#endif  // BUSMASTER_LDFEDITOR_SPORADICFRAMEEDITDLG_H_