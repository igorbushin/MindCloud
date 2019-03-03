#ifndef LINKLINKMODEL_H
#define LINKLINKMODEL_H

#include <QObject>

class LinkModel : public QObject
{
    Q_OBJECT
public:
    explicit LinkModel(QObject *parent = nullptr);    
    bool getIsSelected();
    void setDstID(int ID);
    void setSrcID(int ID);
    int getDstID();
    int getSrcID();
signals:

public slots:
    void setSelected(bool isSelected);
private:
    bool isSelected;
    int dstID;
    int srcID;
};

#endif // LINKLINKMODEL_H
