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
    void resize(int width, int height);

public slots:
    void addVertex(Vertex *vertex);
    void removeVertex(Vertex *vertex);
    void addEdge(Edge *edge);
    void removeEdge(Edge *edge);

    void cellChanged(Cell *cell);

signals:
    void vertexRemoved(Vertex* vertex);
    void edgeRemoved(Edge* edge);

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

    QList<Vertex*> verteces;
    QList<Edge*> edges;

    QPoint mousePos;

    QMap<QPair<int, int>, Cell*> cells;
};

