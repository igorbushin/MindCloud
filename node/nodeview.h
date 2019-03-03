#ifndef NODEODEVIEW_H
#define NODEODEVIEW_H

#include "node/nodemodel.h"
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>

class NodeView : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    NodeView();
    void setModel(NodeModel *nodeModel);
signals:
    void selectionChanged(bool isSelected, NodeModel *nodeModel = nullptr);
    void positionChanged(const QPointF &position);
public slots:
    void deleteFromScene(QObject *object);
    void changeText(const QString &text);
private:
    static double radius;
    NodeModel *nodeModel;
    QGraphicsSimpleTextItem *label;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif // NODEODEVIEW_H
