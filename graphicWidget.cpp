
#include "graphicWidget.h"
#include "node.h"

#include <QKeyEvent>
#include <vector>
//#include <random>

#include "hashLine.h"
#include "helpers.h"

#include <QPushButton>



GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(30, 30, 900, 600);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(400, 400);
    setWindowTitle(tr("Hash Lines Demo"));

    m_numNodes = 200;
    for( int i = 0; i < m_numNodes; i++ )
    {
        Node *node = new Node( this );
        scene->addItem( node );
        node->setPos( rand() % 700 + 50, rand() %550 + 50);

        m_nodes.push_back( node );
    }

    m_start = QPoint(10, 400);
    m_end = QPoint(800, 400);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::drawForeground( QPainter * painter, const QRectF & rect)
{
    QPoint points[2] = {
        QPoint(10, 400),
        QPoint(800, 400)
    };

    points[0] = m_start;
    points[1] = m_end;

    painter->drawPolyline(points, 2);
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

std::vector< Node* >& GraphWidget::getNodes()
{
    return m_nodes;
}

void GraphWidget::hashLine()
{
    std::vector< QPoint > points(  m_nodes.size() );
    for( int n = 0, num = m_nodes.size(); n < num; ++n ){
        points[ n ] =  QPoint( m_nodes[ n ]->pos().x(), m_nodes[ n ]->pos().y());
    }

    timeval timer;
    startHashTimer( timer );
    Line myLine = find_line_with_most_points(  points );
    std::cout<<" hashing "<< m_numNodes*(m_numNodes -1 )<<" lines takes "<<stopHashTimer(timer )<<" seconds "<<std::endl;
    m_start.setX( 50 ); m_start.setY( myLine.y( 50 ) );
    m_end.setX( 600 );  m_end.setY( myLine.y( 600 ) );
}
