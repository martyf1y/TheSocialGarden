/*
 *  Turtle.h
 *  Lsystem
 *
 *  Created by Daan on 02-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
//#include "ofxLSBranch.h"
//#include "ofxLSGeometry.h"

#include <vector>

class Turtle {
    
public:
    Turtle();
    Turtle(string forward, string left, string right, string flower, string leaf);
    vector<ofVec2f> draw(ofVbo& vbo, ofMesh& mesh, string input, float x, float y, float angle,float _branchThickness);
    
    void moveForward(int i, ofMesh& mesh, ofVbo& vbo);
    void turnLeft();
    void turnRight();
    
    void setColours(ofColor flowerCol, ofColor branchCol, ofColor leafCol, ofColor altLeafCol);
    
    void drawFlower(int i, ofMesh& mesh);
    void drawLeaf();
    
    void setGrowLength(int l);
    void setAngle(float a);
    float getAngle();
    void drawLineAsRect(ofVec2f startVec, ofVec2f endVec,float thickness);
    
    
    ofColor  flowerColour = ofColor(55, 30, 255, 100);
    
    ofColor  branchColour = ofColor(0,0,255);
    ofColor  outlineColour = ofColor(255,120);
    
    ofColor  leafColour = ofColor(0,255,0);
    ofColor  altLeafColour = ofColor(0,255,100);
    
    string forward;
    string left;
    string right;
    string flower;
    string leaf;
    
    float angle;
    float curAngle;
    float length;
    float x;
    float y;
    float branchThickness;
    
    vector<float> xHis;
    vector<float> yHis;
    vector<float> aHis;
    
    void pushValues();
    void popValues();
    
    int howBig = 2;
    
    //meshy draw things
    
    
    //ofxLSGeometry                    geometryBuilder;
    std::vector<ofNode> bookmarks;
    std::vector<ofNode> branchContainer;
    
    map<float, float> historySizes;
    pair<float, float> getPrevAndCurrentWidth(float currentLength);
    float getScaledWidth(float currentLength);
    
    bool    scaleWidth = false;
    float width = 2;
    
    // 16 JULY JEN * * * * * * * * * * * * * * * * *
    void setLeafSize(float ls);
    float leafSize = 5;
    
private:
    //  const ofVec3f     origin = ofVec3f(0,0,0);
    ofMesh localMesh;
    
};
