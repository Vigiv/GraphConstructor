#pragma once
#include <QGraphicsScene>
#include <QObject>
#include "src/Graph/vertex.h"


class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = nullptr);

    void setScene(QGraphicsScene *scene);
    void setMousePos(const QPoint &pos);

    bool pointIsVertex(const QPoint &pos);


public slots:
    void makeVertex();
    void removeVertex();

private:
    std::vector<Vertex*> verteces;
    QGraphicsScene *scene;

    long long lastSelectedVertexIndex{-1};

    QPoint mousePos;
};

