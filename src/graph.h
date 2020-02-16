#pragma once
#include "src/Graph/vertex.h"
#include "src/Graph/edge.h"
#include <QObject>
#include <src/Graph/graphscene.h>
#include <src/Matrix/matrix.h>

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);

    void setTable(QTableWidget *table);
    void setView(QGraphicsView *view);

    void resize(int width, int height);

signals:
    void vertexAdded(Vertex* vertex);
    void edgeAdded(Edge* edge);


private:
    GraphScene *graphScene;
    Matrix *matrix;

    QList<Vertex*> verteces;
    QList<Edge*> edges;

    int lastVertexId { -1 };
};
