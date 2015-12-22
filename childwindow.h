#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

#include <QWidget>

namespace Ui {
class ChildWindow;
}

class ChildWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWindow(QWidget *parent = 0);
    ~ChildWindow();

private:
    Ui::ChildWindow *ui;
};

#endif // CHILDWINDOW_H
