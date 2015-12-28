#ifndef TEXTBOXDELEGATE_H
#define TEXTBOXDELEGATE_H

#include <QStyledItemDelegate>

class TextBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TextBoxDelegate(QObject* parent=0);

    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
};
#endif // TEXTBOXDELEGATE_H
