#include "graph.h"

#include <QCursor>
#include <iterator>
#include <vector>


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
    if (lastSelectedVertexIndex >= 0)
    {
        verteces[lastSelectedVertexIndex]->~Vertex();
        verteces.erase(verteces.begin() + lastSelectedVertexIndex);
        lastSelectedVertexIndex = -1;
    }

}

bool Graph::pointIsVertex(const QPoint &pos)
{
    for (auto it = verteces.begin(); it != verteces.end(); ++it)
    {
        if ((*it)->isHover())
        {
            lastSelectedVertexIndex = distance(verteces.begin(), it);
            return true;
        }
    }

    return false;

    Q_UNUSED(pos)
}

