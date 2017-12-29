#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <iostream>
#include <QTimer>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QGraphicsScene *scene);

signals:
    void distanceCalcActivated(QPoint);
    void mousePressed(QPoint);
    void mouseMoved(QPoint);
    
public slots:
    void mousePressed1S();
    
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    
    QTimer timer_mouse;
    QPoint mouse_press_pos;
    

};

#endif // MYGRAPHICSVIEW_H
