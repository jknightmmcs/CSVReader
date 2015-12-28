#include "comboboxdelegate.h"
#include <QComboBox>
#include <csvmodel.h>

ComboBoxItemDelegate::ComboBoxItemDelegate(std::vector<QString> items, QObject* parent)
    : QStyledItemDelegate(parent)
{
    this->items_ = items;
}


ComboBoxItemDelegate::~ComboBoxItemDelegate()
{
}


QWidget* ComboBoxItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    CSVModel* model = (CSVModel*)(index.model());
    QString data = model->repr_->getData(index.row(), index.column()).toString();    
    // Create the combobox and populate it
    QComboBox* cb = new QComboBox(parent);
    cb->setFrame(false);
    int ind = 0;
    for(int i = 0; i < items_.size(); i++)
    {
        cb->addItem(items_[i]);

        if (items_[i].toLower() == data.toLower())
            ind = i;
    }
    cb->setCurrentIndex(ind);
    return cb;
}


void ComboBoxItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
       // get the index of the text in the combobox that matches the current value of the itenm
       QString currentText = index.data(Qt::EditRole).toString();
       int cbIndex = cb->findText(currentText);
       // if it is valid, adjust the combobox
       if (cbIndex >= 0)
           cb->setCurrentIndex(cbIndex);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}


void ComboBoxItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor))
        // save the current text of the combo box as the current value of the item
        model->setData(index, cb->currentText(), Qt::EditRole);
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}
