#include "addcolumndialog.h"
#include "ui_addcolumndialog.h"
#include "csvtablerepresentation.h"

AddColumnDialog::AddColumnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddColumnDialog)
{
    ui->setupUi(this);
}

AddColumnDialog::~AddColumnDialog()
{
    delete ui;
}

void AddColumnDialog::on_enumButton_toggled(bool checked)
{
    ui->enumEdit->setEnabled(checked);
}

void AddColumnDialog::on_buttonBox_accepted()
{
    CellTypeData data;
    if (ui->intButton->isChecked())
    {
        data.defaultValue = 0;
        data.type = CellType::TypeInt;
    }
    else if (ui->stringButton->isChecked())
    {
        data.defaultValue = "";
        data.type = CellType::TypeString;
    }
    else if (ui->boolButton->isChecked())
    {
        data.defaultValue = false;
        data.type = CellType::TypeBool;
    }
    else if (ui->enumButton->isChecked())
    {
        data.defaultValue = 0;
        data.type = CellType::TypeEnum;
        QStringList values = ui->enumEdit->toPlainText().split("\n", QString::SplitBehavior::SkipEmptyParts);
        for(int i = 0; i < values.size(); i++)
            data.data.push_back(values[i]);
    }
    emit typeDataReady(data);
}
