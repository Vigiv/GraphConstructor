#include "file.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

File::File(QObject *parent) : QObject(parent)
{

}

void File::setWidgetParent(QWidget *parent)
{
    this->parent = parent;
}

void File::setGraphicsView(QGraphicsView *view)
{
    this->view = view;
}

void File::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(parent,
        tr("Save graph"), "",
        tr("JPEG (*.jpg;*.jpeg;*.jpe;*.jfif);;PNG (*.png);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QImage image(fileName);
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        view->scene()->render(&painter);
        image.save(fileName);
    }
}
