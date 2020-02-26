#include "graph.h"

Graph::Graph(QObject *parent) : QObject(parent)
{
    graphScene = new GraphScene(parent);

    matrix = new Matrix(parent);

    //graph scene -> matrix
    connect(graphScene, SIGNAL(vertexAdded(Vertex*)), matrix, SLOT(addVertex(Vertex*)));
    connect(graphScene, SIGNAL(vertexRemoved(Vertex*)), matrix, SLOT(removeVertex(Vertex*)));
    connect(graphScene, SIGNAL(edgeAdded(Edge*)), matrix, SLOT(addEdge(Edge*)));
    connect(graphScene, SIGNAL(edgeRemoved(Edge*)), matrix, SLOT(removeEdge(Edge*)));
}

void Graph::setTable(QTableWidget *table)
{
    matrix->setTable(table);
}

void Graph::setGraphView(QGraphicsView *view)
{
    graphScene->setGraphicsView(view);
}
