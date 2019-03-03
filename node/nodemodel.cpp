#include "node/nodemodel.h"
#include <QSet>
#include <QDebug>

QSet<int> NodeModel::usedNodeIDs = QSet<int>({0});

NodeModel::NodeModel(QObject *parent) : QObject(parent)
{
    ID = -1;
}

NodeModel::~NodeModel()
{
    usedNodeIDs.remove(ID);
}

QPointF NodeModel::getPosition()
{
    return this->position;
}

void NodeModel::setPosition(const QPointF &position)
{
    this->position = position;
    emit positionChanged(position);
}

bool NodeModel::getIsSelected()
{
    return isSelected;
}

void NodeModel::setSelected(bool isSelected)
{
    this->isSelected = isSelected;
}

QString NodeModel::getText()
{
    return text;
}

int NodeModel::genNewID()
{
    foreach (int usedID, usedNodeIDs) {
        if(!usedNodeIDs.contains(usedID + 1)) {
            return usedID + 1;
        }
    }
    assert(false);
    return -1;
}

int NodeModel::getID()
{
    return ID;
}

void NodeModel::setID(int ID)
{
    usedNodeIDs.remove(this->ID);
    assert(!usedNodeIDs.contains(ID));
    usedNodeIDs.insert(ID);
    this->ID = ID;

}

void NodeModel::setText(QString text)
{
    this->text = text;
    emit textChanged(text);
}
