#ifndef DELEGATES_H
#define DELEGATES_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QLineEdit>

class Delegates : public QItemDelegate
{
    Q_OBJECT
public:
    explicit Delegates(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATES_H

