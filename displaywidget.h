#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include "gfx/image.h"
#include "gfx/touchscreen.h"

class DisplayWidget : public QWidget, public Image, public TouchScreen
{
    Q_OBJECT
public:
    explicit DisplayWidget(int width, int height, QWidget *parent = nullptr);

    virtual uint16_t pixel(int x, int y) override;
    virtual void setPixel(int x, int y, uint16_t color) override;
    virtual void fillRect(int x, int y, int width, int height, uint16_t color) override;
    virtual void copyRect(int x, int y, int width, int height, const uint16_t *buffer) override;

    using Image::width;
    using Image::height;

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
};

#endif // DISPLAYWIDGET_H
