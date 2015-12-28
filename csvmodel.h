#ifndef CSVMODEL_H
#define CSVMODEL_H

#include <QAbstractTableModel>
#include "csvtablerepresentation.h"

class CSVTableRepresentation;

class CSVModel:public QAbstractTableModel
{
public:
    CSVModel(CSVTableRepresentation* repr, QObject *parent);
    CSVTableRepresentation* getRepresentation();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void SetColumnToAdd(CellTypeData toAdd);

    bool insertRow(int row, const QModelIndex &parent);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRow(int row, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    bool insertColumn(int column, const QModelIndex &parent);
    bool insertColumns(int column, int count, const QModelIndex &parent);
    bool removeColumn(int column, const QModelIndex &parent);
    bool removeColumns(int column, int count, const QModelIndex &parent);

    bool setData(const QModelIndex &index, const QVariant &value, int role);    

    CSVTableRepresentation* repr_;
    CellTypeData columnToAdd;
};

#endif // CSVMODEL_H
