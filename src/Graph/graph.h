#pragma once
#include <QGraphicsScene>
#include <QObject>
#include "src/Graph/vertex.h"
#include "src/Graph/edge.h"

class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);

    void setScene(QGraphicsScene *scene);
    void setMousePos(const QPoint &pos);

    bool pointIsVertex(const QPoint &pos);
    bool isConnected(const Vertex *first, const Vertex *second) const;


public slots:
    void makeVertex();
    void removeVertex();
    void removeEdges();
    void connectVerteces();

    void moveVerteces();
    void vertexSelected(Vertex *vertex);

signals:
    void vertexAdded(const Vertex *vertex);
    void vertexRemoved(const Vertex *vertex);


private:
    Vertex *lastSelected();
    Vertex *prelastSelected();

private:
    std::vector<Vertex*> vertecesHistory;
    std::vector<Edge*> edges;

    QGraphicsScene *scene;
    QPoint mousePos;
    bool isSelectedFirstVertex{false};

    int lastVertexId{-1};
};

