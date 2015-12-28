#ifndef CSVTABLEREPRESENTATION_H
#define CSVTABLEREPRESENTATION_H
#include <vector>
#include <string>
#include <QString>
#include <QVariant>
#include "csvmodel.h"

using std::string;

enum CellType { TypeString, TypeBool, TypeInt, TypeEnum };

inline QString TypeToString(CellType type)
{
    switch(type)
    {
    case TypeString: return "String";
    case TypeBool: return "bool";
    case TypeInt: return "int";
    case TypeEnum: return "enum";
    default: return "unknown";
    }
}

class CellTypeData
{
public:
    CellType type;
    std::vector<QString> data; //for enum    
    QVariant defaultValue;
};

class CSVModel;

class CSVTableRepresentation
{
public:
    CSVTableRepresentation();    
    static CSVTableRepresentation *LoadFromFile(QString fname);
    QVariant getData(int row, int column);

    std::vector<CellTypeData> header;
    std::vector<std::vector<QVariant>> data;

    friend class CSVModel;    
};

#endif // CSVTABLEREPRESENTATION_H
