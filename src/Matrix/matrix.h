#pragma once

#include <QObject>
#include <QSpinBox>
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
    void addEdge(Edge *edge);
    void removeEdge(const Edge *edge);

private:
    void createCell(int row, int column, int value);

private:
    QTableWidget *table;

    QStringList verticalHeader;
    QStringList horizontalHeader;

    std::vector<const Vertex*> verteces;
    std::vector<const Edge*> edges;
};

