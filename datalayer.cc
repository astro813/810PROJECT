//Description: complete methods in datalayer.hh

#include "datalayer.hh"
using namespace std;

Datalayer::Datalayer(int l, int w):length(l),width(w){
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
    for(int i=1; i<l-1; i++)
        for(int j=1; j<w-1; j++)
            layer[j][i]=0;
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
    
}
