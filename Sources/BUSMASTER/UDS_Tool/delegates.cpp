#include "delegates.h"

Delegates::Delegates(QObject *parent)
    : QItemDelegate{parent}
{

}

QWidget *Delegates::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void Delegates::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString inputText = index.model()->data(index,Qt::EditRole).toString();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(inputText);
}

void Delegates::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString inputText = lineEdit->text();
    model->setData(index,inputText,Qt::EditRole);
}

void Delegates::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
