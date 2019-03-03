#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMenu>
#include <QPoint>
#include "../mainmodel.h"

class GraphView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphView(QWidget *parent = nullptr);
    void setModel(MainModel *model);
    QPointF getCenterOnScene();
public slots:
    void selectAll();
    void createNode(NodeModel *nodeModel);
    void createLink(LinkModel *linkModel, NodeModel *nodeModelOne, NodeModel *nodeModelTwo);
private:
    MainModel *model;
    QGraphicsScene *scene;
};

#endif // GRAPHVIEW_H
