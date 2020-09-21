//
//  Plant.hpp
//  plantStructure
//
//  Created by JLG on 8/07/17.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include "ofMain.h"
#include <stdio.h>

#include "Turtle.h"
#include "ofxLSystemGrammar.h"
#include "of3dPrimitives.h"


typedef enum {
    KOWHAI,
    HOROEKA,
    MANUKA,
    HARAKEKE,
    TAWHAI,
    KOHUHU,
    KAIKAWAKA
} PlantType;




class Plant {
    
public:
    Plant();
    Plant(int iid, int iage, PlantType type, float ix, float iy);
    void update(float level, float length, float angle);
    virtual void display(ofVbo& vbo);
    void setColours(ofColor c1, ofColor c2, ofColor c3);
    
    //void updateStatus(float newX, float newYInter, float newYBack);
    void updateStatus();
    void setStatus(int s);
    int getStatus();
    int getAge();
    void setPosition(float newX, float newY);
    void setYPosition(float newY);
    
    PlantType getPlantType();
    
    int id;
    string plantName = "Default";
    
    string axiom = "F";
    
    float x = 0;
    float y = 0;
    float z = 0;
    
    
    float currentHeight = 5;
    float branchThickness = 2;
    float maxHeight = 50;
    
    ofColor schemeColour1,schemeColour2,schemeColour3;
    
    
    // L System and Drawing Turtle
    Turtle turtle;
    vector<string> rules;
    vector<string> result;
    
    
    float growLength = 2.0;
    int growLevel = 1;
    float growAngle = 12.5;
    
    float originalAngle = 7;
    float originalLength = 7;
    int maxLevel = 3;
    int maxLevel1Size=10;
    int maxLevel2Size=20;
    
    vector<ofVec2f> positions;
    
    bool somethingChanged = true;
    int prevGrowLevel=0;
    float prevGrowLength=0;
    float prevGrowAngle=10;
    
    PlantType plantType;
    
    bool gotResult=false;
    bool gotResult2 = false;
    
    
    // meshy things
    ofMesh mesh;
    
    // 15 JULY JEN * * * * * * * * * * * * * * * * *
    void growMyself(float g);
    void checkGrowLevel();
    void moveMyselfBack();
    
    
    void setDestination(int dx, int dy, float dz);
    void killMe();
    
    float destX, destY, destZ;
    float moveBackAmount = 0.05;
    float maxGrowLength = 20;
    
    bool movingToDest=false;
    
    
    // 16 JULY JEN * * * * * * * * * * * * * * * * *
    float leafSize = 6;
    ofVec2f getPos();
    
    
    
    
private:
    
    void drawPlant(ofVbo& vbo);
    
    int age = 0;
    int status = 0;
    
    
};
#endif /* Plant_hpp */
