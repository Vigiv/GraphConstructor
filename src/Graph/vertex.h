#pragma once

#include <QObject>
#include <QGraphicsItem>

class Vertex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Vertex(QObject *parent = nullptr);

    void setName(const QString &name);
    void setId(int id);
    void setSelected(bool selected);

    bool isHover() const { return hover; }
    QString getName() const {return name; }
    int getId() const { return id; }

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
    bool hover { false };
    bool isSelected { false };
    QString name;
    int id;
};

