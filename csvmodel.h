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
    //virtual bool insertRow(int row, const QModelIndex &parent);
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    CSVTableRepresentation* repr_;
};

#endif // CSVMODEL_H