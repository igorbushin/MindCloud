#include "linkview.h"
#include <QGraphicsScene>

LinkView::LinkView(QObject *parent) : QObject(parent)
{
    setFlag(ItemIsSelectable);
    setZValue(-1.0);
}

void LinkView::setNodeModels(LinkModel *linkModel, NodeModel *srcNodeModel, NodeModel *dstNodeModel)
{
    this->linkModel = linkModel;
    this->srcNodeModel = srcNodeModel;
    this->dstNodeModel = dstNodeModel;
    setSrcPosition(srcNodeModel->getPosition());
    setDstPosition(dstNodeModel->getPosition());
    setSelected(linkModel->getIsSelected());
    QObject::connect(srcNodeModel, &NodeModel::positionChanged, this, &LinkView::setSrcPosition);
    QObject::connect(dstNodeModel, &NodeModel::positionChanged, this, &LinkView::setDstPosition);
    QObject::connect(linkModel, &LinkModel::destroyed, this, &LinkView::deleteFromScene);
    QObject::connect(this, &LinkView::selectionChanged, linkModel, &LinkModel::setSelected);
}

void LinkView::setSrcPosition(const QPointF &position)
{
    QLineF line = this->line();
    line.setP1(position);
    setLine(line);
}

void LinkView::setDstPosition(const QPointF &position)
{
    QLineF line = this->line();
    line.setP2(position);
    setLine(line);
}

void LinkView::deleteFromScene(QObject *object)
{
    Q_UNUSED(object);
    scene()->removeItem(this);
    delete this;
}

QVariant LinkView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedHasChanged) {
        emit selectionChanged(value.toBool());
    }
    return QGraphicsItem::itemChange(change, value);
}
