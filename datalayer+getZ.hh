//****************************************************************************************
//Discription: this file Define a logic layer of playground for robots to run 
//****************************************************************************************
#ifndef DATALAYER_HH
#define DATALAYER_HH

#include "Robot.hh"
#include <math.h>


//The class Datalayer makes a logic layer to record robots` locations, radiuses, alert area.
//It is also used for checking collision between robots. 

class Datalayer{
private:
    int length;
    int width;
    int **layer;
    //double coordinate_x;
    //double coordinate_y;
public:

    Datalayer(int ,int);

    ~Datalayer();

    void changeLen(int);

    void changeWid(int);

    int getLength() const;

    int getWidth() const;
    //double getX() const;
    //double getY() const;

    double getZ();

    void clearData();       //clear everything on datalayer

    void loadData();        //paint and robot boundaries on the datalayer
};

#endif // DATALAYER_HH

