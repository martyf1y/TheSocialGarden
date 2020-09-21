//
//  dustParticles.cpp
//  particlesForOF
//
//  Created by Matt Martin on 2/07/17.
//
//

#include "dustParticles.h"

//------------------------------------------------------------------
dustParticle::dustParticle(){
    pos.set(0, 0);
    
    float radius = ofRandom(0,4);
    float yValue = ofRandom(-radius,radius);
    
    float radiusSquared = radius*radius;
    float ySquared = yValue*yValue;
    
    float xValue = sqrt((1 - ySquared/radiusSquared)*radiusSquared);
    int side = ofRandom(0,2);
    xValue = (side>0?xValue:xValue*-1);
    vel.set(xValue, yValue- 3);
    target.set(0, 0);
    acc.set(0, 0);
    
    closeEnoughTarget = 40;
    maxSpeed = 4;
    maxForce = 0.1;
    particleSize = 1;
    isKilled = false;
    
    targetColor = ofColor(0);
    colorWeight = 0;
    colorBlendRate = 0.025;
    
}

void dustParticle::move() {
    
    // Check if particle is close enough to its target to slow down
    float proximityMult = 1.0;
    float distance = ofDist(pos.x, pos.y, target.x, target.y);
    if (distance < closeEnoughTarget) {
        proximityMult = distance/closeEnoughTarget;
    }
    
    // Add force towards target
    ofVec2f towardsTarget(target.x, target.y);
    towardsTarget -= pos;
    towardsTarget.normalize();
    towardsTarget *= (maxSpeed*proximityMult);
    
    ofVec2f steer(towardsTarget.x/2+addWind, towardsTarget.y-0.1);
    steer -= vel;
    steer.normalize();
    steer *= maxForce;
    acc += steer;
    
    // Move particle
    vel += acc;
    if (distance <= 6) {
        particleSize = 1.5;
        isKilled = true;
        pos = target;
        targetColor.a = 255;
    }
    else{
        pos += vel;
    }
    
    acc *= 0;
    addWind *= 0.89;
    
}

void dustParticle::draw() {
    // Draw particle
    
    ofColor currentColor = startColor.lerp(targetColor, colorWeight);
    
    ofSetColor(currentColor);
    ofDrawEllipse(pos.x, pos.y, particleSize, particleSize);
    
    // Blend towards its target color
    if (colorWeight < 1.0) {
        colorWeight = MIN(colorWeight+colorBlendRate, 1.0);
    }
}

