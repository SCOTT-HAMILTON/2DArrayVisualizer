#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QGraphicsLineItem>
#include <vector>
#include <QGraphicsSimpleTextItem>
#include <iostream>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QMenuBar>
#include <QMenu>
#include <QGraphicsRectItem>

#include "DialogCaseChanging.h"
#include "MyGraphicsView.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(int nb_case_w, int nb_case_h, int w_spacing = 40, int h_spacing = 40, int visible_w_spacing = 1, int visible_h_spacing = 1, QWidget *parent = 0);
    ~MainWindow();
    static float distance(const QPoint &p1, const QPoint &p2);
    
public slots:
    void mouseViewMoved(QPoint);
    void mouseViewPressed(QPoint);
    void activateDistanceCalc(QPoint);
    void displayCaseDialog();
    void changeCase(int, int, int, int, int, int);
    
private:
    int width;
    int height;
    int width_spacing;
    int height_spacing;
    int visible_width_spacing;
    int visible_height_spacing;
    int nb_case_width;
    int nb_case_height;
    QVBoxLayout *mainLay;
    QGraphicsScene *scene;
    MyGraphicsView *view;
    std::vector<QGraphicsSimpleTextItem*> lines_text;
    std::vector<QGraphicsSimpleTextItem*> columns_text;
    std::vector<QGraphicsRectItem*> cases;
    QGraphicsSimpleTextItem *text_pos;
    QGraphicsEllipseItem *point1_dist;
    QGraphicsEllipseItem *point2_dist;    
    QGraphicsLineItem *line_previsdist;
    QGraphicsSimpleTextItem *dist_text;
    QMenuBar *bar;
    
    DialogCaseChanging *dialogCase;
    
    int spacing_textw;
    int spacing_texth;
    int start_w;
    int start_h;
    int marge_x;
    int marge_y;
    
    QPoint mouse_pos;
    
    bool distanceCalcActivate;
};

#endif // MAINWINDOW_H
