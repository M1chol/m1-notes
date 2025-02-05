#ifndef TABLETCANVAS_H
#define TABLETCANVAS_H

#include <QWidget>
#include <QTabletEvent>
#include <QPen>
#include <QPointF>
#include <vector>
#include <QPainterPath>
#include <QTextEdit>
#include <QFileDialog>
#include "textblock.h"

struct Stroke {
    QPen pen;
    std::vector<QPointF> points;
};

class TabletCanvas : public QWidget {
    Q_OBJECT

public:
    explicit TabletCanvas(QWidget *parent = nullptr);
    ~TabletCanvas();
    void clear();

protected:
    // Tablet events
    void tabletEvent(QTabletEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void updateCache();

private:
    qreal pressureToWidth(qreal pressure);
    void startStroke(const QTabletEvent *event);
    void mousePressEvent(QMouseEvent *event) override;

    std::vector<TextBlock *> textWindows;
    std::vector<Stroke *> m_strokes;
    Stroke *m_currentStroke;
    QPixmap *m_canvasCached;
    QPen m_pen;
    bool m_drawing;
};

#endif // TABLETCANVAS_H
