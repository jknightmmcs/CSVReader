#include "csvreadermainwindow.h"
#include "ui_csvreadermainwindow.h"

CSVReaderMainWindow::CSVReaderMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSVReaderMainWindow)
{
    ui->setupUi(this);
}

CSVReaderMainWindow::~CSVReaderMainWindow()
{
    delete ui;
}
