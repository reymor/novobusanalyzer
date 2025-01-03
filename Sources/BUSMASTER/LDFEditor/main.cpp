#include <QtWidgets/QApplication>

#include "ldfeditor.h"

int main(int argc, char* argv[]) {

  QApplication a(argc, argv);
  std::string omstrLDFFile = "";
  if (argc > 1) {
    omstrLDFFile = argv[1];
  }
  LDFEditor w(omstrLDFFile);
  w.showMaximized();

  return a.exec();
}