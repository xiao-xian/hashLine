#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#endif // GRAPHICWIDGET_H

#include <vector>
#include <QGraphicsView>
class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

public slots:
    void zoomIn();
    void zoomOut();

    std::vector< Node* >& getNodes();

    void hashLine();



protected:
    void keyPressEvent(QKeyEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void scaleView(qreal scaleFactor);
    void drawForeground( QPainter * painter, const QRectF & rect);

private:

    std::vector<Node*> m_nodes;
    QPoint m_start, m_end;
    int m_numNodes;

};
