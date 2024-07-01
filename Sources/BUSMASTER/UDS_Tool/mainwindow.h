#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCore>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include "delegates.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class QAction;
class QToolBar;
class QComboBox;
class QLabel;
class QPushButton;
class QTreeView;
class QTableView;
class QSplitter;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMap<QString,QList<QString>> *namesMap;
    QMap<QString,QList<QList<QString>>> *dataMap;

    QStandardItemModel *tableModel;
    QStandardItemModel *treeModel;

    Delegates *tableDelegate;

    QAction *firstAction;
    QAction *secndAction;
    QAction *thirdAction;
    QAction *fourthAction;
    QAction *fifthAction;

    QComboBox *firstComboBox;
    QLabel *uniqueLabel;
    QComboBox *secondComboBox;
    QPushButton *executeButton;

    QSplitter *hSplitter;
    QSplitter *vSplitter;

    QTreeView *treeView;
    QTableView *dataTable;
    QTableView *detailsTable;

    void createActions();
    void createToolBar();

private slots:
    void treeChild_selection(const QItemSelection &selected, const QItemSelection &deselected);
    void childComboBoxSelection(int index);

};
#endif // MAINWINDOW_H
