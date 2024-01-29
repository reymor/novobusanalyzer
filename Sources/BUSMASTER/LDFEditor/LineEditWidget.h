#ifndef BUSMASTER_LDFEDITOR_LINEEDITWIDGET_H_
#define BUSMASTER_LDFEDITOR_LINEEDITWIDGET_H_

#include <QLineEdit>

#include "LINDefines.h"

class QTableWidget;
class LineEditWidget : public QLineEdit {
  Q_OBJECT
 public:
  LineEditWidget(int nRow, QTableWidget* parent = 0);
  ~LineEditWidget();

 private:
  int m_nRow;
  QTableWidget* m_pTableWidget;

 protected:
  virtual void mousePressEvent(QMouseEvent*);
};

#endif  // BUSMASTER_LDFEDITOR_LINEEDITWIDGET_H_
