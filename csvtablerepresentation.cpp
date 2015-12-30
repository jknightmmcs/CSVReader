#include "csvtablerepresentation.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QString>

CSVTableRepresentation::CSVTableRepresentation()
{

}

QVariant ConvertToQVariant(QString str, CellTypeData type, bool* check = nullptr)
{
    bool ok; int val;
    switch (type.type)
    {
    case CellType::TypeBool:
        if (str == "true")
            return QVariant(true);
        else
            return QVariant(false);
        break;
    case CellType::TypeInt:
        ok = false;
        val = str.toInt(&ok);
        if (ok)
            return QVariant(val);
        else { if (check != nullptr) *check = false; return QVariant(0); }
        break;
    case CellType::TypeString:
        return QVariant(str);
        break;
    case CellType::TypeEnum:
        if (std::find(type.data.begin(), type.data.end(), str) != type.data.end())
            return QVariant((int)(std::find(type.data.begin(), type.data.end(), str) - type.data.begin()));
        else
            { if (check != nullptr) *check = false; return QVariant(-1); }
    }
    return QVariant();
}

CSVTableRepresentation* CSVTableRepresentation::LoadFromFile(QString fname)
{
    CSVTableRepresentation* repr = new CSVTableRepresentation();

    QFile file(fname);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString types = in.readLine();
    QStringList typesList = types.split(";");
    for(int i = 0; i < typesList.size(); i++)
    {
        CellTypeData cell;
        if (typesList[i] == "string")
        {
            cell.type = CellType::TypeString;
            cell.defaultValue = "";
        }
        else if (typesList[i] == "bool")
        {
            cell.type = CellType::TypeBool;
            cell.defaultValue = false;
        }
        else if (typesList[i] == "int")
        {
            cell.type = CellType::TypeInt;
            cell.defaultValue = 0;
        }
        else if (typesList[i].toStdString().substr(0, 4) == "enum")
        {
            cell.type = CellType::TypeEnum;
            QStringList enumList = typesList[i].split(":");
            for(int j = 1; j < enumList.size(); j++)
                cell.data.push_back(enumList[j]);
            cell.defaultValue = 0;
        }
        repr -> header.push_back(cell);
        repr->fname = fname;
    }

    int line_num = 0;
    while(!in.atEnd())
    {
        QStringList line = in.readLine().split(";");
        repr->data.push_back(std::vector<QVariant>());
        for(int i = 0; i < line.size(); i++)
        {
            repr->data[line_num].push_back(ConvertToQVariant(line[i], repr -> header[i]));
        }
        line_num++;
    }

    return repr;
}

QVariant CSVTableRepresentation::getData(int row, int column)
{    
    if (this->header[column].type == CellType::TypeEnum)
    {
        return this->header[column].data[data[row][column].toInt()];
    }
    else
        return this->data[row][column];
}

void CSVTableRepresentation::Save()
{
    QFile f(this->fname);
    f.open(QIODevice::WriteOnly);
    QTextStream sf(&f);

    QStringList headerList;
    for(int i = 0; i < this->header.size(); i++)
    {
        switch (this->header[i].type)
        {
        case CellType::TypeBool:
            headerList.push_back("bool");
            break;
        case CellType::TypeInt:
            headerList.push_back("int");
            break;
        case CellType::TypeString:
            headerList.push_back("string");
            break;
        case CellType::TypeEnum:
            QStringList enumList;
            enumList.push_back("enum");
            for(int j = 0; j < header[i].data.size(); j++)
                enumList.push_back(header[i].data[j]);
            QString str = enumList.join(":");
            headerList.push_back(str);
            break;
        }
    }
    sf << headerList.join(";") << endl;

    for(int i = 0; i < this->data.size(); i++)
    {
        QStringList list;
        for(int j = 0; j < this->header.size(); j++)
        {
            if (this->header[j].type != CellType::TypeEnum)
            {
                list.push_back(this->data[i][j].toString());
            }
            else
            {
                list.push_back(this->header[j].data[this->data[i][j].toInt()]);
            }
        }
        sf << list.join(";") << endl;
    }
}
