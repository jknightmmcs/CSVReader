#include "csvreader.h"
#include "ui_csvreader.h"
#include <comboboxdelegate.h>
#include <spinboxdelegate.h>


CSVReader::CSVReader(CSVModel* model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSVReader)
{
    ui->setupUi(this);
    ui->tableView->setModel(model);        
    CSVTableRepresentation* repr = model->getRepresentation();
    for(int i = 0; i < repr->header.size(); i++)
    {
        std::vector<QString> items;
        switch (repr->header[i].type)
        {
        case CellType::TypeBool:
            items.push_back("False");
            items.push_back("True");
            ui->tableView->setItemDelegateForColumn(i, new ComboBoxItemDelegate(items, ui->tableView));
            break;
        case CellType::TypeInt:
            ui->tableView->setItemDelegateForColumn(i, new SpinBoxDelegate(ui->tableView));
            break;
        case CellType::TypeString:
            break;
        case CellType::TypeEnum:
            for(int j = 0; j < repr->header[i].data.size(); j++)
                items.push_back(repr->header[i].data[j]);
            ui->tableView->setItemDelegateForColumn(i, new ComboBoxItemDelegate(items, ui->tableView));
            break;
        }
    }
    ui->tableView->resizeColumnsToContents();    

}

CSVReader::~CSVReader()
{
    delete ui;
}
