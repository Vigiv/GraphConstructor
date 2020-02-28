#include "search.h"


Search::Search(QObject *parent) : QObject(parent)
{

}

void Search::setSearchBox(QComboBox *searchBox)
{
    this->searchBox = searchBox;
}

void Search::setVertecesBox(QComboBox *vertecesBox)
{
    this->vertecesBox = vertecesBox;
}

void Search::dfs(Vertex *start)
{
    used[start] = 1;
    QList<Vertex *> adjacent = getAdjacent(start);
    for (auto it = adjacent.cbegin(); it != adjacent.cend(); ++it)
        if(!used[*it])
        {
            (*it)->setSelected(true);
            (*it)->update();
            dfs(*it);
        }

}

void Search::search()
{
    if (!verteces.isEmpty())
    {
        int id = vertecesBox->currentData().toInt();

        for (auto it = verteces.cbegin(); it != verteces.cend(); ++it)
        {
            if ((*it)->getId() == id)
            {
                dfs(*it);
                break;
            }
        }

        used.clear();
    }
}

void Search::addVertex(Vertex *vertex)
{
    verteces.push_back(vertex);
    vertecesBox->addItem(vertex->getName(), vertex->getId());

}

void Search::removeVertex(Vertex *vertex)
{
    verteces.removeOne(vertex);
    int index = vertecesBox->findData(vertex->getId());
    vertecesBox->removeItem(index);
}

void Search::addEdge(Edge *edge)
{
    edges.push_back(edge);
}

void Search::removeEdge(Edge *edge)
{
    edges.removeOne(edge);
}

QList<Vertex *> Search::getAdjacent(Vertex *vertex) const
{
    QList<Vertex *> result;

    for (auto it = edges.cbegin(); it != edges.cend(); ++it)
    {
        if ((*it)->getVerteces().first == vertex)
            result += (*it)->getVerteces().second;
        if ((*it)->getVerteces().second == vertex)
            result += (*it)->getVerteces().first;
    }

    return result;
}
