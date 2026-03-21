// ScrollBarStyleGenerator.cpp
#include "ScrollBarStyleGenerator.h"
#include <QWidget>

ScrollBarStyleGenerator::ScrollBarStyleGenerator(QObject *parent)
    : QObject(parent)
{
}

QString ScrollBarStyleGenerator::colorToRgba(const QColor &color) const
{
    return QString("rgba(%1, %2, %3, %4)")
    .arg(color.red())
        .arg(color.green())
        .arg(color.blue())
        .arg(color.alphaF(), 0, 'f', 2);
}

void ScrollBarStyleGenerator::setBackgroundColor(const QColor &color)
{ m_backgroundColor = color; }

void ScrollBarStyleGenerator::setHandleColor(const QColor &color)
{ m_handleColor = color; }

void ScrollBarStyleGenerator::setHandleHoverColor(const QColor &color)
{ m_handleHoverColor = color; }

void ScrollBarStyleGenerator::setHandlePressedColor(const QColor &color)
{ m_handlePressedColor = color; }

void ScrollBarStyleGenerator::setHandleDisabledColor(const QColor &color)
{ m_handleDisabledColor = color; }

void ScrollBarStyleGenerator::setArrowColor(const QColor &color)
{ m_arrowColor = color; }

void ScrollBarStyleGenerator::setArrowHoverColor(const QColor &color)
{ m_arrowHoverColor = color; }

void ScrollBarStyleGenerator::setArrowPressedColor(const QColor &color)
{ m_arrowPressedColor = color; }

void ScrollBarStyleGenerator::setArrowDisabledColor(const QColor &color)
{ m_arrowDisabledColor = color; }

void ScrollBarStyleGenerator::setSubPageColor(const QColor &color)
{ m_subPageColor = color; }

void ScrollBarStyleGenerator::setAddPageColor(const QColor &color)
{ m_addPageColor = color; }

void ScrollBarStyleGenerator::setScrollBarWidth(int width)
{ m_scrollBarWidth = width; }

void ScrollBarStyleGenerator::setHandleMinLength(int length)
{ m_handleMinLength = length; }

void ScrollBarStyleGenerator::setArrowSize(int size)
{ m_arrowSize = size; }

void ScrollBarStyleGenerator::setBorderRadius(int radius)
{ m_borderRadius = radius; }

QString ScrollBarStyleGenerator::generateStyleSheet() const
{
    QString style;

    // ========== 垂直滚动条 ==========
    style += QString(R"(
/* 垂直滚动条整体 */
QScrollBar:vertical {
    background: %1;
    width: %2px;
    margin: %3px 0px %3px 0px;
    border-radius: %4px;
}

/* 滑块 */
QScrollBar::handle:vertical {
    background: %5;
    min-height: %6px;
    border-radius: %7px;
    margin: 2px;
}

QScrollBar::handle:vertical:hover {
    background: %8;
}

QScrollBar::handle:vertical:pressed {
    background: %9;
}

QScrollBar::handle:vertical:disabled {
    background: %10;
}

/* 上方区域（滑块上面） */
QScrollBar::sub-page:vertical {
    background: %11;
    border-radius: %12px;
}

/* 下方区域（滑块下面） */
QScrollBar::add-page:vertical {
    background: %13;
    border-radius: %14px;
}

/* 向上箭头按钮 */
QScrollBar::sub-line:vertical {
    subcontrol-origin: margin;
    subcontrol-position: top;
    height: %15px;
    background: %16;
    border-radius: %17px;
}

QScrollBar::sub-line:vertical:hover {
    background: %18;
}

QScrollBar::sub-line:vertical:pressed {
    background: %19;
}

QScrollBar::sub-line:vertical:disabled {
    background: %20;
}

/* 向上箭头图标 */
QScrollBar::up-arrow:vertical {
    image: none;
    border-left: 3px solid transparent;
    border-right: 3px solid transparent;
    border-bottom: 5px solid %21;
    width: 0px;
    height: 0px;
}

QScrollBar::up-arrow:vertical:hover {
    border-bottom-color: %22;
}

QScrollBar::up-arrow:vertical:pressed {
    border-bottom-color: %23;
}

QScrollBar::up-arrow:vertical:disabled {
    border-bottom-color: %24;
}

/* 向下箭头按钮 */
QScrollBar::add-line:vertical {
    subcontrol-origin: margin;
    subcontrol-position: bottom;
    height: %25px;
    background: %26;
    border-radius: %27px;
}

QScrollBar::add-line:vertical:hover {
    background: %28;
}

QScrollBar::add-line:vertical:pressed {
    background: %29;
}

QScrollBar::add-line:vertical:disabled {
    background: %30;
}

/* 向下箭头图标 */
QScrollBar::down-arrow:vertical {
    image: none;
    border-left: 3px solid transparent;
    border-right: 3px solid transparent;
    border-top: 5px solid %31;
    width: 0px;
    height: 0px;
}

QScrollBar::down-arrow:vertical:hover {
    border-top-color: %32;
}

QScrollBar::down-arrow:vertical:pressed {
    border-top-color: %33;
}

QScrollBar::down-arrow:vertical:disabled {
    border-top-color: %34;
}
)")
                 .arg(colorToRgba(m_backgroundColor))           // 1
                 .arg(m_scrollBarWidth)                         // 2
                 .arg(m_arrowSize)                              // 3
                 .arg(m_borderRadius)                           // 4
                 .arg(colorToRgba(m_handleColor))               // 5
                 .arg(m_handleMinLength)                        // 6
                 .arg(m_borderRadius - 2)                       // 7
                 .arg(colorToRgba(m_handleHoverColor))          // 8
                 .arg(colorToRgba(m_handlePressedColor))        // 9
                 .arg(colorToRgba(m_handleDisabledColor))       // 10
                 .arg(colorToRgba(m_subPageColor))              // 11
                 .arg(m_borderRadius)                           // 12
                 .arg(colorToRgba(m_addPageColor))              // 13
                 .arg(m_borderRadius)                           // 14
                 .arg(m_arrowSize)                              // 15
                 .arg(colorToRgba(m_backgroundColor))           // 16
                 .arg(m_borderRadius / 2)                       // 17
                 .arg(colorToRgba(m_handleHoverColor))          // 18
                 .arg(colorToRgba(m_handlePressedColor))        // 19
                 .arg(colorToRgba(m_handleDisabledColor))       // 20
                 .arg(colorToRgba(m_arrowColor))                // 21
                 .arg(colorToRgba(m_arrowHoverColor))           // 22
                 .arg(colorToRgba(m_arrowPressedColor))         // 23
                 .arg(colorToRgba(m_arrowDisabledColor))        // 24
                 .arg(m_arrowSize)                              // 25
                 .arg(colorToRgba(m_backgroundColor))           // 26
                 .arg(m_borderRadius / 2)                       // 27
                 .arg(colorToRgba(m_handleHoverColor))          // 28
                 .arg(colorToRgba(m_handlePressedColor))        // 29
                 .arg(colorToRgba(m_handleDisabledColor))       // 30
                 .arg(colorToRgba(m_arrowColor))                // 31
                 .arg(colorToRgba(m_arrowHoverColor))           // 32
                 .arg(colorToRgba(m_arrowPressedColor))         // 33
                 .arg(colorToRgba(m_arrowDisabledColor));       // 34

    // ========== 水平滚动条（对称结构） ==========
    style += QString(R"(
/* 水平滚动条整体 */
QScrollBar:horizontal {
    background: %1;
    height: %2px;
    margin: 0px %3px 0px %3px;
    border-radius: %4px;
}

/* 滑块 */
QScrollBar::handle:horizontal {
    background: %5;
    min-width: %6px;
    border-radius: %7px;
    margin: 2px;
}

QScrollBar::handle:horizontal:hover {
    background: %8;
}

QScrollBar::handle:horizontal:pressed {
    background: %9;
}

QScrollBar::handle:horizontal:disabled {
    background: %10;
}

/* 左侧区域 */
QScrollBar::sub-page:horizontal {
    background: %11;
    border-radius: %12px;
}

/* 右侧区域 */
QScrollBar::add-page:horizontal {
    background: %13;
    border-radius: %14px;
}

/* 向左箭头按钮 */
QScrollBar::sub-line:horizontal {
    subcontrol-origin: margin;
    subcontrol-position: left;
    width: %15px;
    background: %16;
    border-radius: %17px;
}

QScrollBar::sub-line:horizontal:hover {
    background: %18;
}

QScrollBar::sub-line:horizontal:pressed {
    background: %19;
}

QScrollBar::sub-line:horizontal:disabled {
    background: %20;
}

/* 向左箭头图标 */
QScrollBar::left-arrow:horizontal {
    image: none;
    border-top: 3px solid transparent;
    border-bottom: 3px solid transparent;
    border-right: 5px solid %21;
    width: 0px;
    height: 0px;
}

QScrollBar::left-arrow:horizontal:hover {
    border-right-color: %22;
}

QScrollBar::left-arrow:horizontal:pressed {
    border-right-color: %23;
}

QScrollBar::left-arrow:horizontal:disabled {
    border-right-color: %24;
}

/* 向右箭头按钮 */
QScrollBar::add-line:horizontal {
    subcontrol-origin: margin;
    subcontrol-position: right;
    width: %25px;
    background: %26;
    border-radius: %27px;
}

QScrollBar::add-line:horizontal:hover {
    background: %28;
}

QScrollBar::add-line:horizontal:pressed {
    background: %29;
}

QScrollBar::add-line:horizontal:disabled {
    background: %30;
}

/* 向右箭头图标 */
QScrollBar::right-arrow:horizontal {
    image: none;
    border-top: 3px solid transparent;
    border-bottom: 3px solid transparent;
    border-left: 5px solid %31;
    width: 0px;
    height: 0px;
}

QScrollBar::right-arrow:horizontal:hover {
    border-left-color: %32;
}

QScrollBar::right-arrow:horizontal:pressed {
    border-left-color: %33;
}

QScrollBar::right-arrow:horizontal:disabled {
    border-left-color: %34;
}
)")
                 .arg(colorToRgba(m_backgroundColor))
                 .arg(m_scrollBarWidth)
                 .arg(m_arrowSize)
                 .arg(m_borderRadius)
                 .arg(colorToRgba(m_handleColor))
                 .arg(m_handleMinLength)
                 .arg(m_borderRadius - 2)
                 .arg(colorToRgba(m_handleHoverColor))
                 .arg(colorToRgba(m_handlePressedColor))
                 .arg(colorToRgba(m_handleDisabledColor))
                 .arg(colorToRgba(m_subPageColor))
                 .arg(m_borderRadius)
                 .arg(colorToRgba(m_addPageColor))
                 .arg(m_borderRadius)
                 .arg(m_arrowSize)
                 .arg(colorToRgba(m_backgroundColor))
                 .arg(m_borderRadius / 2)
                 .arg(colorToRgba(m_handleHoverColor))
                 .arg(colorToRgba(m_handlePressedColor))
                 .arg(colorToRgba(m_handleDisabledColor))
                 .arg(colorToRgba(m_arrowColor))
                 .arg(colorToRgba(m_arrowHoverColor))
                 .arg(colorToRgba(m_arrowPressedColor))
                 .arg(colorToRgba(m_arrowDisabledColor))
                 .arg(m_arrowSize)
                 .arg(colorToRgba(m_backgroundColor))
                 .arg(m_borderRadius / 2)
                 .arg(colorToRgba(m_handleHoverColor))
                 .arg(colorToRgba(m_handlePressedColor))
                 .arg(colorToRgba(m_handleDisabledColor))
                 .arg(colorToRgba(m_arrowColor))
                 .arg(colorToRgba(m_arrowHoverColor))
                 .arg(colorToRgba(m_arrowPressedColor))
                 .arg(colorToRgba(m_arrowDisabledColor));

    return style;
}

void ScrollBarStyleGenerator::applyToWidget(QWidget *widget)
{
    if (widget) {
        widget->setStyleSheet(generateStyleSheet());
    }
}
