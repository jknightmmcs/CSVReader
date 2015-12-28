#include "textboxdelegate.h"
#include <csvmodel.h>
#include <QLineEdit>

TextBoxDelegate::TextBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *TextBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &index) const
{
    CSVModel* model = (CSVModel*)(index.model());
    QString data = index.data().toString();
    QLineEdit *editor = new QLineEdit(data, parent);
    return editor;
}

void TextBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.data().toString();

    QLineEdit *textEdit = static_cast<QLineEdit*>(editor);
    textEdit->setText(value);
}

void TextBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QLineEdit *textEdit = static_cast<QLineEdit*>(editor);
    QString value = textEdit->text();

    model->setData(index, value, Qt::EditRole);
}
