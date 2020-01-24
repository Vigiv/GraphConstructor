#include "matrix.h"

#include "src/Matrix/cell.h"


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
        createCell(rows - 1, i, 0);
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

    int firstRow = verticalHeader.indexOf(edge->getVerteces().first->getName());
    int secondRow = verticalHeader.indexOf(edge->getVerteces().second->getName());

    for (int i = 0; i < table->rowCount(); ++i)
    {
        if (i == firstRow || i == secondRow)
            createCell(i, columns - 1, 1);
        else
            createCell(i, columns - 1, 0);
    }

    table->resizeColumnToContents(columns - 1);
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

void Matrix::cellChanged(Cell *cell)
{
    if (cell->getValue() == 0)
        updateColumn(table->currentColumn());
}

void Matrix::createCell(int row, int column, int value)
{
    Cell *cell = new Cell(nullptr, table);
    cell->setValue(value);
    if (value == 1)
        cell->setState(Cell::State::VERTEX);
    else
        cell->setState(Cell::State::OCCUPY);

    connect(cell, SIGNAL(cellChanged(Cell *)), this, SLOT(cellChanged(Cell *)));

    if (!cells.contains(QPair<int, int>(row, column)))
        cells.insert(QPair<int, int>(row, column), cell);
    table->setCellWidget(row, column, cell->getWidget());
}

void Matrix::updateColumn(int column)
{
    for (int row = 0; row < table->rowCount(); ++row)
    {
        Cell *cell = cells.value(QPair<int, int>(row, column));
        if (cell->getState() == Cell::State::OCCUPY && !cellIsBlocked(row))
        {
            cell->setState(Cell::State::EMPTY);
        }
    }
}

bool Matrix::cellIsBlocked (int row) const
{
    for (int i = 0; i < table->columnCount(); ++i)
    {
        if (cells.value(QPair<int, int>(row, i))->getState() == Cell::State::VERTEX)
            return true;
    }

    return false;
}
