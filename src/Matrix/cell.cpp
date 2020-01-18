#include "cell.h"

#include <QDebug>

Cell::Cell(QObject *objParent, QWidget *widgetParent) : QObject(objParent)
{
    spinBox = new QSpinBox(widgetParent);

    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(changed(int)));
}

void Cell::setState(Cell::State state)
{
    this->state = state;

    switch (state) {
    case State::EMPTY:
        setColor(Qt::white);
        spinBox->setRange(0, 1);
        break;
    case State::VERTEX:
        setColor(Qt::green);
        spinBox->setRange(0, 1);
        break;
    case State::OCCUPY:
        setColor(QColor(205, 92, 92));
        spinBox->setRange(0, 0);
        break;

    }
}

void Cell::setValue(int value)
{
    spinBox->setValue(value);
}

void Cell::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Base, color);
    spinBox->setPalette(palette);
}

QSpinBox *Cell::getWidget() const
{
    return spinBox;
}

void Cell::changed(int)
{
    emit(cellChanged(spinBox));
}
