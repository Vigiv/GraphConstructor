#pragma once
#include <QObject>
#include "src/Graph/edge.h"
#include "src/Graph/vertex.h"
#include <QComboBox>

class Search : public QObject
{
    Q_OBJECT
public:
    explicit Search(QObject *parent = nullptr);

    void setSearchBox(QComboBox *searchBox);
    void setVertecesBox(QComboBox *vertecesBox);

    void dfs(Vertex *start);
    void bfs(Vertex *start);
    void findCycle(Vertex *start);



public slots:
    void search();
    void reset();

    void addVertex(Vertex *vertex);
    void removeVertex(Vertex *vertex);
    void addEdge(Edge *edge);
    void removeEdge(Edge *edge);

private:
    QList<Vertex*> getAdjacent(Vertex* vertex) const;

private:
    QList<Vertex*> verteces;
    QList<Edge*> edges;
    QMap<Vertex*, int> used;


    QComboBox *searchBox;
    QComboBox *vertecesBox;

};
