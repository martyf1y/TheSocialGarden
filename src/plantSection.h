//
//  plantSection.hpp
//  TheSocialGarden0_1
//
//  Created by Matt Martin on 9/07/17.
//
//

#pragma once
#include "ofMain.h"
#include "dustParticles.h"
#include "ofxParagraph.h"

enum plantInteractionState {
    waitingRoom,
    wordsInDirt,
    ParticlesBursting,
    WordsStayUp

};

class plantSection {
    
    public:
    
    plantSection();
    
    void particleUpdate();
    void wordsUpdate();
    void draw();
    void nextWord();
    
    vector< string > plantTypeTweet; // The tweets per plant type
    vector <dustParticle> arrayDustParticles; // The word particles
    plantInteractionState localPlantState; // What action is happening
    ofxParagraph plantParagraph, localPlantName; // This is what draws

    bool checkDeyAllDead; // Checks the particles have reached their place
    bool doIHaveASpot; // This tells the plant object that it has a spot and becomes self aware
    bool willINeedToMove;
    int thisIsMySpot;
    int messageWidth;
    int messageHeight;
    int messagePositionX;
    int messagePositionY;
    int plantWordAlpha;
    int nameFontSize;
    int messageFontSize;
    int timerStart;
    int timerEnd = 15000;
    
    ofVec2f wordsInGroundPos, wordsInGroundTarget; // Actual position of message in dirt and its target
    ofVec2f iGrowHere; // This is one of the 7 positions a plant can be

    string whichPlantAreWe;
    int whichPlantAreWeNum;
    string thisPlantTweet;
    int wordColorOpacity = 0;
    ofColor particleColor[7];
    ofColor newColor; // THe color the particles will turn
    ofFbo pg;

};
