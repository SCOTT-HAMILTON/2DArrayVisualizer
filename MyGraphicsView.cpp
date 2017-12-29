#include "MyGraphicsView.h"

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene) : 
    QGraphicsView(scene)
{
    setMouseTracking(true);
    timer_mouse.setSingleShot(true);
    
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    
    QObject::connect(&timer_mouse, SIGNAL(timeout()), this, SLOT(mousePressed1S()));
}
void MyGraphicsView::mousePressed1S(){
    std::cout << "mouse pressed for 1 second !!" << std::endl;
    emit distanceCalcActivated(mouse_press_pos);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event){
    timer_mouse.start(1000);
    mouse_press_pos = event->pos();
    emit mousePressed(event->pos());
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    timer_mouse.stop();
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    emit mouseMoved(event->pos());
}
