//getZ()modified by Jun Chen
//Description: complete methods in datalayer.hh

#include "datalayer.hh"
#include "Robot.hh"
using namespace std;

extern vector<Robot *> robotList;


Datalayer::Datalayer(int l, int w):length(l),width(w){
    l = 10;
    w = 10;
    layer=new int*[w+1];
    for(int i=0; i<=w;i++){
        layer[i]=new int[l+1];
    }
    for(int i=1; i<l; i++){                      //mark the boundary!
        layer[0][i-1]=1000;
        layer[w-1][i]=3000;
    }
    for(int i=1; i<w; i++){
        layer[i][0]=4000;
        layer[i-1][l-1]=2000;
    }
    for(int i=1; i<1-1; i++)
        for (int j=1;j<w-1;j++){
            layer[j][i]={0+i};
        }
}

Datalayer::~Datalayer()
{
    delete [] layer;
}

void Datalayer::changeLen(int l){
    length=l;
}

void Datalayer::changeWid(int w){
    width=w;
}

int Datalayer::getLength() const{
    return length;
}

int Datalayer::getWidth() const{
    return width;
}

/*double Robot::getX() const{
    return coordinate_x;
}
double Robot::getY() const{
    return coordinate_y;
}*/
double Datalayer::getZ(){
    Robot d;
    double x,y,z;
    double z1,z2;
    int i,j;
    x=d.getX();
    y=d.getY();
    if((x-(int)x==0)&&(y-(int)y==0))                      //(x,y) are ints
                                          //default length of side of each unit is 1
    z = layer[j][i];
    z1 = layer[i][j] + (x-(int)x)*(layer[i][j+1]-layer[i][j]);   //x=x1+f(x2-x1)
    z2 = layer[i][j] + (x-(int)x)*(layer[i+1][j+1]-layer[i+1][j]);
    return z = z1 + (y-(int)y)*(z2-z1);
}
void Datalayer::clearData(){
    for(int i=1; i<length-1; i++)
        for(int j=1; j<width-1; j++)
            layer[j][i]=0;
    for(int i=1; i<length; i++){                      //mark the boundary!
        layer[0][i-1]=1000;
        layer[width-1][i]=3000;
    }
    for(int i=1; i<width; i++){
        layer[i][0]=4000;
        layer[i-1][length-1]=2000;
    }
}

//loadData() can estimate whether the alert area of the current robot will overlap others` alert areas.
//If it does, this method will call Robot::capture to capture the information of other robots.

void Datalayer::loadData(){
    for(auto i=robotList.begin();i<robotList.end();i++){    //paint and robot boundaries on the datalayer
        vector<int> detect;
        double r=(*i)->getAlert();                          //
        for(int x=(*i)->getX()-r;x<=(*i)->getX()+r;x++) //x-alert <=x=alert
            for(int y=(*i)->getY()-sqrt(r*r-(x-(*i)->getX())*(x-(*i)->getX())); //y-sqrt(alert*alert
                y<=(*i)->getY()+sqrt(r*r-(x-(*i)->getX())*(x-(*i)->getX()));y++)
            {
                if(y>=0&&y<400&&x>=0&&x<400)                //to make sure painting will not go out of boundary
                if(layer[y][x]==0)
                    layer[y][x]=(*i)->getID()*10+1;         //plus 1 to mark this is an alert area, not a robot itself.
                else{
                    int j;
                    for(j=0; j<detect.size();j++)
                    {
                        if(layer[y][x]/10==detect[j]) break;
                    }
                    if(j==detect.size()){
                        (*i)->capture(layer[y][x]/10);
                        detect.push_back(layer[y][x]/10);
                    }
                }
            }
    }
    for(auto i=robotList.begin();i<robotList.end();i++){
        double r=(*i)->getRadius();
        for(int x=(*i)->getX()-r;x<=(*i)->getX()+r;x++)
            for(int y=(*i)->getY()-sqrt(r*r-(x-(*i)->getX())*(x-(*i)->getX()));
                y<=(*i)->getY()+sqrt(r*r-(x-(*i)->getX())*(x-(*i)->getX()));y++)
                if(y>=0&&y<400&&x>=0&&x<400)
                layer[y][x]=(*i)->getID()*10;
    }    
}
