//getZ()modified by Jun Chen
//Description: complete methods in datalayer.hh

#include "map.hh"
#include "Robot.hh"
using namespace std;

extern vector<Robot *> robotList;
Map::Map(int l, int w):length(l),width(w){
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

Map::~Map()
{
    delete [] layer;
}

void Map::changeLen(int l){
    length=l;
}

void Map::changeWid(int w){
    width=w;
}

int Map::getLength() const{
    return length;
}

int Map::getWidth() const{
    return width;
}


void Map::clearData(){
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


//avoidCrash() can estimate whether the alert area of the current robot will overlap others` alert areas.
//If it does, this method will call Robot::record to record the information of other robots.

void Map::avoidCrash(){
    for(auto i=robotList.begin();i<robotList.end();i++){    //create boundaries on the map
        vector<int> identify;
        double r=(*i)->getAlert();                          //
        for(int x=(*i)->getX()-r;x<=(*i)->getX()+r;x++) //x-alert <=x=alert
            for(int y=(*i)->getY()-sqrt(r*r-(x-(*i)->getX())*(x-(*i)->getX())); //y-sqrt(alert*alert
                y<=(*i)->getY()+sqrt(r*r-(x-(*i)->getX())*(x-(*i)->getX()));y++)
            {
                if(y>=0&&y<400&&x>=0&&x<400)                //to make sure painting will not update out of boundary
                if(layer[y][x]==0)
                    layer[y][x]=(*i)->getID()*10+1;         //plus 1 to mark this is an alert area, not a robot itself.
                else{
                    int j;
                    for(j=0; j<identify.size();j++)
                    {
                        if(layer[y][x]/10==identify[j]) break;
                    }
                    if(j==identify.size()){
                        (*i)->record(layer[y][x]/10);
                        identify.push_back(layer[y][x]/10);
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
