#ifndef CMYCOMBOX_H
#define CMYCOMBOX_H

#include <QComboBox>
#include <QObject>

class CMyCombox : public QComboBox
{
    Q_OBJECT
public:
    explicit CMyCombox(QWidget* parent);

    void setTextColor(const QColor& color);
    void setBackgroundColor(const QColor& color);
    void setBorderColor(const QColor& color);
    void setArrowColor(const QColor& color);
    void setPopupBackgroundColor(const QColor& color);
    void setEditBackgroundColor(const QColor& color);
    void setArrowBackgroundColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void showPopup() override;

private:
    QColor m_textColor;
    QColor m_backgroundColor;
    QColor m_borderColor;
    QColor m_arrowColor;
    QColor m_popupBackgroundColor;
    QColor m_editBackgroundColor;
    QColor m_arrowBackgroundColor;
};

#endif // CMYCOMBOX_H
