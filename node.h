#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class GraphWidget;

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF newPos;
    GraphWidget *graph;

};



#endif // NODE_H
