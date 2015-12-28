#include "csvreader.h"
#include "ui_csvreader.h"
#include <comboboxdelegate.h>
#include <spinboxdelegate.h>
#include <textboxdelegate.h>
#include <algorithm>

CSVReader::CSVReader(CSVModel* model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSVReader)
{
    ui->setupUi(this);
    this->model = model;
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
            ui->tableView->setItemDelegateForColumn(i, new TextBoxDelegate(ui->tableView));
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

void CSVReader::on_actionLeft_triggered()
{

}

void CSVReader::on_actionRemove_selected_triggered()
{

}

void CSVReader::on_actionRemove_selected_2_triggered()
{    
    auto selected = ui->tableView->selectionModel()->selectedRows();
    for(int i = 0; i < selected.size(); i++)
        model->removeRow(selected[i].row(), selected[i]);
}

void CSVReader::on_actionHigher_triggered()
{
    auto select = ui->tableView->selectionModel();
    auto selected = select -> selectedRows();
    if (selected.size() == 0)
        model->insertRow(0, QModelIndex());
    else if (selected.at(0).row() == 0)
        model->insertRow(0, selected[0]);
    else
        model->insertRow(selected.at(0).row(), selected[0]);
}

void CSVReader::on_actionLower_triggered()
{
    auto selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.size() == 0)
        model->insertRow(model->rowCount(QModelIndex()), QModelIndex());
    else
        model->insertRow(selected.at(0).row() + 1, selected[0]);
}
