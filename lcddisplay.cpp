#include "lcddisplay.h"
#include <QPainter>

LcdDisplay::LcdDisplay(int width, int height) :
    DisplayWidget(width, height, QImage::Format_RGB16)
{
    m_timer.setInterval(16);
    connect(&m_timer, &QTimer::timeout, this, &LcdDisplay::updateScreen);
    m_img = QImage(width, height, QImage::Format_ARGB32_Premultiplied);
}

void LcdDisplay::setFps(int fps)
{
    m_timer.setInterval(1000 / fps);
}

int LcdDisplay::getFps()
{
    return 1000 / m_timer.interval();
}

void LcdDisplay::configLayer(int number, FrameBuffer *frameBuffer)
{
    m_layer[number-1].fb = frameBuffer;
}

void LcdDisplay::setLayerPos(int number, int x, int y)
{
    m_layer[number-1].x = x;
    m_layer[number-1].y = y;
}

void LcdDisplay::setLayerOpacity(int number, uint8_t alpha)
{
    m_layer[number-1].alpha = alpha;
}

void LcdDisplay::setLayerDefaultColor(int number, Color color)
{
    m_layer[number-1].defaultColor = color;
}

void LcdDisplay::setLayerColorKeying(int number, Color color)
{
    m_layer[number-1].keyColor = color;
}

void LcdDisplay::setEnabled(bool enabled)
{
    if (enabled)
    {
        m_timer.start();
    }
    else
    {
        m_timer.stop();
    }
}

void LcdDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.drawImage(0, 0, m_img);
}

void LcdDisplay::updateScreen()
{
    m_img.fill(0xFF000000);
    QPainter p(&m_img);

    for (int i=0; i<2; i++)
    {
        Layer &layer = m_layer[i];
        FrameBuffer *fb = layer.fb;
        if (!fb)
            continue;
        QImage img(fb->data(), fb->width(), fb->height(), QImage::Format_RGB16);
        p.setOpacity(layer.alpha / 255.0);
        p.drawImage(layer.x, layer.y, img);
    }

    p.end();

    QWidget::update();
}
