#ifndef BUSMASTER_LDFEDITOR_ABOUTLDFEDITOR_H_
#define BUSMASTER_LDFEDITOR_ABOUTLDFEDITOR_H_

#include <QDialog>

#include "ui_AboutLDFEditor.h"

class AboutLDFEditor : public QDialog {
  Q_OBJECT
 public:
  AboutLDFEditor(QWidget* parent = 0);
  ~AboutLDFEditor();

 private:
  Ui::AboutLDFEditor ui;
};

#endif  // BUSMASTER_LDFEDITOR_ABOUTLDFEDITOR_H_