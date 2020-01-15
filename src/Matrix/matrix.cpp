#include "matrix.h"

#include <QSpinBox>


Matrix::Matrix(QObject *parent) : QObject(parent)
{

}

void Matrix::setTable(QTableWidget *table)
{
    this->table = table;
}

void Matrix::addVertex(const Vertex *vertex)
{
    verteces.push_back(vertex);

    int rows = table->rowCount();
    table->setRowCount(++rows);

    verticalHeader.append(vertex->getName());
    table->setVerticalHeaderLabels(verticalHeader);

    for (int i = 0; i < table->columnCount(); ++i)
    {
        QSpinBox *spinBox = new QSpinBox(table);
        spinBox->setValue(0);
        spinBox->setRange(0, 1);
        table->setCellWidget(rows - 1, i, spinBox);
    }
}

void Matrix::removeVertex(const Vertex *vertex)
{
    for (auto it = verteces.begin(); it != verteces.end(); ++it)
    {
        if (*it == vertex)
        {
            verteces.erase(it);
            break;
        }
    }

    int index = verticalHeader.indexOf(vertex->getName());
    verticalHeader.removeAt(index);
    table->removeRow(index);
}

void Matrix::addEdge(Edge *edge)
{
    edges.push_back(edge);

    int columns = table->columnCount();
    table->setColumnCount(++columns);

    horizontalHeader.append(edge->getName());
    table->setHorizontalHeaderLabels(horizontalHeader);

    for (int i = 0; i < table->rowCount(); ++i)
    {
        QSpinBox *spinBox = new QSpinBox(table);
        spinBox->setValue(0);
        spinBox->setRange(0, 1);
        table->setCellWidget(i, columns - 1, spinBox);
    }

    //устанавливает '1' на пересечении вершин и ребер
    for (auto it = verteces.begin(); it != verteces.end(); ++it)
    {
        if (*it == edge->getVerteces().first || *it == edge->getVerteces().second)
        {
            QSpinBox *spinBox = new QSpinBox(table);
            spinBox->setValue(1);
            spinBox->setRange(0, 1);

            table->setCellWidget((*it)->getId(), columns - 1, spinBox);
        }
    }

}

void Matrix::removeEdge(const Edge *edge)
{
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        if (*it == edge)
        {
            edges.erase(it);
            break;
        }
    }

    int index = horizontalHeader.indexOf(edge->getName());
    horizontalHeader.removeAt(index);
    table->removeColumn(index);
}
