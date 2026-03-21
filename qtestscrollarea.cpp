#include "qtestscrollarea.h"
#include "ui_qtestscrollarea.h"

QTestScrollArea::QTestScrollArea(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QTestScrollArea)
{
    ui->setupUi(this);
}

QTestScrollArea::~QTestScrollArea()
{
    delete ui;
}
