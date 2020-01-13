#pragma once

#include <QObject>
#include <QTableWidget>
#include "src/Graph/vertex.h"
#include "src/Graph/edge.h"

class Matrix : public QObject
{
    Q_OBJECT
public:
    explicit Matrix(QObject *parent = nullptr);

    void setTable(QTableWidget *table);

public slots:
    void addVertex(const Vertex *vertex);
    void removeVertex(const Vertex *vertex);


private:
    QTableWidget *table;

    QStringList verticalHeader;

    std::vector<const Vertex*> verteces;
};

