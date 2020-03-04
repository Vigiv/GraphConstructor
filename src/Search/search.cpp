#include "search.h"

#include <QQueue>


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
            dfs(*it);
        }

}


void Search::bfs(Vertex *start)
{
    QQueue<Vertex*> queue;      // Очередь вершин
    queue.push_back(start);     //Добавляем стартовую вершину
    QMap<Vertex*, int> d;       //Вектор расстояний
    QMap<Vertex*, Vertex*> p;   //Вектор предков
    used[start] = 1;            //Стартовую вершину считаем посещенной
    p[start] = nullptr;         //У стартовой вершины нет предка
    while (!queue.empty()) {
        Vertex* v = queue.front();
        queue.pop_front();
        QList<Vertex *> adjacent = getAdjacent(v);
        for (int i = 0; i < adjacent.size(); ++i) {
            Vertex* to = adjacent[i];
            if (used[to] != 1) {    //Если вершина не посещена,
                used[to] = 1;       //посещаем ее
                queue.push_back(to);
                d[to] = d[v] + 1;   //Считаем расстояние до вершины
                p[to] = v;          //Запоминаем предка
                to->setSelected(true);
            }
        }
    }
}


void Search::search()
{
    if (!verteces.isEmpty())
    {
        reset();

        int id = vertecesBox->currentData().toInt();
        Vertex *start = nullptr;

        //get start vertex
        for (auto it = verteces.cbegin(); it != verteces.cend(); ++it)
        {
            if ((*it)->getId() == id)
            {
                start = *it;
                break;
            }
        }

        //choose search
        if (searchBox->currentText() == "dfs")
            dfs(start);
        else if (searchBox->currentText() == "bfs")
            bfs(start);


        used.clear();
    }
}

void Search::reset()
{
    for (auto it = verteces.cbegin(); it != verteces.cend(); ++it)
    {
        (*it)->setSelected(false);
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
