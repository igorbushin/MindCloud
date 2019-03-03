#ifndef LINKLINKVIEW_H
#define LINKLINKVIEW_H

#include "node/nodemodel.h"
#include "link/linkmodel.h"
#include <QObject>
#include <QGraphicsLineItem>

class LinkView : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit LinkView(QObject *parent = nullptr);
    void setNodeModels(LinkModel *linkModel, NodeModel *srcNodeModel, NodeModel *dstNodeModel);
signals:
    void selectionChanged(bool isSelected);
public slots:
    void setSrcPosition(const QPointF &position);
    void setDstPosition(const QPointF &position);
    void deleteFromScene(QObject *object);
private:
    LinkModel *linkModel;
    NodeModel *srcNodeModel;
    NodeModel *dstNodeModel;
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
};

#endif // LINKLINKVIEW_H
