#ifndef CSVREADERMAINWINDOW_H
#define CSVREADERMAINWINDOW_H

#include <QMainWindow>
#include <csvreader.h>
#include <vector>

namespace Ui {
class CSVReaderMainWindow;
}

class CSVReaderMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSVReaderMainWindow(QWidget *parent = 0);
    ~CSVReaderMainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionClose_all_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::CSVReaderMainWindow *ui;
    std::vector<CSVReader*> readers;
};

#endif // CSVREADERMAINWINDOW_H
