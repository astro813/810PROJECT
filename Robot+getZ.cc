//*************************************************************************************************************
//Discription: this cc file contains functions in robot.hh
//add avoid lake and tree
//add method that robot slow down when climing mountain when calculate the high of robot isn't zero, named as Get(z)
//*************************************************************************************************************

#include "Robot.hh"
#include "Map.hh"
#include <iostream>
#include <cmath>
using namespace std;

const double PI=3.1415926;

extern Datalayer Layer;
extern vector<Robot *> robotList;
extern double getX();
extern double getY();
Robot::Robot(){};
Robot::Robot(double s,double x,double y,double theta,double r,double a, int ID):
    speed(s),coordinate_x(x),coordinate_y(y),theta(theta),robotsize_radius(r),alert(a), ID(ID){}

Robot::~Robot(){
    count_robots--;
}

double Robot::getVelocity() const{return volocity;}

void Robot::change_velovity(int s){speed=s;}

double Robot::getX() const{return coordinate_x;}

double Robot::getY() const{return coordinate_y;}

void Robot::change_location (double x,double y){
    coordinate_x=x;
    coordinate_y=y;
}

double Robot::getTheta() const{return theta;}

void Robot::change_theta(double th){theta=th;}

int Robot::getCount() const{return count_robots;}

double Robot::getRadius() const{return robotsize_radius;}

double Robot::getAlert() const {return alert;}

int Robot::getID() const {return ID;}

//the record funtion can record ID of other robots and boundary which are in the alert area of this robot.
//written Yingsheng Bao
void Robot::record(int n){
    bool exist=0;
    auto i=communication.begin();
    for(;i<communication.end();i++)
        if((*i).number==n){
            exist=1;
            break;
        }
    if(exist){
        double newDistance;
        if(n<100){
            newDistance=sqrt((robotList[n]->coordinate_x-coordinate_x)*(robotList[n]->coordinate_x-coordinate_x)+
                             (robotList[n]->coordinate_y-coordinate_y)*(robotList[n]->coordinate_y-coordinate_y));
            if(newDistance<(*i).distance) {(*i).distance=newDistance; Robot::newDirection(this, robotList[n]);}
        }
        else{
            switch (n){
            case 100:
                newDistance=coordinate_y;
                break;
            case 200:
                newDistance=myMap.getLength()-coordinate_x;
                break;
            case 300:
                newDistance=myMap.getWidth()-coordinate_y;
                break;
            case 400:
                newDistance=coordinate_x;
                break;
            default:
                break;
            }
            if(newDistance<(*i).distance) {(*i).distance=newDistance; Robot::newDirection_bound(this, n);}

        }
    }
    else{
        rangeSensor *object=new rangeSensor;
        if(n<100){
            object->pointer=robotList[n];
            object->number=n;
            object->distance=sqrt((robotList[n]->coordinate_x-coordinate_x)*(robotList[n]->coordinate_x-coordinate_x)+
                                (robotList[n]->coordinate_y-coordinate_y)*(robotList[n]->coordinate_y-coordinate_y));
            communication.push_back(*object);
            Robot::newDirection(this, robotList[n]);
        }
        else{
            object->number=n;
            object->pointer=nullptr;
            double newDistance;
            switch (n){
            case 100:
                newDistance=coordinate_y;
                break;
            case 200:
                newDistance=myMap.getLength()-coordinate_x;
                break;
            case 300:
                newDistance=myMap.getWidth()-coordinate_y;
                break;
            case 400:
                newDistance=coordinate_x;
                break;
            default:
                break;
            }
            object->distance=newDistance;
            communication.push_back(*object);
            Robot::newDirection_bound(this, n);
        }
    }
}


// newDirection function can caculate the new direction of this robot according to another record robot`s direction.

//written by Jiyu Lei
void Robot::newDirection(Robot* subject, Robot* object){
    int x=subject->coordinate_x-object->coordinate_x;
    int y=subject->coordinate_y-object->coordinate_y;
    double thetaVector = 90 - atan2(y, x) * 180 / PI;                                   //defination of atan2
    if (thetaVector < 0) thetaVector += 360;
    if(object->theta<180){
        if(thetaVector>object->theta && thetaVector<object->theta+180)
            subject->direction.push_back(object->getTheta()+90);
        else{
            double temp=object->getTheta()-90;
            if(temp<0) temp+=360;
            subject->direction.push_back(temp);
        }
    }
    else{
        if(thetaVector>object->theta-180 && thetaVector<object->theta)
            subject->direction.push_back(object->getTheta()-90);
        else{
            double temp=object->getTheta()+90;
            if(temp>=360) temp-=360;
            subject->direction.push_back(temp);
        }
    }
}

//the newDirection_bound funtion caculate the new direction of this robot if it rush into a boundary.
//written by Jiyu Lei
void Robot::newDirection_bound(Robot* subject, int n){
    if(subject->theta<=180){
        switch (n){
            case 100: case 300:
                subject->direction.push_back(180-subject->theta);
                break;
            case 200:
                subject->direction.push_back(360-subject->theta);
                break;
            default:
                break;
        }
    }
    else{
        switch (n){
            case 100: case 300:
                subject->direction.push_back(540-subject->theta);
                break;
            case 400:
                subject->direction.push_back(360-subject->theta);
                break;
            default:
                break;
        }
    }
    
}

//function update() will update new direction and new location of this robot.
//written by Jiyu Lei
void Robot::update(){
    double newTheta;
    for(auto i=direction.begin()+1;i<direction.end();i++){
        if(abs(direction[0]-*i)>180){
            newTheta=(direction[0]+*i)/2+180;
            if(newTheta>360) newTheta-=360;
        }
        else
            newTheta=(direction[0]+*i)/2;
        direction[0]=newTheta;
    }
    if(direction.size()!=0) theta=direction[0];
    direction.clear();
    coordinate_x+=velocity*sin(theta*PI/180);
    coordinate_y+=velocity*cos(theta*PI/180);
}
