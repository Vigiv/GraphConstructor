#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include "src/Graph/graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void resizeEvent(QResizeEvent *event) override;

    void showContextMenu(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Graph graph;
};
