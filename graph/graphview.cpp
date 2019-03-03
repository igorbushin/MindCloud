#include "graphview.h"
#include "node/nodeview.h"
#include "link/linkview.h"
#include <QContextMenuEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

GraphView::GraphView(QWidget *parent)
{
    Q_UNUSED(parent);
    scene = new QGraphicsScene(this);
    setScene(scene);
}

void GraphView::setModel(MainModel *model)
{
    this->model = model;
    QObject::connect(model, &MainModel::nodeCreated, this, &GraphView::createNode);
    QObject::connect(model, &MainModel::linkCreated, this, &GraphView::createLink);
}

QPointF GraphView::getCenterOnScene()
{
    return mapToScene(viewport()->rect().center());
}

void GraphView::selectAll()
{
    auto items = this->items();
    foreach(auto item , items) {
        item->setSelected(true);
    }
}

void GraphView::createNode(NodeModel *nodeModel)
{
    NodeView *nodeView = new NodeView;
    nodeView->setModel(nodeModel);
    QObject::connect(nodeView, &NodeView::selectionChanged, model, &MainModel::changeSelectedNode);
    scene->addItem(nodeView);    
}

void GraphView::createLink(LinkModel *linkModel, NodeModel *nodeModelOne, NodeModel *nodeModelTwo)
{
    LinkView *linkView = new LinkView;
    linkView->setNodeModels(linkModel, nodeModelOne, nodeModelTwo);
    scene->addItem(linkView);
}
