#include "vertex.h"
#include "src/constants.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>


Vertex::Vertex(QObject *parent) : QObject(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);

    setZValue(VERTEX_Z_VALUE);
}

void Vertex::setName(const QString &name)
{
    this->name = name;
}

void Vertex::setId(int id)
{
    this->id = id;
}

QRectF Vertex::boundingRect() const
{
    return QRectF(-VERTEX_RADIUS / 2, -VERTEX_RADIUS / 2, VERTEX_RADIUS, VERTEX_RADIUS);
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(VERTEX_BORDER_COLOR);
    painter->setBrush(QBrush(VERTEX_BACKGROUND_COLOR, Qt::SolidPattern));
    painter->drawEllipse(boundingRect());

    painter->setPen(VERTEX_TEXT_COLOR);
    painter->setFont(QFont("Arial", VERTEX_TEXT_SIZE));
    painter->drawText(boundingRect(), Qt::AlignCenter, name);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Vertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    emit(vertexSelected(this));


    Q_UNUSED(event)
}

void Vertex::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));

    emit(moveVerteces());
}

void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));

    Q_UNUSED(event)
}

void Vertex::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    hover = true;

    Q_UNUSED(event)
}

void Vertex::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    hover = false;

    Q_UNUSED(event)
}
