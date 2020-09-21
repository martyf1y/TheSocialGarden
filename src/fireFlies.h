//
//  fireFlies.h
//  ATasteOfTheMoon
//
//  Created by Matt Martin on 6/07/17.
//
//

#pragma once
#include "ofMain.h"

class fireFly {
    
public:
    
    fireFly(int rX);
    
    void move();
    void display();
    bool toPlant();
    
    float x, y, r, fx, fy;
    int i=1, j=1;
    ofColor c;
    ofColor t = ofColor(0, 0, 0, 0);
    bool checkNow = false;
    
    ofVec2f fireFlyPos;
    ofVec2f vel;
    ofVec2f acc;
    ofVec2f target;
    
    float closeEnoughTarget;
    float maxSpeed;
    float maxForce;
};






