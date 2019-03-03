#include "link\linkmodel.h"

LinkModel::LinkModel(QObject *parent) : QObject(parent)
{

}

bool LinkModel::getIsSelected()
{
    return isSelected;
}

int LinkModel::getSrcID()
{
    return srcID;
}

int LinkModel::getDstID()
{
    return dstID;
}

void LinkModel::setSrcID(int ID)
{
    this->srcID = ID;
}

void LinkModel::setDstID(int ID)
{
    this->dstID = ID;
}

void LinkModel::setSelected(bool isSelected)
{
    this->isSelected = isSelected;
}
