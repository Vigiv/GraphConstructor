#include "graph.h"

#include <QCursor>


Graph::Graph(QObject *parent) : QObject(parent)
{

}

void Graph::setScene(QGraphicsScene *scene)
{
    this->scene = scene;
}

void Graph::setMousePos(const QPoint &pos)
{
    mousePos = pos;
}

void Graph::makeVertex()
{
    Vertex *vertex = new Vertex;
    vertex->setPos(mousePos);

    verteces.push_back(vertex);
    scene->addItem(vertex);
}

void Graph::removeVertex()
{
    for (auto it = verteces.begin(); it != verteces.end(); ++it)
    {
        QRectF rect = (*it)->boundingRect();
        rect.moveLeft((*it)->pos().x());
        rect.moveRight((*it)->pos().x());
        rect.moveTop((*it)->pos().x());
        rect.moveBottom((*it)->pos().y());

        if (rect.contains(mousePos))
        {
            verteces.erase(it);
            (*it)->~Vertex();
            break;
        }
    }
}

bool Graph::pointIsVertex(const QPoint &pos) const
{
    for (auto it = verteces.cbegin(); it != verteces.cend(); ++it)
    {
        QRectF rect = (*it)->boundingRect();
        rect.moveLeft((*it)->pos().x());
        rect.moveRight((*it)->pos().x());
        rect.moveTop((*it)->pos().x());
        rect.moveBottom((*it)->pos().y());

        if (rect.contains(pos))
            return true;
    }

    return false;
}

Vertex *Graph::getVertex(const QPoint &pos)
{
    for (auto it = verteces.cbegin(); it != verteces.cend(); ++it)
    {
        QRectF rect = (*it)->boundingRect();
        rect.moveLeft((*it)->pos().x());
        rect.moveRight((*it)->pos().x());
        rect.moveTop((*it)->pos().x());
        rect.moveBottom((*it)->pos().y());

        if (rect.contains(pos))
            return *it;
    }

    return nullptr;
}
