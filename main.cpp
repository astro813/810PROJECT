//***********************************************************************************
//Discription:Main function of robotsimulator
//written by Jun Chen
//***********************************************************************************

#include "robotgui.h"
#include <QApplication>

vector<Robot*> robotList;

int Robot::count_robots = 0;

Datalayer myLayer(400,400);

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    RobotGui w;                                            //create GUI

    //Lake
     //(double s,double x,double y,double theta,double r,double a, int ID): speed(s),coordinate_x(x),coordinate_y(y),theta(theta),robotsize_radius(r),alert(a), ID(ID)
     
    //Robot* LakeA=new Robot(0.0,300.0,300.0,45,35,35,0);
    //Robot* LakeB=new Robot(0.0,350.0,300.0,45,35,35,0);
    //Robot* LakeC=new Robot(0.0,325.0,325.0,45,30,30,0);
    //Robot* LakeD=new Robot(0.0,330.0,275.0,45,30,30,0);

    /*robotList.push_back(LakeA);
    robotList.push_back(LakeB);
    robotList.push_back(LakeC);
    robotList.push_back(LakeD);*/
    
    Robot* LakeE=new Robot(0.0,350.0,350.0,0,50,60,0);
    robotList.push_back(LakeE);

    //Trees
    Robot* TreeA=new Robot(0.0,30.0,330.0,45,5,5,0);
    Robot* TreeB=new Robot(0.0,50.0,100.0,45,5,5,0);
    Robot* TreeC=new Robot(0.0,100.0,20.0,45,5,5,0);
    Robot* TreeD=new Robot(0.0,250.0,100.0,45,5,5,0);
    Robot* TreeE=new Robot(0.0,150.0,250.0,45,5,5,0);

    robotList.push_back(TreeA);
    robotList.push_back(TreeB);
    robotList.push_back(TreeC);
    robotList.push_back(TreeD);
    robotList.push_back(TreeE);

    w.show();                                              //Show the GUI

    return a.exec();                                       //Run
}
