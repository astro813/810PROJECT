//*************************************************************************************************************
//Discription: this cc file contains functions in robot.hh
//add avoid lake and tree
//add method that robot slow down when climing mountain when calculate the high of robot isn't zero, named as Get(z)
//*************************************************************************************************************

#include "Robot.hh"
#include "datalayer.hh"
#include <iostream>
#include <cmath>
using namespace std;

const double PI=3.1415926;

extern Datalayer myLayer;
extern vector<Robot *> robotList;

Robot::Robot(double s,double x,double y,double theta,double r,double a, int ID):
    speed(s),coordinate_x(x),coordinate_y(y),theta(theta),robotsize_radius(r),alert(a), ID(ID){}

Robot::~Robot(){
    count_robots--;
}

double Robot::getSpeed() const{return speed;}

void Robot::change_speed(int s){speed=s;}

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

//the capture funtion can record ID of other robots and boundary which are in the alert area of this robot.
//written Yingsheng Bao
void Robot::capture(int n){
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
            if(newDistance<(*i).distance) {(*i).distance=newDistance; Robot::add_trace(this, robotList[n]);}
        }
        else{
            switch (n){
            case 100:
                newDistance=coordinate_y;
                break;
            case 200:
                newDistance=myLayer.getLength()-coordinate_x;
                break;
            case 300:
                newDistance=myLayer.getWidth()-coordinate_y;
                break;
            case 400:
                newDistance=coordinate_x;
                break;
            default:
                break;
            }
            if(newDistance<(*i).distance) {(*i).distance=newDistance; Robot::add_trace_bound(this, n);}

        }
    }
    else{
        Telecom *object=new Telecom;
        if(n<100){
            object->pointer=robotList[n];
            object->number=n;
            object->distance=sqrt((robotList[n]->coordinate_x-coordinate_x)*(robotList[n]->coordinate_x-coordinate_x)+
                                (robotList[n]->coordinate_y-coordinate_y)*(robotList[n]->coordinate_y-coordinate_y));
            communication.push_back(*object);
            Robot::add_trace(this, robotList[n]);
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
                newDistance=myLayer.getLength()-coordinate_x;
                break;
            case 300:
                newDistance=myLayer.getWidth()-coordinate_y;
                break;
            case 400:
                newDistance=coordinate_x;
                break;
            default:
                break;
            }
            object->distance=newDistance;
            communication.push_back(*object);
            Robot::add_trace_bound(this, n);
        }
    }
}


