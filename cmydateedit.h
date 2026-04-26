#ifndef CMYDATEEDIT_H
#define CMYDATEEDIT_H

#include <QDateEdit>

//#define USE_QSS

class CMyDateEdit : public QDateEdit
{
    Q_OBJECT
public:
    explicit CMyDateEdit(QWidget *parent = nullptr);

    void SetColors(const QColor& textColor,
                   const QColor& bgColor,
                   const QColor& borderColor);

private:
    void UpdateStyle();

#ifndef USE_QSS
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
#endif


private:
    QColor m_textColor;
    QColor m_bgColor;
    QColor m_borderColor;


};

#endif // CMYDATEEDIT_H
