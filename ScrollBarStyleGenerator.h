// ScrollBarStyleGenerator.h
#ifndef SCROLLBARSTYLEGENERATOR_H
#define SCROLLBARSTYLEGENERATOR_H

#include <QObject>
#include <QColor>
#include <QString>

class ScrollBarStyleGenerator : public QObject
{
    Q_OBJECT
public:
    explicit ScrollBarStyleGenerator(QObject *parent = nullptr);

    // 设置各种颜色
    void setBackgroundColor(const QColor &color);           // 滚动条背景
    void setHandleColor(const QColor &color);               // 滑块正常状态
    void setHandleHoverColor(const QColor &color);          // 滑块悬停状态
    void setHandlePressedColor(const QColor &color);        // 滑块按下状态
    void setHandleDisabledColor(const QColor &color);       // 滑块禁用状态
    void setArrowColor(const QColor &color);                // 箭头正常状态
    void setArrowHoverColor(const QColor &color);           // 箭头悬停状态
    void setArrowPressedColor(const QColor &color);         // 箭头按下状态
    void setArrowDisabledColor(const QColor &color);        // 箭头禁用状态
    void setSubPageColor(const QColor &color);              // 滑块上方区域
    void setAddPageColor(const QColor &color);              // 滑块下方区域

    // 设置尺寸
    void setScrollBarWidth(int width);                      // 滚动条宽度
    void setHandleMinLength(int length);                    // 滑块最小长度
    void setArrowSize(int size);                            // 箭头按钮大小
    void setBorderRadius(int radius);                       // 圆角半径

    // 生成完整QSS
    QString generateStyleSheet() const;

    // 快捷应用方法
    void applyToWidget(QWidget *widget);

private:
    // 颜色成员
    QColor m_backgroundColor = QColor(240, 240, 240);
    QColor m_handleColor = QColor(180, 180, 180);
    QColor m_handleHoverColor = QColor(150, 150, 150);
    QColor m_handlePressedColor = QColor(120, 120, 120);
    QColor m_handleDisabledColor = QColor(220, 220, 220);
    QColor m_arrowColor = QColor(100, 100, 100);
    QColor m_arrowHoverColor = QColor(80, 80, 80);
    QColor m_arrowPressedColor = QColor(60, 60, 60);
    QColor m_arrowDisabledColor = QColor(200, 200, 200);
    QColor m_subPageColor = QColor(230, 230, 230);
    QColor m_addPageColor = QColor(230, 230, 230);

    // 尺寸成员
    int m_scrollBarWidth = 12;
    int m_handleMinLength = 30;
    int m_arrowSize = 12;
    int m_borderRadius = 6;

    // 辅助函数：颜色转CSS字符串
    QString colorToRgba(const QColor &color) const;
};

#endif // SCROLLBARSTYLEGENERATOR_H
