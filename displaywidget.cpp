#include <QMouseEvent>
#include "displaywidget.h"
#include <QPainter>
#include "application.h"

DisplayWidget::DisplayWidget(int width, int height, QWidget *parent) :
    QWidget{parent},
    Image(width, height)
{
    stmApp()->addWidget(this);
    setFixedSize(width, height);
}

uint16_t DisplayWidget::pixel(int x, int y)
{
    return backgroundColor().rgb565();
}

void DisplayWidget::setPixel(int x, int y, uint16_t color)
{
    Image::setPixel(x, y, color);
    update();
}

void DisplayWidget::fillRect(int x, int y, int width, int height, uint16_t color)
{
    Image::fillRect(x, y, width, height, color);
    update();
}

void DisplayWidget::copyRect(int x, int y, int width, int height, const uint16_t *buffer)
{
    Image::copyRect(x, y, width, height, buffer);
    update();
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    const uchar *data = reinterpret_cast<const uchar *>(pixels());
    QImage img(data, Image::width(), Image::height(), QImage::Format_RGB16);
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

