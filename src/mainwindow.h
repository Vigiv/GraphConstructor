#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTableWidget>
#include <src/File/file.h>
#include "src/Graph/graphscene.h"
#include "src/Matrix/matrix.h"
#include "src/Search/search.h"

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


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    GraphScene *graphScene;
    Matrix *matrix;
    Search *search;
    File *file;
};
