#ifndef CSVREADERMAINWINDOW_H
#define CSVREADERMAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::CSVReaderMainWindow *ui;
};

#endif // CSVREADERMAINWINDOW_H
