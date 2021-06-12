#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSize>

class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(QObject* parent = nullptr);
    ~RenderThread();

    void render(double centerX, double centerY, double scaleFactor, QSize resultSize, double devicePixelRatio);

protected:
    void run() override;

signals:
    void renderedImage(const QImage& image, double scaleFactor);

private:
    //========================================== Threading fields
    QMutex mutex;
    QWaitCondition condition;
    bool restart;
    bool abort;


    //======================================= Map printing fields
    static uint rgbFromWaveLength(double wave);
    double centerX;
    double centerY;
    double scaleFactor;
    double devicePixelRatio;
    QSize resultSize;
    static const int32_t ColorMapSize { 512 };
    uint colorMap[ColorMapSize];
};

#endif // RENDERTHREAD_H
