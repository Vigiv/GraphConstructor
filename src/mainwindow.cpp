#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Graph/vertex.h"
#include "src/constants.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graph = new Graph(parent);
    graph->setView(ui->graphicsView);
    graph->setTable(ui->tableWidget);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    graph->resize(width(), height());

    Q_UNUSED(event)
}

