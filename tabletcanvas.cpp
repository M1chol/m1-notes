#include "tabletcanvas.h"
#include <QPainter>
#include <QtMath>
#include <QResizeEvent>
#include <QMessageBox>


TabletCanvas::TabletCanvas(QWidget *parent)
    : QWidget(parent),
    m_pen(Qt::white, 1.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
    m_currentStroke(nullptr),
    m_drawing(false)
{
    resize(500, 500);
    setAttribute(Qt::WA_TabletTracking);
    m_canvasCached = new QPixmap(size());
    m_canvasCached->fill(Qt::transparent);
}

TabletCanvas::~TabletCanvas(){
    for(Stroke *stroke : m_strokes){
        delete stroke;
    }
}

void TabletCanvas::clear()
{
    m_strokes.clear();
    for(auto &box : textWindows){
        delete box;
    }
    textWindows.clear();
    m_currentStroke = nullptr;
    delete m_canvasCached;
    m_canvasCached = new QPixmap(size());
    m_canvasCached->fill(Qt::transparent);
    updateCache();
    update();
}

void TabletCanvas::mousePressEvent(QMouseEvent *event){
    TextBlock *textBox = new TextBlock(event->pos(), this);
    textWindows.push_back(textBox);
    qDebug() << "TextBlock created";
}


qreal TabletCanvas::pressureToWidth(qreal pressure)
{
    return pressure * 5 + 1;
}

void TabletCanvas::startStroke(const QTabletEvent *event)
{
    m_drawing = true;
    Stroke *stroke = new Stroke;
    stroke->pen = m_pen;
    qreal initialWidth = pressureToWidth(event->pressure());

    stroke->pen.setWidthF(initialWidth);
    stroke->points.push_back(event->position());
    m_strokes.push_back(stroke);
    m_currentStroke = m_strokes.back();
}

void TabletCanvas::tabletEvent(QTabletEvent *event)
{
    switch (event->type()) {
    case QEvent::TabletPress: {
        startStroke(event);
        break;
    }
    case QEvent::TabletMove: {
        if (m_drawing) {
            m_currentStroke->points.push_back(event->position());
            update();
        }
        break;
    }
    case QEvent::TabletRelease: {
        m_drawing = false;
        m_currentStroke = nullptr;
        updateCache();
        break;
    }
    default:
        break;
    }
    event->accept();
}
void TabletCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draw cached strokes
    painter.drawPixmap(0, 0, *m_canvasCached);

    // Draw new stroke
    if(m_drawing && m_currentStroke)
    {
        painter.setPen(m_currentStroke->pen);
        QPainterPath path;
        path.moveTo(m_currentStroke->points[0]);
        for(size_t i = 1; i < m_currentStroke->points.size(); i++)
        {
            path.lineTo(m_currentStroke->points[i]);
        }
        painter.drawPath(path);
    }
}

void TabletCanvas::updateCache(){
    QPainter painter(m_canvasCached);
    painter.setRenderHint(QPainter::Antialiasing);
    for (const Stroke *stroke : m_strokes) {
        if (stroke->points.empty())
            continue;
        painter.setPen(stroke->pen);
        // If the stroke only has one point, draw a point.
        if (stroke->points.size() == 1) {
            painter.drawPoint(stroke->points[0]);
        } else {
            // Create a QPainterPath and connect all points.
            QPainterPath path;
            path.moveTo(stroke->points[0]);
            for (size_t i = 1; i < stroke->points.size(); ++i) {
                path.lineTo(stroke->points[i]);
            }
            painter.drawPath(path);
        }
    }
    qDebug() << "Cache updated";
}

void TabletCanvas::resizeEvent(QResizeEvent *event)
{
    // This is needed becouse we have transparent background
    delete m_canvasCached;
    m_canvasCached = new QPixmap(size());
    m_canvasCached->fill(Qt::transparent);
    updateCache();
    QWidget::resizeEvent(event);
}
