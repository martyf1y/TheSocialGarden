//
//  PlantManager.hpp
//  plantStructure
//
//  Created by JLG on 8/07/17.
//
//

#ifndef PlantManager_hpp
#define PlantManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Plant.hpp"

#include "Turtle.h"
#include "ofxLSystemGrammar.h"


typedef enum {
    TREE, // these can have any name you want, eg STATE_CLAP etc
    BUSH,
    FERN
} State;



class PlantManager {
    
public:
    PlantManager();
    void update(int level, float length, float angle);
    void display(float zAxis);
    void createNewPlant(int type, int plantX, int plantY);
    void setColourScheme(int scheme);
    void feedPlants(int typeNum);
    void movePlantsBack(int typeOfPlant, int newY);
    void updateOldPlants(int typeOfPlant);
    
    Plant p1, p2, p3, p4, p5;
    
    vector<vector<Plant>> arrayOfPlants;
    
    ofColor c1 = ofColor(8,25,89);
    ofColor c2 = ofColor(3,99,148);
    ofColor c3 = ofColor(6,150,119);
    
    vector<Plant*> plants;
    
    float groundYForeground, groundYIntermediate, groundYBackground;
    
    // L System and Drawing Turtle
    Turtle turtle;
    vector<string> rules;
    vector<string> result;
    int prevGrowLevel=0;
    
    float growLength = 10.0;
    int growLevel = 1;
    float growAngle = 5.0;
    
    vector<ofVec2f> positions;
    
    int ageOfPlants = 0;
    
    ofMesh forest;
    
    
    ofFbo fbo;
    
    ofImage bgSaved;
    
    // 15 JULY JEN * * * * * * * * * * * * * * * * *
    
    bool feedHappened = false;
    
    
    // 16 JULY JEN
    
    ofFbo   plantFbo;
    ofFbo   secondplantFbo;
    ofImage plantImage;
    
    void removePlant();
    void savePlant(Plant& thisPlant);
    int setPlantYDestination();
    
    
private:
    float x;
    float y;
    float z;
    
    State myState;
    
    int numDifferentPlants = 7; // HARDCODED?? ?
    
    
    
};

#endif /* PlantManager_hpp */









