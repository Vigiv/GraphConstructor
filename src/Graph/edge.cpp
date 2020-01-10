#include "edge.h"
#include <QPainter>
#include "src/constants.h"


Edge::Edge(QObject *parent) : QObject(parent)
{
    setZValue(EDGE_Z_VALUE);
}

void Edge::setVerteces(Vertex *first, Vertex *second)
{
    firstVertex = first;
    secondVertex = second;
}

QRectF Edge::boundingRect() const
{
    QPointF topLeft = QPointF(std::min(firstVertex->pos().x(), secondVertex->pos().x()),
                             std::min(firstVertex->pos().y(), secondVertex->pos().y()));

    QPointF bottomRight = QPointF(std::max(firstVertex->pos().x(), secondVertex->pos().x()),
                             std::max(firstVertex->pos().y(), secondVertex->pos().y()));

    return QRectF(topLeft, bottomRight);
}

std::pair<Vertex *, Vertex *> Edge::getVerteces() const
{
    return std::pair<Vertex *, Vertex *>(firstVertex, secondVertex);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 4));
    painter->drawLine(firstVertex->pos(), secondVertex->pos());

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
