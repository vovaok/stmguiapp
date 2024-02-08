#include <QMouseEvent>
#include "displaywidget.h"
#include <QPainter>
#include "application.h"

DisplayWidget::DisplayWidget(int width, int height, QImage::Format format, QWidget *parent) :
    QWidget{parent},
    Image(width, height, formatFromQImage(format))
{
    stmApp()->addWidget(this);
    setFixedSize(width, height);
}

uint32_t DisplayWidget::pixel(int x, int y) const
{
    return toRgb(backgroundColor());
}

void DisplayWidget::setPixel(int x, int y, uint32_t color)
{
    Image::setPixel(x, y, color);
    update();
}

void DisplayWidget::fillRect(int x, int y, int width, int height, uint32_t color)
{
    Image::fillRect(x, y, width, height, color);
    update();
}

void DisplayWidget::copyRect(int x, int y, int width, int height, const uint8_t *buffer)
{
    Image::copyRect(x, y, width, height, buffer);
    update();
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    QImage img(Image::data(), Image::width(), Image::height(), QImage::Format_RGB16);
    p.drawImage(0, 0, img);
}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    TouchScreen::m_pressure = 1;
    TouchScreen::m_x = event->x();
    TouchScreen::m_y = event->y();
    touchEvent(TouchEvent::Press);
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    TouchScreen::m_pressure = 1;
    TouchScreen::m_x = event->x();
    TouchScreen::m_y = event->y();
    touchEvent(TouchEvent::Move);
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    TouchScreen::m_pressure = 0;
    TouchScreen::m_x = event->x();
    TouchScreen::m_y = event->y();
    touchEvent(TouchEvent::Release);
}

PixelFormat DisplayWidget::formatFromQImage(QImage::Format format)
{
    switch (format)
    {
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:   return Format_ARGB8888;
    case QImage::Format_RGB888:                 return Format_RGB888;
    case QImage::Format_RGB16:                  return Format_RGB565;
    case QImage::Format_RGB555:                 return Format_ARGB1555; // co close
    case QImage::Format_ARGB4444_Premultiplied: return Format_ARGB4444;
    case QImage::Format_Grayscale8:             return Format_L8;
//    case QImage::Format_:                     return Format_AL44; // no such format
//    case QImage::Format_:                     return Format_AL88; // no
//    case QImage::Format_:                     return Format_A4;
    case QImage::Format_Alpha8:                 return Format_A8;
//    case QImage::Format_:                     return Format_L4;
    default:;
    }
    return Format_RGB565; // invalid format// by default
}
