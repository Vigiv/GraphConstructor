#include "actionboard.h"
#include "src/constants.h"

ActionBoard::ActionBoard(QGraphicsView *view, QObject *parent) : QObject(parent)
{

}

void ActionBoard::setGraphicsView(QGraphicsView *view)
{
    this->view = view;
}

void ActionBoard::resize(int width, int height)
{
    addVertexBtn->move(view->x() + WINDOW_SPACING, view->height() - WINDOW_SPACING);
}

void ActionBoard::initViews()
{
    addVertexBtn = new QPushButton("Add vertex", view);
}
