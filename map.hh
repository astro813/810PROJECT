//****************************************************************************************
//Discription: this file Define a logic layer of playground for robots to run 
//****************************************************************************************
#ifndef MAP_HH
#define MAP_HH

#include "Robot.hh"
#include <math.h>

//This class saves the location, position, size of the robot
//It is also used for checking collision between robots. 


class Datalayer{
private:
    int length;
    int width;
    int **layer;
public:
    Datalayer(int ,int);

    ~Datalayer();

    void changeLen(int);

    void changeWid(int);

    int getLength() const;

    int getWidth() const;

    void clearData();       //clear everything on datalayer

    void loadData();        //paint and robot boundaries on the datalayer
};

#endif // DATALAYER_HH

