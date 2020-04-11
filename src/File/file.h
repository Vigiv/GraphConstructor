#pragma once
#include <QGraphicsView>
#include <QObject>

class File : public QObject
{
    Q_OBJECT
public:
    explicit File(QObject *parent = nullptr);

    void setWidgetParent(QWidget *parent = nullptr);
    void setGraphicsView(QGraphicsView *view);

public slots:
    void saveToFile();

signals:


private:
    QWidget *parent;
    QGraphicsView *view;
};

