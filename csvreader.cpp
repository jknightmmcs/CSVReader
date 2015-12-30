#include "csvreader.h"
#include "ui_csvreader.h"
#include <comboboxdelegate.h>
#include <spinboxdelegate.h>
#include <textboxdelegate.h>
#include <addcolumndialog.h>
#include <QMessageBox>
#include <QKeyEvent>
#include <algorithm>

void CSVReader::SetDelegates()
{
    for(unsigned i = 0; i < model->repr_->header.size(); i++)
        SetDelegate(i, model->repr_);
}

void CSVReader::SetDelegate(int i, CSVTableRepresentation* repr)
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
        for(unsigned j = 0; j < repr->header[i].data.size(); j++)
            items.push_back(repr->header[i].data[j]);
        ui->tableView->setItemDelegateForColumn(i, new ComboBoxItemDelegate(items, ui->tableView));
        break;
    }
}

CSVReader::CSVReader(CSVModel* model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSVReader)
{
    ui->setupUi(this);
    this->model = model;
    ui->tableView->setModel(model);            

    SetDelegates();

    ui->tableView->installEventFilter(this);

    ui->tableView->resizeColumnsToContents();    

}

CSVReader::~CSVReader()
{
    delete ui;
}

void CSVReader::addColumn(CellTypeData data)
{
    model->SetColumnToAdd(data);
}

void CSVReader::on_actionRemove_selected_triggered()
{
    auto selected = ui->tableView->selectionModel()->selectedColumns();

    if (selected.size() == 0)
        return;
    model->removeColumns(selected[0].column(), selected.size(), selected[0]);
    SetDelegates();
}

void CSVReader::on_actionRemove_selected_2_triggered()
{    
    auto selected = ui->tableView->selectionModel() -> selectedRows();
    if (selected.size() == 0)
        return;

    model->removeRows(selected[0].row(), selected.size(), selected[0]);
    SetDelegates();
}

void CSVReader::on_actionHigher_triggered()
{    
    auto selected = ui->tableView->selectionModel() -> selectedRows();
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

void CSVReader::on_actionRight_triggered()
{
    AddColumnDialog dialog;
    connect(&dialog, SIGNAL(typeDataReady(CellTypeData)), this, SLOT(addColumn(CellTypeData)));
    dialog.exec();
    if (dialog.result() == QDialog::Accepted)
    {
        auto selected = ui->tableView->selectionModel()->selectedColumns();
        if (selected.size() == 0)
            model->insertColumn(model->columnCount(QModelIndex()), QModelIndex());
        else
            model->insertColumn(selected[0].column() + 1, selected[0]);
        SetDelegates();
    }
}

bool CSVReader::handleCopyEvent()
{
    auto selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.size() != 0)
    {
        isCopy = true;
        rowCopyPaste = selected[0];
        copyPasteCount = selected.size();
        ui->tableView->clearSelection();
    }
    return true;
}

bool CSVReader::handleCutEvent()
{
    auto selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.size() != 0)
    {
        isCopy = false;
        for(int i = 0; i < selected.size(); i++)
        {
            ui->tableView->setRowHidden(selected[i].row(), true);
        }
        rowCopyPaste = selected[0];
        copyPasteCount = selected.size();
        ui->tableView->clearSelection();
    }
    return true;
}

bool CSVReader::handlePasteEvent()
{
    if (copyPasteCount != 0)
    {
        auto selection = ui->tableView->selectionModel()->selectedRows();
        if (selection.size() > 0)
        {
            auto selected = selection[0];
            if (!isCopy)
            {
                model->moveRows(rowCopyPaste, rowCopyPaste.row(), copyPasteCount, selected, 0 /* UNUSED */);
                for(int i = 0; i < copyPasteCount; i++)
                {
                    ui->tableView->setRowHidden(i + rowCopyPaste.row(), false);
                }
            }
            else
            {
                model->copyRows(rowCopyPaste.row(), copyPasteCount, selected.row(), selected);
            }
            copyPasteCount = 0;
            ui->tableView->clearSelection();
        }
    }
    return true;
}

bool CSVReader::eventFilter(QObject * object, QEvent *event)
{
    if (object == ui->tableView && event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent -> key() == Qt::Key_C && keyEvent->modifiers().testFlag(Qt::ControlModifier))
            return handleCopyEvent();
        if (keyEvent -> key() == Qt::Key_X && keyEvent->modifiers().testFlag(Qt::ControlModifier))
            return handleCutEvent();
        if (keyEvent -> key() == Qt::Key_V && keyEvent->modifiers().testFlag(Qt::ControlModifier))
            return handlePasteEvent();
    }
    return false;
}

void CSVReader::on_actionLeft_triggered()
{
    AddColumnDialog dialog;
    connect(&dialog, SIGNAL(typeDataReady(CellTypeData)), this, SLOT(addColumn(CellTypeData)));
    dialog.exec();
    if (dialog.result() == QDialog::Accepted)
    {
        auto selected = ui->tableView->selectionModel()->selectedColumns();
        if (selected.size() == 0)
            model->insertColumn(0, QModelIndex());
        else if (selected.at(0).column() == 0)
            model->insertColumn(0, selected[0]);
        else
            model->insertColumn(selected[0].column(), selected[0]);
        SetDelegates();
    }
}

void CSVReader::closeEvent(QCloseEvent *)
{
    if (QMessageBox::question(this, tr("Changes confirmation"), tr("Save file?"),
                                       QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        model->getRepresentation()->Save();
    }
}
