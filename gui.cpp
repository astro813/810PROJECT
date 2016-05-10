// Author:Jiyu Lei

#include "gui.h"
#include "ui_robotgui.h"
#include <QtWidgets>

RobotGui::RobotGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RobotGui)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(update()));                             //if timeout then run paintevent();
    timer->start(100);                                                                 //set time as 100ms

    setWindowTitle(tr("Robot Simulator (By Yingsheng Bao, Jun Chen, Jiyu Lei, Allison Dumandan)"));                                             //define the title of the window
    QSize mySize(myMap.getLength()+200,myMap.getWidth()+100);                      //define the size of the window
    this->resize(mySize);
    ui->pushButton->setGeometry(myMap.getLength()+15,430,100,20); //add new robot
    ui->pushButton_2->setGeometry(myMap.getLength()+15,300,100,20); //layout widgets //show status
    ui->label->setGeometry(20,myMap.getWidth()+15,90,20);
    ui->label1->setGeometry(20,myMap.getWidth()+35,90,20);
    ui->label2->setGeometry(20,myMap.getWidth()+55,90,20);
    ui->label3->setGeometry(20,myMap.getWidth()+75,90,20);
    ui->label4->setGeometry(200,myMap.getWidth()+15,90,20);
    ui->label5->setGeometry(200,myMap.getWidth()+35,90,20);
    ui->label6->setGeometry(200,myMap.getWidth()+55,110,20);
    ui->lineEdit->setGeometry(100,myMap.getWidth()+15,70,20);
    ui->lineEdit_1->setGeometry(100,myMap.getWidth()+35,70,20);
    ui->lineEdit_2->setGeometry(100,myMap.getWidth()+55,70,20);
    ui->lineEdit_3->setGeometry(100,myMap.getWidth()+75,70,20);
    ui->lineEdit_4->setGeometry(280,myMap.getWidth()+15,70,20);
    ui->lineEdit_5->setGeometry(280,myMap.getWidth()+35,70,20);
    ui->lineEdit_6->setGeometry(300,myMap.getWidth()+55,70,20);
    ui->label_2->setGeometry(myMap.getLength()+20,50,80,20);
    ui->lineEdit_7->setGeometry(myMap.getLength()+20,80,50,20);
    ui->label_3->setGeometry(myMap.getLength()+20,110,80,20);
    ui->label_4->setGeometry(myMap.getLength()+20,140,120,20);
    ui->label_5->setGeometry(myMap.getLength()+20,170,65,20);
    ui->label_6->setGeometry(myMap.getLength()+20,200,70,20);
    ui->label_7->setGeometry(myMap.getLength()+20,230,65,22);
    ui->label_8->setGeometry(myMap.getLength()+20,275,70,20);
}

RobotGui::~RobotGui()
{
    delete ui;
}

void RobotGui::paintEvent(QPaintEvent *e){                                               //painting;
    QPainter painter(this);
    QPainter painter2(this);
    painter.setRenderHint(QPainter::Antialiasing);                                       //make shape more smooth
    QColor robotC(0,0,255);
    QColor boundC(127,127,0);
    QColor AlertC(0,127,127);
    myMap.avoidCrash();                                                                  //load data to datalayer and check collision;
    myMap.clearData();                                                                 //clear datalayer;
    painter.setPen(boundC);
    painter.drawLine(0,0,myMap.getLength(),0);
    painter.drawLine(0,0,0,myMap.getWidth());
    painter.drawLine(myMap.getLength(),0,myMap.getLength(),myMap.getWidth());
    painter.drawLine(0,myMap.getWidth(),myMap.getLength(),myMap.getWidth());
    for(int i=0; i<robotList.size();i++){
        QPoint myCenter(robotList[i]->getX(),robotList[i]->getY());
        painter2.setPen(AlertC);
        painter2.save();
        painter2.drawEllipse(myCenter,robotList[i]->getAlert(),robotList[i]->getAlert());
        painter.setPen(Qt::NoPen);
        painter.setBrush(robotC);
        painter.save();
        painter.drawEllipse(myCenter,robotList[i]->getRadius(),robotList[i]->getRadius());
        robotList[i]->update();                                                               //robot move;
    }

}

void RobotGui::on_pushButton_clicked()                                                    //push button "New Robot" then add a new robot.
{
    bool c=1;
    QString Speed = ui->lineEdit_1->text();
    double speed=Speed.toDouble(&c);
    QString X = ui->lineEdit_2->text();
    double x = X.toDouble(&c);
    QString Y = ui->lineEdit_3->text();
    double y = Y.toDouble(&c);
    QString Theta = ui->lineEdit_4->text();
    double theta = Theta.toDouble(&c);
    QString Radius = ui->lineEdit_5->text();
    double radius = Radius.toDouble(&c);
    QString Alert = ui->lineEdit_6->text();
    double alert = Alert.toDouble(&c);
    QString ID = ui->lineEdit->text();
    int id = ID.toInt(&c,10);
    Robot* newRobot = new Robot(speed, x, y, theta, radius, alert, id);
    robotList.push_back(newRobot);
}

void RobotGui::on_pushButton_2_clicked()
{
    bool c=1;
    QString ID = ui->lineEdit->text();
    unsigned int id = ID.toInt(&c,10);
    if(id>=robotList.size()) return;
    QString location='('+QString::number(robotList[id]->getX(),'g',6)+','+QString::number(robotList[id]->getY(),'g',6)+')';
    ui->label_4->setText(location);
    QString speed=QString::number(robotList[id]->getVelocity(),'g',6);
    ui->label_6->setText(speed);
    QString degree=QString::number(robotList[id]->getTheta(),'g',6);
    ui->label_8->setText(degree);
}
