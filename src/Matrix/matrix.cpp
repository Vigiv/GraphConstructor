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

