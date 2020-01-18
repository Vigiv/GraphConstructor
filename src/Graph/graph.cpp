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
    Vertex *vertex = new Vertex(scene);
    vertex->setPos(mousePos);
    vertex->setId(++lastVertexId);
    vertex->setName("v" + QString::number(lastVertexId));

    connect(vertex, SIGNAL(moveVerteces()), this, SLOT(moveVerteces()));
    connect(vertex, SIGNAL(vertexSelected(Vertex*)), this, SLOT(vertexSelected(Vertex*)));

    vertexSelected(vertex);
    vertecesHistory.push_back(vertex);
    scene->addItem(vertex);

    emit(vertexAdded(vertex));
}

void Graph::removeVertex()
{
    Vertex *last = lastSelected();
    emit(vertexRemoved(last));

    removeEdges();

    /**************************************************************
     * удаляет последний выбранный Vertex и все его копии в истории
    ***************************************************************/
    for (auto it = vertecesHistory.begin(); it != vertecesHistory.end(); ++it)
    {
        if (*it == last)
        {
            vertecesHistory.erase(it);
            --it;
        }
    }

    scene->removeItem(last);
}

void Graph::removeEdges()
{
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        if ((*it)->getVerteces().first == lastSelected() || (*it)->getVerteces().second == lastSelected())
        {
            emit(edgeRemoved(*it));
            (*it)->~Edge();
            edges.erase(it);
            --it;
        }
    }
}
void Graph::connectVerteces()
{
    isSelectedFirstVertex = true;
}

void Graph::moveVerteces()
{
    for (auto it = edges.cbegin(); it != edges.cend(); ++it)
        (*it)->update();
}

void Graph::vertexSelected(Vertex *vertex)
{
    if (isSelectedFirstVertex) {
        Vertex *last = lastSelected();

        if (vertex != last && !isConnected(vertex, last))
        {
            Edge *edge = new Edge(scene);
            edge->setVerteces(vertex, last);
            edge->setId(++lastEdgeId);
            edge->setName("e" + QString::number(lastEdgeId));
            edges.push_back(edge);
            scene->addItem(edge);

            emit(edgeAdded(edge));
        }

        isSelectedFirstVertex = false;
    }

    vertecesHistory.push_back(vertex);
}

Vertex *Graph::lastSelected()
{
    if (!vertecesHistory.empty())
        return vertecesHistory[vertecesHistory.size() - 1];

    return nullptr;
}

Vertex *Graph::prelastSelected()
{
    int i = 2;
    while(vertecesHistory.size() >= i) {
        if (vertecesHistory[vertecesHistory.size() - i] != vertecesHistory[vertecesHistory.size() - 1])
            return vertecesHistory[vertecesHistory.size() - i];
        ++i;
    }

    return nullptr;
}

bool Graph::pointIsVertex(const QPoint &pos)
{
    for (auto it = vertecesHistory.begin(); it != vertecesHistory.end(); ++it)
    {
        if ((*it)->isHover())
        {
            vertexSelected(*it);
            return true;
        }
    }

    isSelectedFirstVertex = false;
    return false;

    Q_UNUSED(pos)
}

bool Graph::isConnected(const Vertex *first, const Vertex *second) const
{
    for (auto it = edges.cbegin(); it != edges.cend(); ++it)
    {
        if ((*it)->getVerteces().first == first && (*it)->getVerteces().second == second)
            return true;
        if ((*it)->getVerteces().first == second && (*it)->getVerteces().second == first)
            return true;
    }

    return false;
}

