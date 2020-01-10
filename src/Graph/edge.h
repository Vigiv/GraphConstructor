#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QObject>
#include "src/constants.h"
#include "src/Graph/vertex.h"


class Edge : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Edge(QObject *parent = nullptr);

    void setVerteces(Vertex *first, Vertex *second);

    QRectF boundingRect() const override;
    std::pair<Vertex *, Vertex *> getVerteces() const;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    Vertex *firstVertex{nullptr};
    Vertex *secondVertex{nullptr};
};

#endif // EDGE_H
