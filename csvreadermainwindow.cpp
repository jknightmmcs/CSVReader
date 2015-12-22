#include "csvreadermainwindow.h"
#include "ui_csvreadermainwindow.h"
#include "csvtablerepresentation.h"
#include <csvreader.h>
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

        child->show();
    }
}
