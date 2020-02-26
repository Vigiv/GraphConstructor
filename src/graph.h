#pragma once
#include "src/Graph/vertex.h"
#include "src/Graph/edge.h"
#include <QObject>
#include <src/Graph/graphscene.h>
#include <src/Matrix/matrix.h>
#include <src/ActionBoard/actionboard.h>

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);

    void setTable(QTableWidget *table);
    void setGraphView(QGraphicsView *view);

signals:
    void vertexAdded(Vertex* vertex);
    void edgeAdded(Edge* edge);


private:
    GraphScene *graphScene;
    Matrix *matrix;
};
