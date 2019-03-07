#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QPoint>
#include <QSet>
#include <QList>
#include "node/nodemodel.h"
#include "link/linkmodel.h"
#define enumName(v) QString(#v)

class MainModel : public QObject
{
    Q_OBJECT
public:
    explicit MainModel(QObject *parent = nullptr);
signals:
    void nodeCreated(NodeModel *nodeModel);
    void linkCreated(LinkModel *linkModel, NodeModel *srcNodeModel, NodeModel *dstNodeModel);
    void nodeSelectedWithText(const QString &text);
public slots:
    void changeSelectedNode(bool isSelected, NodeModel *nodeModel = nullptr);
    void changeSelectedNodeText(const QString &text);
    void createNode(const QPointF &position, const QString &text = "?", int ID = NodeModel::genNewID(), bool isSelected = true);
    void linkSelectedNodes();
    void deleteSelectedNodes();
    void deleteSelectedLinks();
    void saveData();
    void loadData();
private:
    QSet<NodeModel*> nodes;
    QSet<LinkModel*> links;
    QList<NodeModel*> selectedNodes;
    void createLink(NodeModel *srcNodeModel, NodeModel *dstNodeModel, bool isSelected = false);
    NodeModel *getNodeWithID(int ID);
    void clearAll();
    enum DataBaseTables {tNodes, tLinks};
    enum DataBaseFields {NodeID, Text, PositionX, PositionY, IsSelected, LinkID, SrcNodeID, DstNodeID};
};

#endif // MAINMODEL_H
