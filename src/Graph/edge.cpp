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

void Edge::setName(const QString &name)
{
    this->name = name;
}

void Edge::setId(int id)
{
    this->id = id;
}

QRectF Edge::boundingRect() const
{
    if (firstVertex != nullptr && secondVertex != nullptr)
    {
        QPointF topLeft = QPointF(std::min(firstVertex->pos().x(), secondVertex->pos().x()),
                                std::min(firstVertex->pos().y(), secondVertex->pos().y()));

        QPointF bottomRight = QPointF(std::max(firstVertex->pos().x(), secondVertex->pos().x()),
                                std::max(firstVertex->pos().y(), secondVertex->pos().y()));

        return QRectF(topLeft, bottomRight);
    }
    else
        return QRectF(0, 0, 0, 0);
}

std::pair<Vertex *, Vertex *> Edge::getVerteces() const
{
    return std::pair<Vertex *, Vertex *>(firstVertex, secondVertex);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (firstVertex != nullptr && secondVertex != nullptr)
    {
        painter->setPen(QPen(Qt::black, 4));
        painter->drawLine(firstVertex->pos(), secondVertex->pos());
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

