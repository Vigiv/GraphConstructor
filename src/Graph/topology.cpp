#include "topology.h"

#include <QDebug>
#include <QMessageBox>
#include <math.h>

Topology::Topology(QObject *parent) : QObject(parent)
{

}

void Topology::setTopologyBox(QComboBox *topologyBox)
{
    this->topologyBox = topologyBox;
}

void Topology::addLinkToVerteces(QList<Vertex *> *verteces)
{
    this->verteces = verteces;
}

void Topology::addLinkToEdges(QList<Edge *> *edges)
{
    this->edges = edges;
}

bool Topology::isStarTopology() const
{
    if (edges->isEmpty())
        return false;
    Vertex *center = nullptr;

    if(edges->first()->getVerteces().first == edges->last()->getVerteces().first)
        center = edges->first()->getVerteces().first;
    else if(edges->first()->getVerteces().first == edges->last()->getVerteces().second)
        center = edges->first()->getVerteces().first;
    else if(edges->first()->getVerteces().second == edges->last()->getVerteces().second)
        center = edges->first()->getVerteces().second;
    else if(edges->first()->getVerteces().second == edges->last()->getVerteces().first)
        center = edges->first()->getVerteces().second;
    else
        return false;

    for (auto it = edges->cbegin(); it != edges->cend(); ++it)
    {
        if ((*it)->first() != center && (*it)->second() != center)
            return false;
    }

    return true;
}

bool Topology::isCircleTopology() const
{
    if (edges->size() < 3)
        return false;

    QMap<Vertex*, int> count;

    for (auto it = edges->cbegin(); it != edges->cend(); ++it)
    {
        count[(*it)->first()]++;
        count[(*it)->second()]++;
    }

    for (auto it = count.cbegin(); it != count.cend(); ++it)
    {
        if (it.value() != 2)
            return false;
    }

    return true;
}

void Topology::updateGraphSceneSize(int width, int height)
{
    graphSceneWidth = width;
    graphSceneHeight = height;
}

void Topology::toTopology()
{
    qDebug() << topologyBox->currentText();
    if (topologyBox->currentText() == "star")
        toStar();
    else if (topologyBox->currentText() == "circle")
        toCircle();
}

void Topology::toStar()
{
    if (!isStarTopology())
    {
        QMessageBox::information(nullptr, "Converting", "Cannot convert to star");
        return;
    }


    Vertex *center = nullptr;

    if(edges->first()->getVerteces().first == edges->last()->getVerteces().first)
        center = edges->first()->getVerteces().first;
    else if(edges->first()->getVerteces().first == edges->last()->getVerteces().second)
        center = edges->first()->getVerteces().first;
    else if(edges->first()->getVerteces().second == edges->last()->getVerteces().second)
        center = edges->first()->getVerteces().second;
    else if(edges->first()->getVerteces().second == edges->last()->getVerteces().first)
        center = edges->first()->getVerteces().second;
    else
        qDebug() << "star topology error";

    center->setPos(graphSceneWidth/2, graphSceneHeight/2);
    double alpha = 360 / (verteces->size() - 1);
    int radius = qMin(graphSceneWidth, graphSceneHeight) / 4;
    double angle = 0;

    for (auto it = edges->cbegin(); it != edges->cend(); ++it)
    {
        double pi = 3.1415926535;
        double x = radius * std::sin(angle * pi / 180);
        double y = radius * std::cos(angle * pi / 180);

        (*it)->getAnotherVertex(center)->setPos(graphSceneWidth/2 + x, graphSceneHeight/2 - y);
        angle += alpha;
        (*it)->update();
    }
}

void Topology::toCircle()
{
    if (!isCircleTopology())
    {
        QMessageBox::information(nullptr, "Converting", "Cannot convert to circle");
        return;
    }

    double alpha = 360 / verteces->size();
    int radius = qMin(graphSceneWidth, graphSceneHeight) / 4;
    double angle = 0;
    double pi = 3.1415926535;

    Edge *edge = edges->first();
    Vertex *end = edge->first();
    Vertex *prev = edge->second();

    while(prev != end) {
        for (auto it = edges->cbegin(); it != edges->cend(); ++it)
        {
            if (*it == edge)
                continue;
            if ((*it)->first() == prev)
            {
                double x = radius * std::sin(angle * pi / 180);
                double y = radius * std::cos(angle * pi / 180);

                prev->setPos(graphSceneWidth/2 + x, graphSceneHeight/2 - y);
                angle += alpha;
                prev = (*it)->second();
                edge = *it;
                edge->update();
            }
            else if ((*it)->second() == prev)
            {
                double x = radius * std::sin(angle * pi / 180);
                double y = radius * std::cos(angle * pi / 180);

                prev->setPos(graphSceneWidth/2 + x, graphSceneHeight/2 - y);
                angle += alpha;
                prev = (*it)->first();
                edge = *it;
                edge->update();
            }

        }
    }

    double x = radius * std::sin(angle * pi / 180);
    double y = radius * std::cos(angle * pi / 180);

    end->setPos(graphSceneWidth/2 + x, graphSceneHeight/2 - y);
    edge->update();
}
