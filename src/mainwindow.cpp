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

    graphScene = new GraphScene(this);
    graphScene->setGraphicsView(ui->graph);

    matrix = new Matrix(this);
    matrix->setTable(ui->matrix);

    search = new Search(this);
    search->setSearchBox(ui->searchBox);
    search->setVertecesBox(ui->vertecesBox);

    file = new File(this);
    file->setWidgetParent(parent);
    file->setGraphicsView(ui->graph);


    ui->graph->setRenderHint(QPainter::Antialiasing);
    ui->graph->setCacheMode(QGraphicsView::CacheBackground);
    ui->graph->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graph->setContextMenuPolicy(Qt::CustomContextMenu);

    //main window buttons -> graphScene
    connect(ui->addVertexBtn, SIGNAL(clicked()), graphScene, SLOT(createVertexAction()));
    connect(ui->addEdgeBtn, SIGNAL(clicked()), graphScene, SLOT(addEmptyEdge()));

    //graphScene -> matrix
    connect(graphScene, SIGNAL(vertexAdded(Vertex*)), matrix, SLOT(addVertex(Vertex*)));
    connect(graphScene, SIGNAL(vertexRemoved(Vertex*)), matrix, SLOT(removeVertex(Vertex*)));
    connect(graphScene, SIGNAL(edgeAdded(Edge*)), matrix, SLOT(addEdge(Edge*)));
    connect(graphScene, SIGNAL(edgeRemoved(Edge*)), matrix, SLOT(removeEdge(Edge*)));

    //graphScene -> searh
    connect(graphScene, SIGNAL(vertexAdded(Vertex*)), search, SLOT(addVertex(Vertex*)));
    connect(graphScene, SIGNAL(vertexRemoved(Vertex*)), search, SLOT(removeVertex(Vertex*)));
    connect(graphScene, SIGNAL(edgeAdded(Edge*)), search, SLOT(addEdge(Edge*)));
    connect(graphScene, SIGNAL(edgeRemoved(Edge*)), search, SLOT(removeEdge(Edge*)));


    //button -> search
    connect(ui->searchBtn, SIGNAL(clicked()), search, SLOT(search()));
    connect(ui->resetBtn, SIGNAL(clicked()), search, SLOT(reset()));


    //menubar -> file
    connect(ui->actionSaveAs, SIGNAL(triggered()), file, SLOT(saveToFile()));
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

