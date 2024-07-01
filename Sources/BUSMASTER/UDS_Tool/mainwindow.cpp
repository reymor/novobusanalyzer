#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <QtCore>
#include <QList>
#include <QDesktopWidget>
#include <QAction>
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // QMap with data to use as placeholders:
    namesMap = new QMap<QString, QList<QString>>;
    namesMap->insert("Parent #1", {"Child 1-1", "Child 1-2", "Child 1-3"});
    namesMap->insert("Parent #2", {"Child 2-1", "Child 2-2"});
    namesMap->insert("Parent #3", {"Child 3-1"});

    dataMap = new QMap<QString,QList<QList<QString>>>;
    dataMap->insert("Child 1-1", {{"Name 1", "00000000000000", "1-1"},{"Name 2", "00000000000000", "0"}});
    dataMap->insert("Child 1-2", {{"Name 1", "00000000000000", "1-2"},{"Name 2", "00000000000000", "0"}});
    dataMap->insert("Child 1-3", {{"Name 1", "00000000000000", "1-3"},{"Name 2", "00000000000000", "0"}});
    dataMap->insert("Child 2-1", {{"Name 1", "00000000000000", "2-1"},{"Name 2", "00000000000000", "0"}});
    dataMap->insert("Child 2-2", {{"Name 1", "00000000000000", "2-2"},{"Name 2", "00000000000000", "0"}});
    dataMap->insert("Child 3-1", {{"Name 1", "00000000000000", "3-1"},{"Name 2", "00000000000000", "0"}});

    /*******************************************************************************************************/

    ui->setupUi(this);

    // Setting the delegate for the tableview
    tableDelegate = new Delegates(this);

    // Setting the table model
    tableModel = new QStandardItemModel(3,3,this);
    tableModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    tableModel->setHeaderData(1, Qt::Horizontal, tr("Value"));
    tableModel->setHeaderData(2, Qt::Horizontal, tr("Unit"));

    // Setting the treeview model
    treeModel = new QStandardItemModel(this);
    QStandardItem *root = treeModel->invisibleRootItem();

    QList<QStandardItem*> rowItems;
    QMap<QString,QList<QString>>::iterator iter;
    for (iter = namesMap->begin(); iter != namesMap->end(); ++iter) // Iterating through namesMap data
    {
        QString parentName = QString(iter.key());
        QStandardItem *parent = new QStandardItem(parentName);
        parent->setEditable(false);
        rowItems << parent;
        root->appendRow(rowItems);
        rowItems.clear();

        QListIterator<QString> i(iter.value());
        while (i.hasNext())
        {
            QString childName = QString(i.next());
            QStandardItem *item = new QStandardItem(childName);
            item->setEditable(false);
            rowItems << item;
            parent->appendRow(rowItems);
            rowItems.clear();
        }
    }

    // treeModel->setHeaderData(0, Qt::Horizontal, tr("Name"));
    // treeModel->setHeaderData(1, Qt::Horizontal, tr("Data"));


    // setting a small comboBox
    firstComboBox = new QComboBox(this);
    firstComboBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed); // the ComboBox wont strech or shrink with the window

    firstComboBox->addItem(tr("Option 1"));
    firstComboBox->addItem(tr("Option 2"));

    // setting a Label
    uniqueLabel = new QLabel(this);
    // Label configuration
    uniqueLabel->setText("UniqueLabel");
    uniqueLabel->setAlignment(Qt::AlignRight);
    uniqueLabel->setFrameShape(QFrame::WinPanel);
    uniqueLabel->setFrameShadow(QFrame::Sunken);


    // Setting a Long comboBox
    secondComboBox = new QComboBox(this);

    // Adding items to the ComboBox from a QMap
    QMap<QString, QList<QString>>::iterator it;
    for (it = namesMap->begin(); it != namesMap->end(); ++it)
    {
        QListIterator<QString> i(it.value()); // iterating through the Qlist
        while (i.hasNext())
        {
            secondComboBox->addItem(i.next());
        }
    }


    // Setting a the execute button
    executeButton = new QPushButton("&Execute", this);
    executeButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed); // the button wont strech or shrink with the window


    // setting an horizontal splitter
    hSplitter = new QSplitter(this);
    hSplitter->setOrientation(Qt::Vertical);

    // setting the two Table Views
    dataTable = new QTableView(this);
    dataTable->setFrameShape(QFrame::WinPanel);
    dataTable->setFrameShadow(QFrame::Sunken);

    dataTable->setModel(tableModel); // setting the model for the data table
    dataTable->verticalHeader()->setVisible(false);
    dataTable->setShowGrid(false);
    dataTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    dataTable->setItemDelegate(tableDelegate); // setting the delegate for the data table

    detailsTable = new QTableView(this);
    detailsTable->setFrameShape(QFrame::WinPanel);
    detailsTable->setFrameShadow(QFrame::Sunken);

    // adding two widgets to the splitter layout
    hSplitter->addWidget(dataTable);
    hSplitter->addWidget(detailsTable);

    // setting a vertical splitter
    vSplitter = new QSplitter(this);
    // setting a treeView
    treeView = new QTreeView(this);
    treeView->setFrameShape(QFrame::WinPanel);
    treeView->setFrameShadow(QFrame::Sunken);
    treeView->setHeaderHidden(true);

    treeView->setModel(treeModel); // setting the model for the treeView


    // setting the treeView and hSplitter to the vertical splitter
    vSplitter->addWidget(treeView);
    vSplitter->addWidget(hSplitter);
    // setting the size of the vsplitter
    QList<int> splittrSize = {100,200};
    vSplitter->setSizes(splittrSize);

    // Setting the layout of the widgets on a grid layout
    QGridLayout *glayout1 = new QGridLayout;
    glayout1->addWidget(firstComboBox,0,0,1,1);
    glayout1->addWidget(uniqueLabel,0,1,1,6);
    glayout1->addWidget(secondComboBox,1,0,1,6);
    glayout1->addWidget(executeButton,1,6,1,1);
    glayout1->addWidget(vSplitter,2,0,1,7);
    // glayout1->setContentsMargins(0,0,0,0);
    // glayout1->setSpacing(5);
    glayout1->setHorizontalSpacing(10);
    glayout1->setVerticalSpacing(2);

    // set layout in QWindow
    QWidget *window = new QWidget;
    window->setLayout(glayout1);

    setCentralWidget(window);
    setWindowTitle(tr("Diagnostics"));
    ui->statusbar->hide();


    // To populate the Tableview with data through the combobox:
    connect(secondComboBox, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::childComboBoxSelection);

    // To populate the Tableview with data through the treeView:
    QItemSelectionModel *selectionModel = treeView->selectionModel(); // selection changes shall trigger a slot
    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &MainWindow::treeChild_selection);


    // Function createActions and createToolBar will set the toolbar and its icons.
    createActions();
    createToolBar();

}

void MainWindow::createActions()
{
    firstAction = new QAction(tr("&First"), this);
    firstAction->setIcon(QIcon(":/Images/monitor.png"));

    secndAction = new QAction(tr("&Second"), this);
    secndAction->setIcon(QIcon(":/Images/network.png"));

    thirdAction = new QAction(tr("&Third"), this);
    thirdAction->setIcon(QIcon(":/Images/history.png"));

    fourthAction = new QAction(tr("&Fourth"), this);
    fourthAction->setIcon(QIcon(":/Images/cross.png"));

    fifthAction = new QAction(tr("&Fifth"), this);
    fifthAction->setIcon(QIcon(":/Images/binocular.png"));
}

void MainWindow::createToolBar()
{
    QToolBar *dToolBar = addToolBar(tr("Diagnostics")); // toolBar defined here
    dToolBar->addAction(firstAction);
    dToolBar->addSeparator();
    dToolBar->addAction(secndAction);
    dToolBar->addSeparator();
    dToolBar->addAction(thirdAction);
    dToolBar->addAction(fourthAction);
    dToolBar->addSeparator();
    dToolBar->addAction(fifthAction);

}

void MainWindow::treeChild_selection(const QItemSelection &/*selected*/, const QItemSelection &/*deselected*/)
{
    // to get the text of the selected item
    const QModelIndex index = treeView->selectionModel()->currentIndex();
    QString selectedLeaf = index.data(Qt::DisplayRole).toString();

    // iterating though the Qmap data to find the rows correspondig to the selected item
    QMap<QString,QList<QList<QString>>>::iterator itr;
    for (itr = dataMap->begin(); itr != dataMap->end(); ++itr)
    {
        if (itr.key() == selectedLeaf)
        {
            int row = 0;
            // iterating through the Qlist
            QListIterator<QList<QString>> i(itr.value());
            while (i.hasNext())
            {
                QList list = i.next();
                for (int col = 0; col < list.size(); ++col)
                {
                    QModelIndex index = tableModel->index(row, col, QModelIndex());
                    tableModel->setData(index, list.at(col));
                }
                ++row;
            }
        }
        // if a parent item is selected the table is cleared
        if (selectedLeaf == "Parent #1" || selectedLeaf == "Parent #2" || selectedLeaf == "Parent #3")
        {
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    QModelIndex index2 = tableModel->index(row, col, QModelIndex());
                    // tableModel->setData(index2, tr(""));
                    tableModel->clearItemData(index2);
                }
            }
        }
    }

}

void MainWindow::childComboBoxSelection(int index)
{
    // to get the text of the selected item
    QString child_selected = secondComboBox->itemData(index, Qt::DisplayRole).toString();

    QMap<QString,QList<QList<QString>>>::iterator itr;
    for (itr = dataMap->begin(); itr != dataMap->end(); ++itr)
    {
        // Next is to get the match between the combobox item and the tree model data
        QModelIndexList matches = treeModel->match(
            treeModel->index(0,0,QModelIndex()),
            Qt::DisplayRole,
            child_selected,
            1,
            Qt::MatchFlags(Qt::MatchExactly|Qt::MatchRecursive));

        if (matches.count() == 1)
        {
            const QModelIndex item_selected = matches.at(0);
            treeView->scrollTo(item_selected,QAbstractItemView::EnsureVisible); // making the child item in the tree visible
        }

        // to populate the table with the row data
        if (itr.key() == child_selected)
        {
            int row = 0;
            // iterating through the Qlist
            QListIterator<QList<QString>> i(itr.value());
            while (i.hasNext())
            {
                QList list = i.next();
                for (int col = 0; col < list.size(); ++col)
                {
                    QModelIndex qmodel_index = tableModel->index(row, col, QModelIndex());
                    tableModel->setData(qmodel_index, list.at(col));
                }
                ++row;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
