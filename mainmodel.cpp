#include "mainmodel.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>

MainModel::MainModel(QObject *parent) : QObject(parent)
{
    Q_UNUSED(parent);
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MindCloud.db");
    if (!database.open()) {
        qDebug() << database.lastError().text();
    }
}

void MainModel::changeSelectedNode(bool isSelected, NodeModel *nodeModel)
{
    if(isSelected) {
        selectedNodes.push_back(nodeModel);
        emit nodeSelectedWithText(nodeModel->getText());
    }
    else {
        selectedNodes.removeOne(nodeModel);
        emit nodeSelectedWithText(selectedNodes.size() ? selectedNodes.last()->getText() : "");
    }
}

void MainModel::changeSelectedNodeText(const QString &text)
{
    if(selectedNodes.size()) {
        selectedNodes.last()->setText(text);
    }
}

void MainModel::createNode(const QPointF &position, const QString &text, int ID, bool isSelected)
{
    NodeModel *nodeModel = new NodeModel;
    nodeModel->setID(ID);
    nodeModel->setText(text);
    nodeModel->setPosition(position);
    nodeModel->setSelected(isSelected);
    nodes.insert(nodeModel);
    emit nodeCreated(nodeModel);
    changeSelectedNode(isSelected, nodeModel);
}

void MainModel::createLink(NodeModel *srcNodeModel, NodeModel *dstNodeModel, bool isSelected)
{
    LinkModel *linkModel = new LinkModel;
    linkModel->setSelected(isSelected);
    linkModel->setSrcID(srcNodeModel->getID());
    linkModel->setDstID(dstNodeModel->getID());
    links.insert(linkModel);
    emit linkCreated(linkModel, srcNodeModel, dstNodeModel);
}

NodeModel *MainModel::getNodeWithID(int ID)
{
    foreach (NodeModel *node, nodes) {
        if(node->getID() == ID) {
            return node;
        }
    }
    return nullptr;
}

void MainModel::linkSelectedNodes()
{
    for (int index1 = 0; index1 < selectedNodes.size(); ++index1) {
        for (int index2 = index1 + 1; index2 < selectedNodes.size(); ++index2) {
            createLink(selectedNodes[index1], selectedNodes[index2]);
        }
    }
}

void MainModel::deleteSelectedLinks()
{
    QList<LinkModel*> linksList = links.toList();
    foreach (LinkModel * link, linksList) {
        if(link->getIsSelected()){
            links.remove(link);
            delete link;
        }
    }
}

void MainModel::deleteSelectedNodes()
{
    QList<NodeModel*> nodesList = nodes.toList();
    foreach (NodeModel * node, nodesList) {
        if(node->getIsSelected()){
            changeSelectedNode(false, node);
            int nodeID = node->getID();
            nodes.remove(node);
            delete node;
            QList<LinkModel*> linksList = links.toList();
            foreach (LinkModel * link, linksList) {
                if(link != nullptr && (link->getSrcID() == nodeID || link->getDstID() == nodeID)){
                    links.remove(link);
                    delete link;
                }
            }
        }
    }
}

void MainModel::clearAll()
{
    foreach (LinkModel * link, links) {
        delete link;
    }
    foreach (NodeModel * node, nodes) {
        delete node;
    }
    nodes.clear();
    links.clear();
}

void MainModel::saveData()
{
    QSqlTableModel nodesTableModel;
    nodesTableModel.setTable(enumName(tNodes));
    nodesTableModel.select();
    int nodesRowCount = nodesTableModel.rowCount();
    //???: not work model.removeRows(0, rowCount);
    for (int row = 0; row < nodesRowCount; ++row) {
        nodesTableModel.removeRow(row);
    }
    nodesTableModel.submitAll();
    QSqlTableModel linksTableModel;
    linksTableModel.setTable(enumName(tLinks));
    linksTableModel.select();
    int linksRowCount = linksTableModel.rowCount();
    for (int row = 0; row < linksRowCount; ++row) {
        linksTableModel.removeRow(row);
    }
    linksTableModel.submitAll();

    foreach (NodeModel *nodeModel, nodes) {
        QSqlRecord sqlRecord = nodesTableModel.record();
        sqlRecord.setValue(enumName(NodeID), nodeModel->getID());
        sqlRecord.setValue(enumName(Text), nodeModel->getText());
        sqlRecord.setValue(enumName(PositionX), nodeModel->getPosition().x());
        sqlRecord.setValue(enumName(PositionY), nodeModel->getPosition().y());
        sqlRecord.setValue(enumName(IsSelected), nodeModel->getIsSelected());
        nodesTableModel.insertRecord(0, sqlRecord);
    }    
    nodesTableModel.submitAll();
    foreach (LinkModel *linkModel, links) {
        QSqlRecord sqlRecord = linksTableModel.record();
        sqlRecord.setValue(enumName(SrcNodeID), linkModel->getSrcID());
        sqlRecord.setValue(enumName(DstNodeID), linkModel->getDstID());
        sqlRecord.setValue(enumName(IsSelected), linkModel->getIsSelected());
        linksTableModel.insertRecord(0, sqlRecord);
    }
    linksTableModel.submitAll();
}

void MainModel::loadData()
{
    clearAll();
    QSqlTableModel nodesTableModel;
    nodesTableModel.setTable(enumName(tNodes));
    nodesTableModel.select();
    for (int index = 0; index < nodesTableModel.rowCount(); ++index) {
        QSqlRecord sqlRecord = nodesTableModel.record(index);
        int ID = sqlRecord.value(enumName(NodeID)).toInt();
        QString text = sqlRecord.value(enumName(TEXT)).toString();
        double positionX = sqlRecord.value(enumName(PositionX)).toDouble();
        double positionY = sqlRecord.value(enumName(PositionY)).toDouble();
        bool isSelected = sqlRecord.value(enumName(IsSelected)).toBool();
        createNode(QPointF(positionX, positionY), text, ID, isSelected);
    }
    QSqlTableModel linksTableModel;
    linksTableModel.setTable(enumName(tLinks));
    linksTableModel.select();
    for (int index = 0; index < linksTableModel.rowCount(); ++index) {
        QSqlRecord sqlRecord = linksTableModel.record(index);
        int srcID = sqlRecord.value(enumName(SrcNodeID)).toInt();
        int dstID = sqlRecord.value(enumName(DstNodeID)).toInt();
        bool isSelected = sqlRecord.value(enumName(IsSelected)).toBool();
        createLink(getNodeWithID(srcID), getNodeWithID(dstID), isSelected);
    }
}

