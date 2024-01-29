#ifndef BUSMASTER_LDFEDITOR_LDFTABLEWIDGET_H_
#define BUSMASTER_LDFEDITOR_LDFTABLEWIDGET_H_

#include <QTableWidget>

class LDFTableWidget : public QTableWidget {
  Q_OBJECT
 private:
  QFont m_ldfFont;

 public:
  LDFTableWidget(QWidget* parent = 0);
  ~LDFTableWidget();
};

#endif  // BUSMASTER_LDFEDITOR_LDFTABLEWIDGET_H_