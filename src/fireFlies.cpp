//
//  fireFlies.cpp
//  ATasteOfTheMoon
//
//  Created by Matt Martin on 6/07/17.
//
//
#include "dustParticles.h"

#include "fireFlies.h"

//------------------------------------------------------------------

fireFly::fireFly(int rX)
{
    fireFlyPos.x = ofRandom(0, ofGetWidth());
    fireFlyPos.y = ofRandom(0, 180);
    r = rX;
    fx = ofRandom(0.1, 0.5);
    fy = ofRandom(0.1, 0.5);
    
    vel.set(0, 0);
    target.set(0, 0);
    acc.set(0, 0);
    
    closeEnoughTarget = 40;
    maxSpeed = 4;
    maxForce = 0.1;
}

void fireFly::display(){
    
    if(r == 4){
        int ik = (int)ofRandom(0, 60*r);
        if (ik==1*r) t= ofColor(255, 201, 201, 255);
        if (ik==2*r) t= ofColor(192, 209, 255, 255);
        if (ik==3*r) t= ofColor(237, 238, 255, 255);
        if (ik==4*r) t= ofColor(255, 249, 249, 255);
        if (ik==5*r) t= ofColor(255, 241, 223, 255);
        if (ik==6*r) t= ofColor(226, 120, 34);
        if (ik==7*r) t= ofColor(226, 88, 34);
        if (ik==8*r) t= ofColor(226, 216, 34);
        if (ik==9*r) t= ofColor(150, 42, 0);
    }
    else{
        int ik = (int)ofRandom(0, 60*r);
        if (ik==1*r) t= ofColor(255, 201, 201, 255);
        if (ik==2*r) t= ofColor(192, 209, 255, 255);
        if (ik==3*r) t= ofColor(237, 238, 255, 255);
        if (ik==4*r) t= ofColor(255, 249, 249, 255);
        if (ik==5*r) t= ofColor(255, 241, 223, 255);
        if (ik==6*r) t= ofColor(255, 215, 224, 255);
        if (ik==7*r) t= ofColor(255, 221, 197, 255);
        if (ik==8*r) t= ofColor(240, 230, 140, 255);
        if (ik==9*r) t= ofColor(205, 255, 102, 255);
    }
    //---------------blur/glow ----------
    float h = 3;
    for (float r1 = r*4; r1 > 0; --r1) {
        ofSetColor(t, h);
        ofDrawEllipse(fireFlyPos, r1, r1);
        h=(h+2);
    }
    
    ofSetColor(t);
    ofFill();
    ofDrawEllipse(fireFlyPos, r, r);
}

void fireFly::move() {
    if(ofGetSeconds()%5==0 && !checkNow){
        checkNow = true;
        int check = ofRandom(0,7);
        if(check == 2){
            i = ofRandom(0,4);
            j = ofRandom(0,4);
            i -= 2;
            j -= 2;
            (i==0?i=2:i=i);
            (j==0?j=2:j=j);
        }
    }
    else if(ofGetSeconds()%6==0){
        checkNow = false;
    }
    fireFlyPos.x += j*fx;
    fireFlyPos.y += i*fy;
    
    if (fireFlyPos.y >= ofGetHeight()-r){ i=-1;}
    else if (fireFlyPos.y <= 0+r){ i=1;}
    if (fireFlyPos.x >= ofGetWidth()-r){ j=-1;}
    else if (fireFlyPos.x <= 0+r){ j=1;}
}

bool fireFly::toPlant(){
    
    bool fireFlyMadeIt = false;
    
    // Check if particle is close enough to its target to slow down
    float proximityMult = 1.0;
    float distance = ofDist(fireFlyPos.x, fireFlyPos.y, target.x, target.y);
    if (distance < closeEnoughTarget) {
        proximityMult = distance/closeEnoughTarget;
    }
    
    // Add force towards target
    ofVec2f towardsTarget(target.x, target.y);
    towardsTarget -= fireFlyPos;
    towardsTarget.normalize();
    towardsTarget *= (maxSpeed*proximityMult);
    
    ofVec2f steer(towardsTarget.x, towardsTarget.y);
    steer -= vel;
    steer.normalize();
    steer *= maxForce;
    acc += steer;
    
    // Move particle
    vel += acc;
    if (distance <= 6) {
        fireFlyPos = target;
        return false;
    }
    else{
        fireFlyPos += vel;
    }
    
    acc *= 0;
    return true;
}

