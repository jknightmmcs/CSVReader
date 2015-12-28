#include "csvmodel.h"
#include <QMessageBox>
#include <iostream>

CSVModel::CSVModel(CSVTableRepresentation *repr, QObject* parent = 0):QAbstractTableModel(parent)
{
    this->repr_ = repr;
}

CSVTableRepresentation *CSVModel::getRepresentation()
{
    return this->repr_;
}

int CSVModel::rowCount(const QModelIndex &parent) const
{
    return repr_->data.size();
}

int CSVModel::columnCount(const QModelIndex &parent) const
{
    return repr_->header.size();
}

QVariant CSVModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        if (repr_->header[index.column()].type != CellType::TypeEnum)
            return repr_->data[index.row()][index.column()];
        else
        {
            int data_index = repr_->data[index.row()][index.column()].toInt();
            return QVariant(repr_->header[index.column()].data[data_index]);
        }
    else return QVariant::Invalid;
}

QVariant CSVModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant::Invalid;
    if (orientation == Qt::Horizontal)
    {
        return QString("%1:%2").arg(QString::number(section), TypeToString(repr_->header[section].type));
    }
    else
    {
        return QString("%1").arg(QString::number(section));
    }
}

bool CSVModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;
    int col = index.column();
    int row = index.row();
    QString data = value.toString();

    switch(repr_->header[col].type)
    {
    case CellType::TypeBool:
        if (data == "False")
            repr_->data[row][col] = QVariant(false);
        else repr_->data[row][col] = QVariant(true);
        break;
    case CellType::TypeInt:
        repr_->data[row][col] = QVariant(data.toInt());
        break;
    case CellType::TypeString:
        repr_->data[row][col] = QVariant(data);
        break;
    case CellType::TypeEnum:
        std::vector<QString>& headers = repr_->header[col].data;
        int ind = std::find(headers.begin(), headers.end(), data) - headers.begin();
        repr_->data[row][col] = QVariant(ind);
        break;
    }
    return true;
}


Qt::ItemFlags CSVModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CSVModel::insertRow(int row, const QModelIndex &parent)
{
    return insertRows(row, 1, parent);
}

bool CSVModel::insertRows(int row, int count, const QModelIndex &parent)
{
    using namespace std;
    beginInsertRows(parent, row, row + count - 1);
    for(int i = row; i < row + count; i++)
    {
        std::vector<QVariant> newRow;
        for(int i = 0; i < repr_->header.size(); i++)
            newRow.push_back(repr_->header[i].defaultValue);
        repr_->data.insert(repr_->data.begin() + i, newRow);
    }
    endInsertRows();
    emit dataChanged(index(0, 0), index(rowCount(parent), columnCount(parent)));
    emit layoutChanged();
    return true;
}

bool CSVModel::removeRow(int row, const QModelIndex &parent)
{
    removeRows(row, 1, parent);
}

bool CSVModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for(int i = row; i < row + count; i++)
    {
        repr_->data.erase(repr_->data.begin() + i);
    }
    endRemoveRows();
    emit dataChanged(index(0, 0), index(rowCount(parent), columnCount(parent)));
    emit layoutChanged();
    return true;
}

bool CSVModel::insertColumn(int column, const QModelIndex &parent)
{
    QMessageBox::about(0, "insertcolumn", "insertcolumn");
}

bool CSVModel::removeColumn(int column, const QModelIndex &parent)
{
    QMessageBox::about(0, "removecolumn", "removecolumn");
}
