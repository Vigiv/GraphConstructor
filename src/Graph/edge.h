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
    void setFirst(Vertex *first);
    void setSecond(Vertex *second);
    void setName(const QString &name);
    void setId(int id);

    Vertex *first() const { return firstVertex; }
    Vertex *second() const { return secondVertex; }

    QRectF boundingRect() const override;
    std::pair<Vertex *, Vertex *> getVerteces() const;
    QString getName() const {return name; }
    int getId() const { return id; }

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    Vertex *firstVertex{nullptr};
    Vertex *secondVertex{nullptr};
    QPointF firstPos;
    QPointF secondPos;

    QString name;
    int id;
};

#endif // EDGE_H
