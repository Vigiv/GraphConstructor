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

    bool pointIsVertex(const QPoint &pos) const;

public slots:
    void makeVertex();

private:
    QVector<Vertex*> verteces;
    QGraphicsScene *scene;

    QPoint mousePos;
};

