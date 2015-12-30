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


    void SetDelegate(int i, CSVTableRepresentation* repr);

    void SetDelegates();
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *object, QEvent *event);
    bool handleCopyEvent();
    bool handleCutEvent();
    bool handlePasteEvent();

    Ui::CSVReader *ui;    
    CSVModel* model;
    CellTypeData ColumnToAdd;
    QModelIndex rowCopyPaste;
    int copyPasteCount;
    bool isCopy;
};

#endif // CSVREADER_H
