#pragma once
#include <QGraphicsScene>
#include <QObject>
#include "src/Graph/vertex.h"
#include "src/Graph/edge.h"

class GraphScene : public QObject
{
    Q_OBJECT
public:
    explicit GraphScene(QObject *parent = nullptr);

    void setGraphicsView(QGraphicsView *view);
    void resize(int width, int height);

    bool pointIsVertex(const QPoint &pos);
    bool isConnected(const Vertex *first, const Vertex *second) const;
    QGraphicsScene *getScene() const { return scene; }

public slots:
    void createVertexAction();
    void removeVertexAction();
    void removeEdgesAction();
    void connectVertexAction();

    void moveVerteces();
    void vertexSelected(Vertex* vertex);
    void showContextMenu(const QPoint& pos);

    void removeEdge(Edge *edge);
    void removeVertex(Vertex *vertex);

private slots:
    void addVertex(const QPoint& pos);
    void removeVertex();
    void addEdge(Vertex *first, Vertex* second);
    void removeEdges();


signals:
    void vertexAdded(Vertex *vertex);
    void vertexRemoved(Vertex *vertex);
    void edgeAdded(Edge *edge);
    void edgeRemoved(Edge *edge);

private:
    QList<Vertex*> verteces;
    QList<Edge*> edges;

    Vertex *lastVertex { nullptr };

    QGraphicsView *view;
    QGraphicsScene *scene;
    QPoint mousePos;
    bool isSelectedFirstVertex { false };

    int lastVertexId{-1};
    int lastEdgeId{-1};
};

