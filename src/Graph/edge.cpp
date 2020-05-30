#include "edge.h"
#include <QPainter>
#include "src/constants.h"


Edge::Edge(QObject *parent) : QObject(parent)
{
    setZValue(EDGE_Z_VALUE);
}

void Edge::setVerteces(Vertex *first, Vertex *second)
{
    setFirst(first);
    setSecond(second);
}

void Edge::setFirst(Vertex *first)
{
    firstVertex = first;

    if (first != nullptr)
        firstPos = first->pos();
}

void Edge::setSecond(Vertex *second)
{
    secondVertex = second;

    if (second != nullptr)
        secondPos = second->pos();
}

void Edge::setName(const QString &name)
{
    this->name = name;
}

void Edge::setId(int id)
{
    this->id = id;
}

Vertex *Edge::getAnotherVertex(const Vertex *vertex) const
{
    if (vertex == firstVertex)
        return secondVertex;

    if (vertex == secondVertex)
        return firstVertex;

    return  nullptr;
}

QRectF Edge::boundingRect() const
{

    QPointF topLeft = QPointF(std::min(firstPos.x(), secondPos.x()),
                                std::min(firstPos.y(), secondPos.y()));

    QPointF bottomRight = QPointF(std::max(firstPos.x(), secondPos.x()),
                                std::max(firstPos.y(), secondPos.y()));

    return QRectF(topLeft, bottomRight);
}

std::pair<Vertex *, Vertex *> Edge::getVerteces() const
{
    return std::pair<Vertex *, Vertex *>(firstVertex, secondVertex);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (firstVertex != nullptr && secondVertex != nullptr)
    {
        firstPos = firstVertex->pos();
        secondPos = secondVertex->pos();
        painter->setPen(QPen(Qt::black, 4));
        painter->drawLine(firstPos, secondPos);
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

