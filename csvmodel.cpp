#include "csvmodel.h"

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
}


Qt::ItemFlags CSVModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
