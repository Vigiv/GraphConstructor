#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Graph/vertex.h"
#include "src/constants.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graph->resize(467, 493);

    scene = new QGraphicsScene(ui->graph);
    ui->graph->setScene(scene);

    graphScene = new GraphScene(parent);
    graphScene->setGraphicsView(ui->graph);

    matrix = new Matrix(parent);
    matrix->setTable(ui->matrix);


    ui->graph->setRenderHint(QPainter::Antialiasing);
    ui->graph->setCacheMode(QGraphicsView::CacheBackground);
    ui->graph->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graph->setContextMenuPolicy(Qt::CustomContextMenu);

    //graphScene -> matrix
    connect(graphScene, SIGNAL(vertexAdded(Vertex*)), matrix, SLOT(addVertex(Vertex*)));
    connect(graphScene, SIGNAL(vertexRemoved(Vertex*)), matrix, SLOT(removeVertex(Vertex*)));
    connect(graphScene, SIGNAL(edgeAdded(Edge*)), matrix, SLOT(addEdge(Edge*)));
    connect(graphScene, SIGNAL(edgeRemoved(Edge*)), matrix, SLOT(removeEdge(Edge*)));


    //main window buttons -> graphScene/matrix
    connect(ui->addVertexBtn, SIGNAL(clicked()), graphScene, SLOT(createVertexAction()));
    connect(ui->addEdgeBtn, SIGNAL(clicked()), graphScene, SLOT(addEmptyEdge()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graph->scene()->setSceneRect(ui->graph->rect());

    Q_UNUSED(event)
}

