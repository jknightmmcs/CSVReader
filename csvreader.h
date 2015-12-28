#ifndef CSVREADER_H
#define CSVREADER_H

#include <QWidget>
#include <csvmodel.h>
#include <QMainWindow>

namespace Ui {
class CSVReader;
}

class CSVReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSVReader(CSVModel *model, QWidget *parent = 0);
    ~CSVReader();

    void SetDelegate(int i, CSVTableRepresentation* repr);

    void SetDelegates();
public slots:
    void addColumn(CellTypeData data);

private slots:
    void on_actionLeft_triggered();

    void on_actionRemove_selected_triggered();

    void on_actionRemove_selected_2_triggered();

    void on_actionHigher_triggered();

    void on_actionLower_triggered();

    void on_actionRight_triggered();

private:
    Ui::CSVReader *ui;    
    CSVModel* model;
    CellTypeData ColumnToAdd;
};

#endif // CSVREADER_H
