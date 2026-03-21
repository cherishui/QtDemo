#ifndef QTESTSCROLLAREA_H
#define QTESTSCROLLAREA_H

#include <QDialog>

namespace Ui {
class QTestScrollArea;
}

class QTestScrollArea : public QDialog
{
    Q_OBJECT

public:
    explicit QTestScrollArea(QWidget *parent = nullptr);
    ~QTestScrollArea();

private:
    Ui::QTestScrollArea *ui;
};

#endif // QTESTSCROLLAREA_H
