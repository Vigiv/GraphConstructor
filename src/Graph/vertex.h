#pragma once

#include <QObject>
#include <QGraphicsItem>

class Vertex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Vertex(QObject *parent = nullptr);

    QRectF boundingRect() const override;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};


