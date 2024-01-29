#ifndef BUSMASTER_LDFEDITOR_SCHEDULECOMBOWIDGET_H_
#define BUSMASTER_LDFEDITOR_SCHEDULECOMBOWIDGET_H_

#include <QComboBox>

#include "LINDefines.h"

class ScheduleComboWidget : public QComboBox {
  Q_OBJECT
 public:
  ScheduleComboWidget(int nRow, QWidget* parent = 0);
  ~ScheduleComboWidget();

 private:
  int m_nRow;

 signals:
  void onScheduleComboChange(int nRow, int nIndex);

 private slots:
  void onComboSelectionChange(int nIndex);
};

#endif  // BUSMASTER_LDFEDITOR_SCHEDULECOMBOWIDGET_H_
