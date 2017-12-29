#ifndef DIALOGCASECHANGING_H
#define DIALOGCASECHANGING_H



#include <iostream>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QGroupBox>

class DialogCaseChanging : public QDialog
{
    Q_OBJECT
    
public:
    DialogCaseChanging(int nb_case_w, int nb_case_h, int real_spacing_w, int real_spacing_h, int visible_spacing_w, int visible_spacing_h, QWidget *parent = Q_NULLPTR);
    
signals:
    void submitPressed(int, int, int, int, int, int);
    
public slots:
    void sendSubmitPressed();

private:
    int nb_case_width;
    int nb_case_height;
    int real_spacing_width;
    int real_spacing_height;
    int visible_spacing_width;
    int visible_spacing_height;
    QVBoxLayout *mainLay;
    
    QGroupBox *box_nb_cases;
    QVBoxLayout *lay_nb_cases;    
    QFormLayout *lay_nb_case_w;
    QFormLayout *lay_nb_case_h;
    QSpinBox *spinNbCaseW;
    QSpinBox *spinNbCaseH;
    
    QGroupBox *box_spacing_real;
    QVBoxLayout *lay_spacing_real;    
    QFormLayout *lay_spacing_real_w;
    QFormLayout *lay_spacing_real_h;
    QSpinBox *spinSpacingRealW;
    QSpinBox *spinSpacingRealH;
    
    QGroupBox *box_spacing_displayed;
    QVBoxLayout *lay_spacing_displayed;
    QFormLayout *lay_spacing_displayed_w;
    QFormLayout *lay_spacing_displayed_h;
    QSpinBox *spinSpacingDisplayedW;
    QSpinBox *spinSpacingDisplayedH;
    
    
    QPushButton *submitButton;
};

#endif // DIALOGCASECHANGING_H
