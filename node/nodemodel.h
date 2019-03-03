#ifndef NODEMODEL_H
#define NODEMODEL_H

#include <QObject>
#include <QPoint>

class NodeModel : public QObject
{
    Q_OBJECT
public:
    explicit NodeModel(QObject *parent = nullptr);
    ~NodeModel();
    int getID();
    void setID(int ID);
    QPointF getPosition();
    bool getIsSelected();
    QString getText();
    static int genNewID();
signals:
    void textChanged(const QString &text);
    void positionChanged(const QPointF &position);
public slots:
    void setPosition(const QPointF &position);
    void setSelected(bool isSelected);
    void setText(QString text);
private:
    int ID;
    QPointF position;
    bool isSelected;
    QString text;
    static QSet<int> usedNodeIDs;

};

#endif // NODEMODEL_H
