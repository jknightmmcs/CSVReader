#include "csvreadermainwindow.h"
#include "ui_csvreadermainwindow.h"
#include "csvtablerepresentation.h"
#include <csvreader.h>
#include <QMessageBox>
#include <QFileDialog>

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

void CSVReaderMainWindow::on_actionOpen_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Open file..."), QString(), tr("CSV (*.csv)"));
    if (!fname.isEmpty())
    {
        CSVTableRepresentation* repr = CSVTableRepresentation::LoadFromFile(fname);
        CSVModel* model = new CSVModel(repr, 0);
        auto child = new CSVReader(model, ui->mdiArea);
        model -> setParent(child);
        child->setAttribute(Qt::WA_DeleteOnClose);
        child->setWindowTitle(fname);
        ui->mdiArea->addSubWindow(child);
        readers.push_back(child);
        child->show();
    }
}

void CSVReaderMainWindow::on_actionClose_all_triggered()
{
    ui->mdiArea->closeAllSubWindows();
    readers.clear();
}

void CSVReaderMainWindow::on_actionExit_triggered()
{
    close();
}

void CSVReaderMainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("CSV Reader"), tr("Leontyev Georgiy, 2nd year of master's degree, computer science"));
}
