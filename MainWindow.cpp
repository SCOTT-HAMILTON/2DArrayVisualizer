#include "MainWindow.h"
#include <string>
#include <QFont>
#include <QtMath>

MainWindow::MainWindow(int nb_case_w, int nb_case_h, int w_spacing, int h_spacing, int visible_w_spacing, int visible_h_spacing, QWidget *parent)
    : QWidget(parent)
{
    distanceCalcActivate = false;
    
    width_spacing = w_spacing;
    height_spacing = h_spacing;
    this->width = ((nb_case_w+2)*width_spacing);
    this->height = ((nb_case_h+2)*height_spacing);
    nb_case_width = nb_case_w;
    nb_case_height = nb_case_h;
    visible_height_spacing = visible_h_spacing;
    visible_width_spacing = visible_w_spacing;
    
    dialogCase = new DialogCaseChanging(nb_case_w, nb_case_h, width_spacing, height_spacing, visible_width_spacing, visible_height_spacing, this);
            
    mainLay = new QVBoxLayout;
    
    bar = new QMenuBar;
    menuParam = new QMenu("&Paramètre");
    actCase = new QAction("&Cases", this);
    menuParam->addAction(actCase);
    
    menuDistCalc = new QMenu("Calcul de &distances");
    actDistCalcRealSpacing = new QAction("&Utiliser les réelles distances", this);
    actDistCalcRealSpacing->setCheckable(true);
    actDistCalcRealSpacing->setChecked(false);
    
    actDistCalcVisibleSpacing = new QAction("&Utiliser les distances visibles", this);
    actDistCalcVisibleSpacing->setCheckable(true);
    actDistCalcVisibleSpacing->setChecked(true);
    
    dist_type = VisibleDist;
    
    menuDistCalc->addAction(actDistCalcRealSpacing);
    menuDistCalc->addAction(actDistCalcVisibleSpacing);
    
    
    menuParam->addMenu(menuDistCalc);
    
    bar->addMenu(menuParam);
    mainLay->addWidget(bar);
    
    QFont font_textpos;
    font_textpos.setPixelSize(8);
    font_textpos.setBold(true);
    text_pos = new QGraphicsSimpleTextItem(", ");
    text_pos->setFont(font_textpos);
    text_pos->setVisible(false);
    
    point1_dist = new QGraphicsEllipseItem(0, 0, 5, 5);
    point1_dist->setBrush(QBrush(QColor(255, 246, 0)));
    point1_dist->setVisible(false);
    
    point2_dist = new QGraphicsEllipseItem(0, 0, 5, 5);
    point2_dist->setBrush(QBrush(QColor(255, 246, 0)));
    point2_dist->setVisible(false);
    
    dist_text = new QGraphicsSimpleTextItem;
    dist_text->setVisible(false);
    
    lines_previsdist.emplace_back(std::move(new QGraphicsLineItem));
    lines_previsdist.emplace_back(std::move(new QGraphicsLineItem));
        
    scene = new QGraphicsScene(0, 0, this->width, this->height, this);
    
    view = new MyGraphicsView(scene);   
    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setMinimumSize(width+2, height+2);
    view->setMaximumSize(width+2, height+2); 
    
    setFixedSize(this->width+25, this->height+50);
        
    mainLay->addWidget(view, Qt::AlignRight|Qt::AlignBottom);
    
    marge_x = 50;
    marge_y = 50;
    std::cout << "oui" << std::endl;
    
    for (int i = 0; i < nb_case_h; i++){
        lines_text.emplace_back(std::move(new QGraphicsSimpleTextItem(QString::fromStdString(std::string(std::to_string( (i*height_spacing)*visible_h_spacing/height_spacing ))))));
        lines_text[lines_text.size()-1]->setX(marge_x-40);
        lines_text[lines_text.size()-1]->setY(i*height_spacing+marge_y+12);
        scene->addItem(lines_text[lines_text.size()-1]);
        for (int j = 0; j < nb_case_w; j++){
            if(i == 0){
                columns_text.emplace_back(std::move(new QGraphicsSimpleTextItem(QString::fromStdString(std::string(std::to_string( (j*width_spacing)*visible_w_spacing/width_spacing ))))));
                columns_text[columns_text.size()-1]->setX(j*width_spacing+marge_x+5);
                columns_text[columns_text.size()-1]->setY(marge_y-35);
                scene->addItem(columns_text[columns_text.size()-1]);
            }
            
            int x = j*width_spacing+marge_x;
            int y = i*height_spacing+marge_y;
            std::cout << "x, y : " << x << ", " << y << std::endl;
            cases.emplace_back( std::move( new QGraphicsRectItem(x-2, y-2, width_spacing, height_spacing) ) );
            scene->addItem(cases[cases.size()-1]);
        }
    }
    
    scene->addItem(text_pos);
    scene->addItem(point1_dist);
    scene->addItem(point2_dist);
    scene->addItem(lines_previsdist[0]);
    scene->addItem(lines_previsdist[1]);
    scene->addItem(dist_text);
    
    setLayout(mainLay);
    
    QObject::connect(view, SIGNAL(mouseMoved(QPoint)), this, SLOT(mouseViewMoved(QPoint)));
    QObject::connect(view, SIGNAL(distanceCalcActivated(QPoint)), this, SLOT(activateDistanceCalc(QPoint)));
    QObject::connect(view, SIGNAL(mousePressed(QPoint)), this, SLOT(mouseViewPressed(QPoint)));
    
    QObject::connect(actCase, SIGNAL(triggered(bool)), this, SLOT(displayCaseDialog()));
    QObject::connect(actDistCalcVisibleSpacing, SIGNAL(triggered(bool)), this, SLOT(setDistCalcVisible()));
    QObject::connect(actDistCalcRealSpacing, SIGNAL(triggered(bool)), this, SLOT(setDistCalcReal()));
    
    
    QObject::connect(dialogCase, SIGNAL(submitPressed(int, int, int, int, int, int)), this, SLOT(changeCase(int, int, int, int, int, int)));
    
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::mouseViewMoved(QPoint pos){
    int x = pos.x();
    int y = pos.y();
    mouse_pos = pos;
    std::cout << "pos : " << x << ", " << y << std::endl;
    if (x>marge_x && x < (width_spacing*nb_case_width)+marge_x && y > marge_y && y < (height_spacing*nb_case_height)+marge_y){
        int pos_text_x;
        int pos_text_y;
        pos_text_x = x-((x-marge_x)%width_spacing)+5;
        pos_text_y = y-((y-marge_y)%height_spacing)+(height_spacing/2)-5;
        int pos_x = ((x-((x-marge_x)%width_spacing))-marge_x)*visible_width_spacing/width_spacing;
        int pos_y = ((y-((y-marge_y)%height_spacing))-marge_y)*visible_height_spacing/height_spacing;
        text_pos->setText(QString::fromStdString( std::string(std::to_string(pos_x)+", "+std::to_string(pos_y)) ));
        text_pos->setX(pos_text_x);
        text_pos->setY(pos_text_y);        
        text_pos->setVisible(true);
        if (distanceCalcActivate){
            int y_line1 = y-((y-marge_y)%height_spacing)+(height_spacing/2)-2;
            int x_line2 = x-((x-marge_x)%width_spacing)+(width_spacing/2);
            lines_previsdist[0]->setLine(lines_previsdist[0]->line().p1().x(), lines_previsdist[0]->line().p1().y(), lines_previsdist[0]->line().p1().x(), y_line1);
            lines_previsdist[1]->setLine(lines_previsdist[0]->line().p2().x(), lines_previsdist[0]->line().p2().y(), x_line2, y_line1);            
        }
    }else{
        text_pos->setVisible(false);
    }
}

void MainWindow::activateDistanceCalc(QPoint pos){
    int x = pos.x();
    int y = pos.y();
    int pos_x = x-((x-marge_x)%width_spacing)+(width_spacing/2)-4;
    int pos_y = y-((y-marge_y)%height_spacing)+(height_spacing/2)-5;
    point2_dist->setVisible(false);
    dist_text->setVisible(false);
    
    distanceCalcActivate = true;
    text_pos->setVisible(false);
    point1_dist->setX(pos_x);
    point1_dist->setY(pos_y);
    point1_dist->setVisible(true);
    
    lines_previsdist[0]->setLine(pos_x+2, pos_y+2, pos_x+2, pos_y+2);
    lines_previsdist[1]->setLine(pos_x+2, pos_y+2, pos_x+2, pos_y+2);    
    lines_previsdist[0]->setVisible(true);
    lines_previsdist[1]->setVisible(true);
    
}

void MainWindow::mouseViewPressed(QPoint pos){
    if (distanceCalcActivate){
        int x = pos.x();
        int y = pos.y();
        mouse_pos = pos;
        if (x>marge_x && x < (width_spacing*nb_case_width)+marge_x && y > marge_y && y < (height_spacing*nb_case_height)+marge_y){
            int pos_x = x-((x-marge_x)%width_spacing)+(width_spacing/2)-4;
            int pos_y = y-((y-marge_y)%height_spacing)+(height_spacing/2)-5;          
            distanceCalcActivate = false;
            point2_dist->setX(pos_x);
            point2_dist->setY(pos_y);
            point2_dist->setVisible(true);
            
            QPoint tmp_pos;
            tmp_pos = QPoint(lines_previsdist[1]->line().p1().x(), lines_previsdist[1]->line().p1().y());
            tmp_pos.setX(tmp_pos.x()-(int)point1_dist->pos().x()+10);
            tmp_pos.setY(tmp_pos.y()-(int)point1_dist->pos().y());            
            tmp_pos/=2;
            dist_text->setPos(point1_dist->pos()+tmp_pos);
            
            
            int dist_x, dist_y;
            if (dist_type == RealDist){
                std::cout << "real dist !! " << std::endl;
                int tmp_1 = lines_previsdist[1]->line().p1().x();
                tmp_1 = tmp_1-((tmp_1-marge_x)%width_spacing);
                int tmp_2 = lines_previsdist[1]->line().p2().x();
                tmp_2 = tmp_2-((tmp_2-marge_x)%width_spacing);
                dist_x = qAbs(tmp_2-tmp_1);
                
                tmp_1 = lines_previsdist[0]->line().p1().y();
                tmp_1 = tmp_1-((tmp_1-marge_y)%height_spacing);
                
                tmp_2 = lines_previsdist[0]->line().p2().y();
                tmp_2 = tmp_2-((tmp_2-marge_y)%height_spacing);
                dist_y = qAbs(tmp_2-tmp_1);        
            }else{
                std::cout << "visible dist !! " << std::endl;                
                int tmp_1 = lines_previsdist[1]->line().p1().x();
                tmp_1 = (tmp_1-((tmp_1-marge_x)%width_spacing))*visible_width_spacing/width_spacing;
                int tmp_2 = lines_previsdist[1]->line().p2().x();
                tmp_2 = (tmp_2-((tmp_2-marge_x)%width_spacing))*visible_width_spacing/width_spacing;
                dist_x = qAbs(tmp_2-tmp_1);
                
                tmp_1 = lines_previsdist[0]->line().p1().y();
                tmp_1 = (tmp_1-((tmp_1-marge_y)%height_spacing))*visible_height_spacing/height_spacing;
                
                tmp_2 = lines_previsdist[0]->line().p2().y();
                tmp_2 = (tmp_2-((tmp_2-marge_y)%height_spacing))*visible_height_spacing/height_spacing;
                dist_y = qAbs(tmp_2-tmp_1);  
            }
            dist_text->setText(QString::fromStdString(std::string(std::to_string(dist_x)+" , "+std::to_string(dist_y))));
            
            dist_text->setVisible(true);
            
        }
    }
}

void MainWindow::displayCaseDialog(){
    dialogCase->show();
}

float MainWindow::distance(const QPoint &p1, const QPoint &p2){
    float a = p2.x()-p1.x();
    float b = p2.y()-p1.y();
    return qSqrt( (a*a)+(b*b) );
}

void MainWindow::changeCase(int nb_case_w, int nb_case_h, int real_spacing_w, int real_spacing_h, int visible_spacing_w, int visible_spacing_h){
    nb_case_width = nb_case_w;
    nb_case_height = nb_case_h;
    width_spacing = real_spacing_w;
    height_spacing = real_spacing_h;
    visible_width_spacing = visible_spacing_w;
    visible_height_spacing = visible_spacing_h;
    for (int i = 0; i < cases.size(); i++){
        scene->removeItem(cases[i]);
    }
    for (int i = 0; i < lines_text.size(); i++){
        scene->removeItem(lines_text[i]);
    }
    for (int i = 0; i < columns_text.size(); i++){
        scene->removeItem(columns_text[i]);
    }
    
    columns_text.clear();
    lines_text.clear();
    
    width = ((nb_case_w+2)*width_spacing);
    height = ((nb_case_h+2)*height_spacing);
    
    view->setMinimumSize(width+2, height+2);
    view->setMaximumSize(width+2, height+2); 
    
    view->setSceneRect(0, 0, width, height);  
    setFixedSize(width+25, height+50);
    
    
    cases.clear();
    for (int i = 0; i < nb_case_h; i++){
        lines_text.emplace_back(std::move(new QGraphicsSimpleTextItem(QString::fromStdString(std::string(std::to_string(i*height_spacing*visible_height_spacing/height_spacing))))));
        lines_text[lines_text.size()-1]->setX(marge_x-40);
        lines_text[lines_text.size()-1]->setY(i*height_spacing+marge_y+12);
        scene->addItem(lines_text[lines_text.size()-1]);
        for (int j = 0; j < nb_case_w; j++){
            if(i == 0){
                columns_text.emplace_back(std::move(new QGraphicsSimpleTextItem(QString::fromStdString(std::string(std::to_string(j*width_spacing*visible_width_spacing/width_spacing))))));
                columns_text[columns_text.size()-1]->setX(j*width_spacing+marge_x+5);
                columns_text[columns_text.size()-1]->setY(marge_y-35);
                scene->addItem(columns_text[columns_text.size()-1]);
            }
            
            int x = j*width_spacing+marge_x;
            int y = i*height_spacing+marge_y;
            std::cout << "x, y : " << x << ", " << y << std::endl;
            cases.emplace_back( std::move( new QGraphicsRectItem(x-2, y-2, width_spacing, height_spacing) ) );
            scene->addItem(cases[cases.size()-1]);
        }
    }
    std::cout << "finish!!" << std::endl;
}

void MainWindow::setDistCalcVisible(){
    actDistCalcRealSpacing->setChecked(false);
    actDistCalcVisibleSpacing->setChecked(true);
    dist_type = VisibleDist;        
}
void MainWindow::setDistCalcReal(){
    actDistCalcRealSpacing->setChecked(true);
    actDistCalcVisibleSpacing->setChecked(false);
    dist_type = RealDist;    
}

