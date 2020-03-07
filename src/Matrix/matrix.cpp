#include "matrix.h"

#include "src/Matrix/cell.h"

Matrix::Matrix(QObject *parent) : QObject(parent)
{

}

void Matrix::setTable(QTableWidget *table)
{
    this->table = table;
}

void Matrix::addVertex(Vertex *vertex)
{
    verteces.push_back(vertex);

    int rows = table->rowCount();
    table->setRowCount(++rows);

    verticalHeader.append(vertex->getName());
    table->setVerticalHeaderLabels(verticalHeader);


    for (int i = 0; i < table->columnCount(); ++i)
    {
        if (rows - 2 > 0 && cells[QPair<int, int>(rows - 2, i)]->getState() != Cell::State::EMPTY)
            createCell(rows - 1, i, Cell::State::OCCUPY);
        else
            createCell(rows - 1, i, Cell::State::EMPTY);
    }
}

void Matrix::removeVertex(Vertex *vertex)
{
    verteces.removeOne(vertex);

    int row = verticalHeader.indexOf(vertex->getName());
    verticalHeader.removeAt(row);

    for (int c = 0; c < table->columnCount(); ++c)
    {
        for (int r = row; r < table->rowCount() - 1; ++r)
        {
            Cell *following = cells[QPair<int, int>(r + 1, c)];
            createCell(r, c, following->getState());
        }
    }

    table->removeRow(table->rowCount() - 1);
    table->setVerticalHeaderLabels(verticalHeader);
}

void Matrix::addEdge(Edge *edge)
{
    edges.push_back(edge);

    int columns = table->columnCount();
    table->setColumnCount(++columns);

    horizontalHeader.append(edge->getName());
    table->setHorizontalHeaderLabels(horizontalHeader);

    int firstRow = -1;
    int secondRow = -1;

    if (edge->getVerteces().first != nullptr)
        firstRow = verticalHeader.indexOf(edge->getVerteces().first->getName());

    if (edge->getVerteces().second != nullptr)
        secondRow = verticalHeader.indexOf(edge->getVerteces().second->getName());

    for (int i = 0; i < table->rowCount(); ++i)
    {
        if (firstRow == -1 || secondRow == -1)
            createCell(i, columns - 1, Cell::State::EMPTY);
        else if (i == firstRow || i == secondRow)
            createCell(i, columns - 1, Cell::State::VERTEX);
        else
            createCell(i, columns - 1, Cell::State::OCCUPY);
    }

    table->resizeColumnToContents(columns - 1);
}

void Matrix::removeEdge(Edge *edge)
{   
    edges.removeOne(edge);

    int column = horizontalHeader.indexOf(edge->getName());
    horizontalHeader.removeAt(column);

    for (int r = 0; r < table->rowCount(); ++r)
    {
        for (int c = column; c < table->columnCount() - 1; ++c)
        {
            Cell *following = cells[QPair<int, int>(r, c + 1)];
            createCell(r, c, following->getState());
        }
    }

    table->removeColumn(table->columnCount() - 1);
    table->setHorizontalHeaderLabels(horizontalHeader);
}

void Matrix::cellChanged(Cell *cell)
{
    cell->setState(Cell::State::EMPTY);
    setOccupyToEmpty(table->currentColumn());
    Edge *currentEdge = nullptr;

    //get current edge
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        if ((*it)->getName() == horizontalHeader[table->currentColumn()])
        {
            currentEdge = *it;
            break;
        }
    }

    if (cell->getValue() == 0)
    {
        if (currentEdge->first() != nullptr && currentEdge->first()->getName() == verticalHeader[table->currentRow()])
            currentEdge->setFirst(nullptr);
        else
            currentEdge->setSecond(nullptr);

    }
    else if (cell->getValue() == 1)
    {
        cell->setState(Cell::State::VERTEX);

        QPair<int, int> rows = getVertexRows(table->currentColumn());

        QString firstName;
        QString secondName;
        if (rows.first != -1)
            firstName = verticalHeader[rows.first];
        if (rows.second != -1)
            secondName = verticalHeader[rows.second];
        Vertex *first = nullptr;
        Vertex *second = nullptr;


        for (auto it = verteces.cbegin(); it != verteces.cend(); ++it)
        {
            if ((*it)->getName() == firstName)
                first = *it;
            if ((*it)->getName() == secondName)
                second = *it;
        }

        if (currentEdge->first() == nullptr)
            currentEdge->setFirst(first);
        else
            currentEdge->setSecond(second);

        if (getVertecesCount(table->currentColumn()) == 1)
            setBlockedEmptyToOccupy(table->currentColumn());
        else if (getVertecesCount(table->currentColumn()) == 2)
            setAllEmptyToOccupy(table->currentColumn());
    }

    currentEdge->update(currentEdge->boundingRect());
}

void Matrix::createCell(int row, int column, Cell::State state)
{
    Cell *cell = new Cell(nullptr, table);
    if (state == Cell::State::VERTEX)
    {
        cell->setValue(1);
    }
    else if (state == Cell::State::OCCUPY)
    {
        cell->setValue(0);
    }
    else if (state == Cell::State::EMPTY)
    {
        cell->setValue(0);
    }

    cell->setState(state);

    connect(cell, SIGNAL(cellChanged(Cell *)), this, SLOT(cellChanged(Cell *)));


    if (cells.contains(QPair<int, int>(row, column)))
        cells.remove(QPair<int, int>(row, column));
    cells.insert(QPair<int, int>(row, column), cell);
    table->setCellWidget(row, column, cell->getWidget());
}

void Matrix::setOccupyToEmpty(int column)
{
    for (int row = 0; row < table->rowCount(); ++row)
    {
        Cell *cell = cells.value(QPair<int, int>(row, column));
        if (cell->getState() == Cell::State::OCCUPY)
        {
            if ((getVertecesCount(column) == 1 && !cellIsBlocked(row, column)) || getVertecesCount(column) == 0)
                cell->setState(Cell::State::EMPTY);
        }
    }
}

void Matrix::setAllEmptyToOccupy(int column)
{
    for (int row = 0; row < table->rowCount(); ++row)
    {
        Cell *cell = cells.value(QPair<int, int>(row, column));
        if (cell->getState() == Cell::State::EMPTY)
        {
            cell->setState(Cell::State::OCCUPY);
        }
    }
}

void Matrix::setBlockedEmptyToOccupy(int column)
{
    int row = table->currentRow();

    QVector<int> anotherRows = getAnotherVertecesRows(row);

    for (int i = 0; i < table->rowCount(); ++i)
    {
        if (anotherRows.contains(i))
            cells.value(QPair<int, int>(i, column))->setState(Cell::State::OCCUPY);
    }
}


QPair<int, int> Matrix::getVertexRows(int column) const
{
    QPair<int, int> rows { -1, -1 };

    for (int i = 0; i < table->rowCount(); ++i)
    {
        if (cells.value(QPair<int, int>(i, column))->getState() == Cell::State::VERTEX)
        {
            if (rows.first == -1)
                rows.first = i;
            else
                rows.second = i;
        }
    }

    return rows;
}

QVector<int> Matrix::getAnotherVertecesRows(int row) const
{
    QVector<int> another;

    for (int i = 0; i < table->columnCount(); ++i)
    {
        QPair<int, int> rows = getVertexRows(i);

        if (rows.first == row && rows.second != -1)
            another.push_back(rows.second);
        else if (rows.second == row)
            another.push_back(rows.first);
    }

    return another;
}

bool Matrix::cellIsBlocked (int row, int column) const
{
    for (int i = 0; i < table->columnCount(); ++i)
    {
        if (cells.value(QPair<int, int>(row, i))->getState() == Cell::State::VERTEX)
        {
            QPair<int, int> rows = getVertexRows(column);
            int vertexRow;
            if (rows.first != -1)
                vertexRow = rows.first;
            else
                vertexRow = rows.second;

            if (cells.value(QPair<int, int>(vertexRow, i))->getState() == Cell::State::VERTEX)
                return true;
        }
    }

    return false;
}

int Matrix::getVertecesCount(int column) const
{
    int count = 0;

    for (int row = 0; row < table->rowCount(); ++row)
        if (cells.value(QPair<int, int>(row, column))->getState() == Cell::State::VERTEX)
            count++;

    return count;
}
