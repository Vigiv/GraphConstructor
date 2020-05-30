#include "edge.h"
#include "vertex.h"

#include <QComboBox>
#include <QObject>

class Topology : public QObject
{
    Q_OBJECT
public:
    explicit Topology(QObject *parent = nullptr);

    void setTopologyBox(QComboBox *topologyBox);
    void addLinkToVerteces(QList<Vertex *> *verteces);
    void addLinkToEdges(QList<Edge *> *edges);

    bool isStarTopology() const;
    bool isCircleTopology() const;

    void updateGraphSceneSize(int width, int height);

public slots:
    void toTopology();

private:
    void toStar();
    void toCircle();

private:
    int graphSceneWidth;
    int graphSceneHeight;
    QComboBox *topologyBox;

    QList<Vertex *> *verteces;
    QList<Edge *> *edges;
};


