#ifndef ADDCOLUMNDIALOG_H
#define ADDCOLUMNDIALOG_H

#include "csvtablerepresentation.h"
#include <QDialog>

namespace Ui {
class AddColumnDialog;
}

class AddColumnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddColumnDialog(QWidget *parent = 0);
    ~AddColumnDialog();

private slots:
    void on_enumButton_toggled(bool checked);

    void on_buttonBox_accepted();

signals:
    void typeDataReady(CellTypeData data);

private:
    Ui::AddColumnDialog *ui;
};

#endif // ADDCOLUMNDIALOG_H
