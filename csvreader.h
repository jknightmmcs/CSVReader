#ifndef CSVREADER_H
#define CSVREADER_H

#include <QWidget>
#include <csvmodel.h>

namespace Ui {
class CSVReader;
}

class CSVReader : public QWidget
{
    Q_OBJECT

public:
    explicit CSVReader(CSVModel *model, QWidget *parent = 0);
    ~CSVReader();

private:
    Ui::CSVReader *ui;    
};

#endif // CSVREADER_H
