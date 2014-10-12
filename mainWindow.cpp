#include "mainWindow.h"
#include "graphicWidget.h"
#include "node.h"

#include <QGridLayout>
#include <QHBoxLayout>

#include <iostream>
#include <vector>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the button, make "this" the parent
    m_button = new QPushButton("Hash!" );
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(0, 0),
                                 QSize(100, 100)));

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));

    m_widget = new GraphWidget;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget( m_button );
    layout->addWidget( m_widget );

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
}

void MainWindow::handleButton()
{
    std::vector<Node*> nodes = m_widget->getNodes();

    double ratio = ( (double) rand() / (RAND_MAX)) ;

    for( int n = 0; n < nodes.size();  ++n )
    {
        Node* node = nodes[ n ];

        if( n < 10 ){
            int x = 30 * ( n + 1 );
            node->setPos( x, 600 - int( ratio* double( x ) ) );
        }
        else
        {
            node->setPos( rand() % 850 + 50, rand() %550 + 50);
        }
    }


    m_widget->hashLine();
}
