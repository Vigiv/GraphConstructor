#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Graph/vertex.h"
#include "src/constants.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    matrix = new Matrix(this);
    matrix->setTable(ui->tableWidget);
    connect(&graph, SIGNAL(vertexAdded(const Vertex*)), matrix, SLOT(addVertex(const Vertex*)));
    connect(&graph, SIGNAL(vertexRemoved(const Vertex*)), matrix, SLOT(removeVertex(const Vertex*)));
    connect(&graph, SIGNAL(edgeAdded(Edge*)), matrix, SLOT(addEdge(Edge*)));
    connect(&graph, SIGNAL(edgeRemoved(const Edge*)), matrix, SLOT(removeEdge(const Edge*)));

    scene = new QGraphicsScene(this);
    graph.setScene(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->resize(width() / 2 - 2 * WINDOW_SPACING, height() - 4 * WINDOW_SPACING);
    ui->tableWidget->resize(width() / 2 - 2 * WINDOW_SPACING, height() / 2 - 2 * WINDOW_SPACING);
    ui->tableWidget->move(width() / 2 + WINDOW_SPACING, height() / 2 - WINDOW_SPACING);
    scene->setSceneRect(ui->graphicsView->x(),
                        ui->graphicsView->y(),
                        ui->graphicsView->width() - 2 * WINDOW_SPACING,
                        ui->graphicsView->height() - 4 * WINDOW_SPACING);

    Q_UNUSED(event)
}



void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu *menu = new QMenu(this);
    graph.setMousePos(pos);
    //empty field
    if(!graph.pointIsVertex(pos))
    {
        QAction *createVertex = new QAction(tr("Create vertex"), this);
        connect(createVertex, SIGNAL(triggered()), &graph, SLOT(makeVertex()));
        menu->addAction(createVertex);
    }
    //vertex
    else
    {
        QAction *removeVertex = new QAction(tr("Remove vertex"), this);
        connect(removeVertex, SIGNAL(triggered()), &graph, SLOT(removeVertex()));
        menu->addAction(removeVertex);

        QAction *removeEdges = new QAction(tr("Remove edges"), this);
        connect(removeEdges, SIGNAL(triggered()), &graph, SLOT(removeEdges()));
        menu->addAction(removeEdges);

        QAction *connectVertex = new QAction(tr("Connect vertex with"), this);
        connect(connectVertex, SIGNAL(triggered()), &graph, SLOT(connectVerteces()));
        menu->addAction(connectVertex);
    }

    menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
}

