#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>

class GraphWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void handleButton();

private:
    QPushButton *m_button;
    GraphWidget *m_widget;
};

#endif // MAINWINDOW_H
