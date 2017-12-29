#include "DialogCaseChanging.h"

DialogCaseChanging::DialogCaseChanging(int nb_case_w, int nb_case_h, int real_spacing_w, int real_spacing_h, int visible_spacing_w, int visible_spacing_h, QWidget *parent) : 
    QDialog(parent)
{
    
    nb_case_height = nb_case_h;
    nb_case_width = nb_case_w;
    real_spacing_width = real_spacing_w;
    real_spacing_height = real_spacing_h;
    visible_spacing_width = visible_spacing_w;
    visible_spacing_height = visible_spacing_h;
    
    mainLay = new QVBoxLayout;
    
    /*nb cases box*/
    box_nb_cases = new QGroupBox("Nombres de cases : ");
    lay_nb_cases = new QVBoxLayout;
    
    lay_nb_case_h = new QFormLayout;
    lay_nb_case_w = new QFormLayout;
    
    spinNbCaseH = new QSpinBox;
    spinNbCaseH->setValue(nb_case_height);
    
    spinNbCaseW = new QSpinBox;
    spinNbCaseW->setValue(nb_case_width);
    
    lay_nb_case_w->addRow("Nombre de case en largeur : ", spinNbCaseW);
    lay_nb_case_h->addRow("Nombre de case en hauteur : ", spinNbCaseH);
    
    lay_nb_cases->addLayout(lay_nb_case_w);
    lay_nb_cases->addLayout(lay_nb_case_h);
    
    box_nb_cases->setLayout(lay_nb_cases);
    /*---------*/
    
    /*spacing real*/
    box_spacing_real = new QGroupBox("Pas réel : ");
    lay_spacing_real = new QVBoxLayout;
    
    lay_spacing_real_h = new QFormLayout;
    lay_spacing_real_w = new QFormLayout;
    
    spinSpacingRealH = new QSpinBox;
    spinSpacingRealH->setValue(real_spacing_h);
    
    spinSpacingRealW = new QSpinBox;
    spinSpacingRealW->setValue(real_spacing_w);
    
    lay_spacing_real_w->addRow("Pas réel en largeur : ", spinSpacingRealW);
    lay_spacing_real_h->addRow("Pas réel en hauteur : ", spinSpacingRealH);
    
    lay_spacing_real->addLayout(lay_spacing_real_w);
    lay_spacing_real->addLayout(lay_spacing_real_h);
    
    box_spacing_real->setLayout(lay_spacing_real);
    /*---------*/
    
    /*spacing displayed*/
    box_spacing_displayed = new QGroupBox("Pas visible : ");
    lay_spacing_displayed = new QVBoxLayout;
    
    lay_spacing_displayed_h = new QFormLayout;
    lay_spacing_displayed_w = new QFormLayout;
    
    spinSpacingDisplayedH = new QSpinBox;
    spinSpacingDisplayedH->setValue(visible_spacing_h);
    
    spinSpacingDisplayedW = new QSpinBox;
    spinSpacingDisplayedW->setValue(visible_spacing_w);
    
    lay_spacing_displayed_w->addRow("Pas visible en largeur : ", spinSpacingDisplayedW);
    lay_spacing_displayed_h->addRow("Pas visible en hauteur : ", spinSpacingDisplayedH);
    
    lay_spacing_displayed->addLayout(lay_spacing_displayed_w);
    lay_spacing_displayed->addLayout(lay_spacing_displayed_h);
    
    box_spacing_displayed->setLayout(lay_spacing_displayed);
    /*---------*/
    
    
    //submit button
    submitButton = new QPushButton("submit");
    
    mainLay->addWidget(box_nb_cases);
    mainLay->addWidget(box_spacing_real);
    mainLay->addWidget(box_spacing_displayed);
    mainLay->addWidget(submitButton);
    
    setLayout(mainLay);
    
    QObject::connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(sendSubmitPressed()));
}

void DialogCaseChanging::sendSubmitPressed(){
    emit submitPressed(spinNbCaseW->value(), spinNbCaseH->value(), spinSpacingRealW->value(), spinSpacingRealH->value(), spinSpacingDisplayedW->value(), spinSpacingDisplayedH->value());
}
