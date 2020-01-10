#pragma once

#include <QObject>
#include <QGraphicsItem>

class Vertex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Vertex(QObject *parent = nullptr);

    bool isHover() const { return hover; }

    QRectF boundingRect() const override;

signals:
    void moveVerteces();
    void vertexSelected(Vertex *);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    bool hover {false};
};


