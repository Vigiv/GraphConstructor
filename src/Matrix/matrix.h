#pragma once

#include <QObject>
#include <QSpinBox>
#include <QTableWidget>
#include "src/Graph/vertex.h"
#include "src/Graph/edge.h"
#include "src/Matrix/cell.h"

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

    void cellChanged(Cell *cell);

private:
    void createCell(int row, int column, int value);

    void setOccupyToEmpty(int column);
    void setAllEmptyToOccupy(int column);
    void setBlockedEmptyToOccupy(int column);

    QPair<int, int> getVertexRows(int column) const;
    QVector<int> getAnotherVertecesRows(int row) const;
    bool cellIsBlocked(int row, int column) const;
    int getVertecesCount(int column) const;

private:
    QTableWidget *table;

    QStringList verticalHeader;
    QStringList horizontalHeader;

    std::vector<const Vertex*> verteces;
    std::vector<const Edge*> edges;

    QMap<QPair<int, int>, Cell*> cells;
};

