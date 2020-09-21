//
//  plantSection.cpp
//  TheSocialGarden0_1
//
//  Created by Matt Martin on 9/07/17.
//
//

#include "plantSection.h"


plantSection::plantSection(){    
    whichPlantAreWe = "NONE";
    localPlantState = waitingRoom;
    doIHaveASpot = false;
    
    wordsInGroundPos.set(0,0);
    
    plantWordAlpha = 195;
    
    particleColor[0] = ofColor(35, 177, 201, 155); // blue
    particleColor[1] = ofColor(79, 187, 135, 155); // green
    particleColor[2] = ofColor(250, 198, 0, 155); // Orange
    particleColor[3] = ofColor(238, 237, 238, 155); // White
    particleColor[4] = ofColor(244, 0, 105, 155); // pink
    particleColor[5] = ofColor(224, 0, 0, 155); // Red
    particleColor[6] = ofColor(255,255,153, 155); // Light Yellow
    
    messageWidth = 280;
    messageHeight = 180;
}

void plantSection::particleUpdate(){
    checkDeyAllDead = true;
    for (int x = arrayDustParticles.size()-1; x > -1; x--) {
        // Simulate and draw pixels
        if(!arrayDustParticles[x].isKilled){
            arrayDustParticles[x].move();
            checkDeyAllDead = false;
        }
    }
    if(checkDeyAllDead && arrayDustParticles.size() > 0){
        for (int x = arrayDustParticles.size ()-1; x > -1; x--) {
            arrayDustParticles.pop_back();
        }
    }
}

void plantSection::wordsUpdate(){
    
    if(timerEnd < ofGetElapsedTimeMillis() - timerStart){
        plantWordAlpha -=10;
    }
    else if(plantWordAlpha<255){
        plantWordAlpha +=5;
    }
    else{
        plantWordAlpha = 255;
    }
    // wordsAreMoving only becomes false ONCE all new messages are completed
}

void plantSection::draw(){
    
    switch ( localPlantState ) {
        case waitingRoom:
            break;
        case wordsInDirt:
            //  ofSetColor(200, 200, 0);
            //  ofDrawEllipse(wordsInGroundPos, 10, 20);
            break;
        case ParticlesBursting:
            for (int x = arrayDustParticles.size()-1; x > -1; x--) {
                arrayDustParticles[x].draw();
            }
            break;
        case WordsStayUp:
            newColor.a = plantWordAlpha;
            plantParagraph.setColor(newColor);
            plantParagraph.draw(messagePositionX - messageWidth/2, messagePositionY - messageHeight/2);
            break;
        default:
            cout<<"Error, bad draw input, quitting\n";
            break;
    }
    
    if(doIHaveASpot){ // Used for the name of the plant setting opacity
        if(wordColorOpacity < 255){
            wordColorOpacity += 5;
        }
    }
    else{
        if(wordColorOpacity > 0){
            wordColorOpacity -= 5;
        }
    }
    localPlantName.setIndent(0);
    localPlantName.setColor(ofColor(255, 255, 255, wordColorOpacity));
    localPlantName.setText(whichPlantAreWe);
    localPlantName.setAlignment(ofxParagraph::ALIGN_CENTER);
    localPlantName.draw(iGrowHere.x - localPlantName.getWidth()/2,ofGetHeight()-messageFontSize-50);
}

// Makes all particles draw the next word
void plantSection::nextWord() {
    // Draw word in memory
    pg.allocate(messageWidth, messageHeight);
    
    plantParagraph.setWidth(messageWidth);
    plantParagraph.setText(thisPlantTweet);
    plantParagraph.setColor(ofColor(255, 255, 255));
    plantParagraph.setIndent(0);
    plantParagraph.setLeading(1);
    
    pg.begin();
    ofClear(0,0,0,0);
    plantParagraph.draw(0,messageFontSize);
    pg.end();
    
    ofPixels pixels;
    pg.readToPixels(pixels);
    //ofSaveImage(pixels,"hello.png");     // Next color for all pixels to change to
    
    ofColor beginColor = ofColor(239, 193, 57);
    newColor = particleColor[int(ofRandom(0, 7))];
    for (int i = 0; i < (messageWidth*messageHeight)-1; i+=3) {
        // Convert index to its coordinates
        int x = i % pixels.getWidth();
        int y = i / pixels.getWidth();
        
        // Only continue if the pixel is not blank
        if (pixels.getColor(x, y) != ofColor(0,0,0,0)) {
            
            dustParticle newParticle;
            
            newParticle.target.x = messagePositionX + x - messageWidth/2;
            newParticle.target.y = messagePositionY + y - messageHeight/2 - messageFontSize;
            newParticle.pos = iGrowHere;
            
            newParticle.maxSpeed = ofRandom(4.5, 6.0);
            newParticle.maxForce = newParticle.maxSpeed*0.025;
            newParticle.particleSize = ofRandom(3, 6);
            newParticle.colorBlendRate = ofRandom(0.0025, 0.03);
            
            // Blend it from its current color
            newParticle.startColor = beginColor;
            newParticle.targetColor = newColor;
            newParticle.colorWeight = 0;
            newParticle.addWind = ofRandom(-10,10);
            arrayDustParticles.push_back(newParticle);
        }
    }
}


