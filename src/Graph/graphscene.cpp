#include "graphscene.h"

#include <QGraphicsView>
#include <QMenu>

GraphScene::GraphScene(QObject *parent) : QObject(parent)
{
    scene = new QGraphicsScene(parent);
}

void GraphScene::setGraphicsView(QGraphicsView *view)
{
    this->view = view;
    this->view->setScene(scene);

    connect(view, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
}

void GraphScene::resize(int width, int height)
{
    view->resize(width / 2 - 2 * WINDOW_SPACING, height - 4 * WINDOW_SPACING);
    scene->setSceneRect(view->x(), view->y(),
                        view->width() - 2 * WINDOW_SPACING, view->height() - 4 * WINDOW_SPACING);
}

void GraphScene::createVertexAction()
{
    addVertex(mousePos);
}

void GraphScene::removeVertexAction()
{
    removeVertex();
}

void GraphScene::removeEdgesAction()
{
    removeEdges();
}

void GraphScene::connectVertexAction()
{
    isSelectedFirstVertex = true;
}

void GraphScene::moveVerteces()
{
    for (auto it = edges.cbegin(); it != edges.cend(); ++it)
        (*it)->update();
}

void GraphScene::vertexSelected(Vertex *vertex)
{
    if (isSelectedFirstVertex)
    {
        addEdge(vertex, lastVertex);
        isSelectedFirstVertex = false;
    }
}

void GraphScene::addVertex(const QPoint &pos)
{
    Vertex *vertex = new Vertex(this);
    vertex->setPos(pos);
    vertex->setId(++lastVertexId);
    vertex->setName("v" + QString::number(lastVertexId));

    verteces.push_back(vertex);
    scene->addItem(vertex);
    lastVertex = vertex;

    connect(vertex, SIGNAL(moveVerteces()), this, SLOT(moveVerteces()));
    connect(vertex, SIGNAL(vertexSelected(Vertex *)), this, SLOT(vertexSelected(Vertex *)));
    emit(vertexAdded(vertex));
}

void GraphScene::removeVertex()
{
    emit(vertexRemoved(lastVertex));

    removeVertex(lastVertex);
}

void GraphScene::addEdge(Vertex *first, Vertex *second)
{
    if (first != second && !isConnected(first, second))
    {
        Edge *edge = new Edge(scene);
        edge->setVerteces(first, second);
        edge->setId(++lastEdgeId);
        edge->setName("e" + QString::number(lastEdgeId));
        edges.push_back(edge);
        scene->addItem(edge);

        emit(edgeAdded(edge));
    }
}

void GraphScene::removeEdges()
{
    QList<Edge*> remove;
    for (auto it = edges.cbegin(); it != edges.cend(); ++it)
    {
        if ((*it)->getVerteces().first == lastVertex || (*it)->getVerteces().second == lastVertex)
        {            
            remove.push_back(*it);
        }
    }

    for (auto it = remove.begin(); it != remove.end(); ++it)
    {
        emit(edgeRemoved(*it));
        removeEdge(*it);
    }
}

void GraphScene::showContextMenu(const QPoint &pos)
{
    QMenu *menu = new QMenu(view);
    mousePos = pos;
    //empty field
    if(!pointIsVertex(pos))
    {
        QAction *createVertex = new QAction(tr("Create vertex"), this);
        connect(createVertex, SIGNAL(triggered()), this, SLOT(createVertexAction()));
        menu->addAction(createVertex);
    }
    //vertex
    else
    {
        QAction *removeVertex = new QAction(tr("Remove vertex"), this);
        connect(removeVertex, SIGNAL(triggered()), this, SLOT(removeVertexAction()));
        menu->addAction(removeVertex);

        QAction *removeEdges = new QAction(tr("Remove edges"), this);
        connect(removeEdges, SIGNAL(triggered()), this, SLOT(removeEdgesAction()));
        menu->addAction(removeEdges);

        QAction *connectVertex = new QAction(tr("Connect vertex with"), this);
        connect(connectVertex, SIGNAL(triggered()), this, SLOT(connectVertexAction()));
        menu->addAction(connectVertex);
    }

    menu->popup(view->viewport()->mapToGlobal(pos));
}

void GraphScene::removeEdge(Edge *edge)
{
    scene->removeItem(edge);
    edges.removeOne(edge);
}

void GraphScene::removeVertex(Vertex *vertex)
{
    removeEdges();

    scene->removeItem(vertex);
    verteces.removeOne(vertex);
}

bool GraphScene::pointIsVertex(const QPoint &pos)
{
    for (auto it = verteces.cbegin(); it != verteces.cend(); ++it)
    {
        if ((*it)->isHover())
        {
            vertexSelected(*it);
            lastVertex = *it;
            return true;
        }
    }

    isSelectedFirstVertex = false;
    return false;

    Q_UNUSED(pos)
}

bool GraphScene::isConnected(const Vertex *first, const Vertex *second) const
{
    for (auto it = edges.cbegin(); it != edges.cend(); ++it)
    {
        if ((*it)->getVerteces().first == first && (*it)->getVerteces().second == second)
            return true;
        if ((*it)->getVerteces().first == second && (*it)->getVerteces().second == first)
            return true;
    }

    return false;
}




