#include "node/nodeview.h"
#include <QGraphicsScene>
#include <QDebug>

double NodeView::radius = 15;

NodeView::NodeView() : QGraphicsEllipseItem(0, 0, 2*radius, 2*radius)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsScenePositionChanges);
    setBrush(QBrush(Qt::yellow));
    setAcceptHoverEvents(true);
    label = new QGraphicsSimpleTextItem(this);
    label->setPos(QPointF(radius, radius/2));
}

void NodeView::setModel(NodeModel *nodeModel)
{
    this->nodeModel = nodeModel;
    setPos(QPointF(nodeModel->getPosition().x() - radius, nodeModel->getPosition().y() - radius));
    setSelected(nodeModel->getIsSelected());
    changeText(nodeModel->getText());
    QObject::connect(nodeModel, &NodeModel::textChanged, this, &NodeView::changeText);
    QObject::connect(nodeModel, &NodeModel::destroyed, this, &NodeView::deleteFromScene);
    QObject::connect(this, &NodeView::selectionChanged, nodeModel, &NodeModel::setSelected);
    QObject::connect(this, &NodeView::positionChanged, nodeModel, &NodeModel::setPosition);
}

void NodeView::changeText(const QString &text)
{
    label->setText(text.size() ? text.left(1) : "?");
    setToolTip(text);
}

void NodeView::deleteFromScene(QObject *object)
{
    Q_UNUSED(object);
    scene()->removeItem(this);
    delete this;
}

QVariant NodeView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedHasChanged) {
        emit selectionChanged(value.toBool(), nodeModel);
    } else if(change == QGraphicsItem::ItemPositionChange) {
        emit positionChanged(QPointF(value.toPointF().x() + radius, value.toPointF().y() + radius));
    }
    return QGraphicsItem::itemChange(change, value);
}
