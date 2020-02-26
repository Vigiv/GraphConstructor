#pragma once
#include <QObject>
#include <QPushButton>
#include <QGraphicsView>

class ActionBoard : public QObject
{
    Q_OBJECT
public:
    explicit ActionBoard(QGraphicsView *view, QObject *parent = nullptr);

    void setGraphicsView(QGraphicsView *view);
    void resize(int width, int height);

private:
    void initViews();

private:
    QGraphicsView *view;

    QPushButton *addVertexBtn;
};

