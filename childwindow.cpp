#include "childwindow.h"
#include "ui_childwindow.h"

ChildWindow::ChildWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWindow)
{
    ui->setupUi(this);
}

ChildWindow::~ChildWindow()
{
    delete ui;
}
