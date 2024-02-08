#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include "gfx/image.h"
#include "gfx/touchscreen.h"

class DisplayWidget : public QWidget, public Image, public TouchScreen
{
    Q_OBJECT
public:
    explicit DisplayWidget(int width, int height, QImage::Format format, QWidget *parent = nullptr);

    virtual uint32_t pixel(int x, int y) const override;
    virtual void setPixel(int x, int y, uint32_t color) override;
    virtual void fillRect(int x, int y, int width, int height, uint32_t color) override;
    virtual void copyRect(int x, int y, int width, int height, const uint8_t *buffer) override;
    virtual bool isReadable() const override {return true;}

    using Image::width;
    using Image::height;

    static PixelFormat formatFromQImage(QImage::Format format);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
};

#endif // DISPLAYWIDGET_H
