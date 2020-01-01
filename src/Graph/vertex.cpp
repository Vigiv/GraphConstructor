#include "vertex.h"
#include "src/constants.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>


Vertex::Vertex(QObject *parent) : QObject(parent)
{

}

QRectF Vertex::boundingRect() const
{
    return QRectF(-VERTEX_RADIUS / 2, -VERTEX_RADIUS / 2, VERTEX_RADIUS, VERTEX_RADIUS);
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter->drawEllipse(-VERTEX_RADIUS / 2, -VERTEX_RADIUS / 2, VERTEX_RADIUS, VERTEX_RADIUS);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event)
}

void Vertex::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));

    Q_UNUSED(event)
}
