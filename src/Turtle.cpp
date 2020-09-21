/*
 *  Turtle.cpp
 *  Lsystem
 *
 *  Created by Daan on 02-04-11.
 *  Copyright 2011 Daan van Hasselt. All rights reserved.
 *
 
 F move forward at distance L(Step Length) and draw a line
 f move forward at distance L(Step Length) without drawing a line
 + turn left A(Default Angle) degrees
 ‚Äì turn right A(Default Angle) degrees
 \ roll left A(Default Angle) degrees
 / roll right A(Default Angle) degrees
 ^ pitch up A(Default Angle) degrees
 & pitch down A(Default Angle) degrees
 | turn around 180 degrees
 J insert point at this position
 ‚Äú multiply current length by dL(Length Scale)
 ! multiply current thickness by dT(Thickness Scale)
 [ start a branch(push turtle state)
 ] end a branch(pop turtle state)
 A/B/C/D.. placeholders, used to nest other symbols
 
 *
 *
 *
 */

#include "Turtle.h"


Turtle::Turtle(){
    angle = 90;
    curAngle = 0;
    length = 10;
    x = ofGetWidth()/2;
    y = ofGetHeight()/2;
    
    bookmarks.clear();
    branchContainer.clear();
    historySizes.clear();
    //SETUP THE ROOT NODE to start growing.
    /* shared_ptr<ofNode> root(new ofNode);
     root->setPosition(ofVec3f(0,0,0));
     branchContainer.push_back(root);*/
    
}

Turtle::Turtle(string _forward, string _left, string _right, string _flower, string _leaf){
    forward = _forward;
    left = _left;
    right = _right;
    flower = _flower;
    leaf = _leaf;
    
    angle = 90;
    curAngle = 0;
    length = 10; //default
    x = ofGetWidth()/2;
    y = ofGetHeight()/2;
    
    bookmarks.clear();
    branchContainer.clear();
    historySizes.clear();
    /* //SETUP THE ROOT NODE to start growing.
     shared_ptr<ofNode> root(new ofNode);
     root->setPosition(ofVec3f(0,0,0));
     branchContainer.push_back(root);*/
    
}

void Turtle::setColours(ofColor flowerCol, ofColor branchCol, ofColor leafCol, ofColor altLeafCol) {
    
    flowerColour = flowerCol;
    branchColour = branchCol;
    leafColour = leafCol;
    altLeafColour = altLeafCol;
    
}

vector<ofVec2f> Turtle::draw(ofVbo& vbo, ofMesh& mesh, string input, float _x, float _y, float _angle, float _branchThickness) {
    x = _x;
    y = _y;
    branchThickness = _branchThickness;
    
    bool branching = false;
    
    curAngle = _angle;
    
    //  localMesh.clear();
    vector<ofVec2f> coords;
    
    int length = input.length();	// length of the input string
    //cout << "length " << length << endl;
    
    //string substr[length];				// split into 1-char substrings
    //vector<string> substr(length);
    string *substr = new string[length];
    
    for(int i = 0; i < length; i++){
        substr[i] = input.substr(i,1);
    }
    
    for(int i = 0; i < length; i++){		// check every character
        
        if(substr[i] == forward) {		// and act accordingly
            
            branching=true; //see branching conditional below
            
            moveForward(i, mesh, vbo);
            ofVec2f pos = ofVec2f(x, y);
            // mesh.addVertex(pos);
            coords.push_back(pos);
        }
        
        if(substr[i] == left) {
            
            /*
             shared_ptr<ofNode> newJoin(new ofNode);
             newJoin->setParent(*branchContainer.back());
             newJoin->roll(+angle);
             branchContainer.push_back(newJoin);*/
            
            turnLeft();
        }
        
        if(substr[i] == right) {
            /*shared_ptr<ofNode> newJoin(new ofNode);
             newJoin->setParent(*branchContainer.back());
             newJoin->roll(-angle);
             branchContainer.push_back(newJoin);
             */
            
            turnRight();
        }
        
        if(substr[i] == "[") {
            //store whatever is at the back of the branch container
            //bookmarks.push_back(branchContainer.back());
            
            pushValues();
            
        }
        
        if(substr[i] == "]") {
            //retrieve whatever was put in bookmarks
            //branchContainer.push_back(bookmarks.back());
            //bookmarks.pop_back();
            
            popValues();
        }
        
        if (substr[i] == flower) {
            drawFlower(i, mesh);
        }
        if (substr[i] == leaf) {
            drawLeaf();
        }
        
        if (substr[i] == "&") { //  & pitch down A(Default Angle) degrees
            //curAngle += angle/3;
            //length = length/2;
        }
        if (substr[i] == "^") { //   ^ pitch up A(Default Angle) degrees
            // curAngle -= angle/3;
            //length = length*2;
            
        }
        if (substr[i] == "|") { // | turn around 180 degrees
            // curAngle = angle-180;
        }
        if (substr[i] == "\\") { // roll left A(Default Angle) degrees
            // drawFlower(i);
            // curAngle += angle*2;
        }
        if (substr[i] == "/") { // roll right A(Default Angle) degrees
            // curAngle -= angle*2;
        }
        
        if (branching) {
            
            
            mesh.append(localMesh);
            //ofNode beginBranch = branchContainer.back();
            
            //End of the branch ...
            //ofNode endBranch;
            //endBranch->setParent(*branchContainer.back());
            //endBranch->move(ofVec3f(0, length, 0));
            
            //Something about a bounding box
            //maybeVectorExpandsBoundingBox(endBranch->getGlobalPosition());
            
            // Create a new branch based on
            // auto widths = getPrevAndCurrentWidth(length);
            // auto newBranch = ofxLSBranch(*beginBranch, *endBranch, widths);
            
            //ofxLSGeometryAvailable geometry = GL_LINES;
            //int resolution = 10;
            
            //geometryBuilder.putIntoMesh(newBranch, mesh, geometry, resolution, length, textureRepeat);
            // branchContainer.push_back(endBranch);
            branching = false;
            
        }
        
    }
    
    //  branchContainer.clear();
    //  bookmarks.clear();
    //  historySizes.clear();
    return coords;
    
}


// In case there is the need to keep track of the differents branches width and lenght,
// as in the case when scaleWidth is set to true, this method does 2 things:
// 1) it stores all the sizes in the container historySizes, for each pair, the first calue is the lenght
// the second the width.
// 2) It returns the current width and the previous one, as the method name says.
// If there is no need to keep track of the branch  width, just returns a pair containing
// the default width, both for the prev and current width.
pair<float, float> Turtle::getPrevAndCurrentWidth(float currentLength) {
    if(!scaleWidth){
        return make_pair(width, width);
    }
    
    
    float currentWidth = (scaleWidth) ? getScaledWidth(currentLength) : width;
    if (historySizes.empty()) {
        historySizes.insert(make_pair(currentLength, currentWidth));
        return (make_pair(currentWidth, currentWidth));
    } else {
        map<float, float>::iterator current;
        if (historySizes.find(currentLength) == historySizes.end()) {
            historySizes.insert(make_pair(currentLength, currentWidth));
            current = historySizes.begin();
        } else {
            current = historySizes.find(currentLength);
        }
        auto prev = current;
        ++prev;
        return make_pair(prev->second, current->second);
    }
}



void Turtle::pushValues(){
    xHis.push_back(x);
    yHis.push_back(y);
    aHis.push_back(curAngle);
}

void Turtle::popValues(){
    x = xHis[xHis.size()-1];
    y = yHis[yHis.size()-1];
    curAngle = aHis[aHis.size()-1];
    
    xHis.pop_back();
    yHis.pop_back();
    aHis.pop_back();
}

void Turtle::moveForward(int i, ofMesh& mesh, ofVbo& vbo){
    
    float newX = x + (cos(ofDegToRad(curAngle))*length);
    float newY = y + (sin(ofDegToRad(curAngle))*length);
    
    float sw = 6;
    
    /*
     localMesh.addVertex(ofPoint(x, y));
     localMesh.addVertex(ofPoint(newX, newY));
     localMesh.addIndex(i);
     */
    
    /*
     mesh.addVertex(ofVec3f(x+2, y+2));
     mesh.addVertex(ofVec3f(newX+50, newY+50));
     mesh.addVertex(ofVec3f(newX, newY-length/2));
     mesh.addIndex(x+2);
     */
    /* doesnt work
     
     ofPolyline line;
     line.addVertex(ofPoint(x, y));
     line.addVertex(ofPoint(newX, newY));
     line.close();
     */
    
    // DRAW LINES OF BRANCH COLOUR
    /*
     ofSetColor(branchColour);
     ofSetLineWidth(length/(i+2)+3);
     ofDrawLine(x,y,newX, newY);
     */
    ofPushStyle();
    shared_ptr<ofPath> path(new ofPath);
    
    ofNoFill();
    //ofSetColor(branchColour);
    //path->setFillColor(branchColour);
    path->setStrokeColor(branchColour);
    //path->hasOutline();
    path->setStrokeWidth(branchThickness);
    //path->circle(x,y,3);
    path->moveTo(x,y);
    path->lineTo(x,y);
    path->lineTo(newX,newY);
    path->close();
    
    path->draw();
    ofPopStyle();
    
    //mesh = path->getTessellation();
    
    // mesh = polyline.getPath().getTessellation();
    //vbo.setMesh(mesh, GL_STATIC_DRAW);
    
    /*
     float leafX = x + (cos(ofDegToRad(curAngle-45))*length);
     float leafY = y + (sin(ofDegToRad(curAngle-45))*length);
     
     
     ofPolyline curve;
     
     curve.curveTo(x, y);
     curve.curveTo(x, y);
     curve.curveTo(x-10, y);
     curve.curveTo(leafX, leafY);
     curve.curveTo(leafX, leafY); // Necessary Duplicate for Control Point
     
     curve.simplify(0.50);
     curve.draw();
     
     //leaf.draw();
     */
    
    /*
     ofSetColor(leafColour);
     ofPolyline leaf;
     leaf.curveTo(x*cos(angle), 0, newY*sin(angle));
     leaf.curveTo(newX*cos(angle), 0, newY*sin(angle));
     leaf.close();
     
     */
    
    //mesh.addVertex(ofVec2f(x, y));
    //mesh.addVertex(ofVec2f(newX, newY));
    
    
    // vert.x += ofRandom(-1,1);
    // vert.y += ofRandom(-1,1);
    
    //cout << "move forward from: " << x << ", " << y << " to " << newX << ", " << newY << endl;
    // ofEnableAlphaBlending();
    //   ofSetColor(255, 0, 0);
    //   ofSetLineWidth(2);
    //    ofDrawLine(x, y, newX, newY);
    
    //ofVec2f startVec = ofVec2f(x,y);
    //  ofVec2f endVec = ofVec2f(newX,newY);
    // drawLineAsRect(startVec,endVec,5);
    
    
    //ofDrawLine(x,y,newX, newY);
    // ofPolyline b;
    // b.curveTo(x*cos(angle), 0, newY*sin(angle));
    // b.curveTo(newX*cos(angle), 0, newY*sin(angle));
    
    //ofSetLineWidth(3);
    //ofDrawLine(x,y,x-15, y);
    // ofPushMatrix();
    //   ofTranslate(startVec.x,startVec.y);
    //  ofDrawEllipse(newX-x,newY-y,length,length);
    //ofPopMatrix();
    
    /*
     ofPath path;
     ofNoFill();
     ofSetColor(0,174,255);
     path.hasOutline();
     path.setCircleResolution(80);
     path.circle(x,y,2);
     path.setStrokeWidth(2);
     path.draw();
     */
    
    //   ofPolyline line;
    
    // mesh = path.getTessellation();
    
    /*
     ofFill();
     ofSetColor(outlineColour);
     ofDrawEllipse(x,y,length/2,length/2);
     
     ofSetLineWidth(sw);
     ofSetColor(branchColour);
     ofNoFill();
     ofDrawEllipse(x,y,length/2,length/2);
     */
    // ofDrawEllipse(x+(cos(ofDegToRad(curAngle))*length*0.5),y+(sin(ofDegToRad(curAngle))*length*0.5),length, length);
    
    //ofDrawEllipse(newX-4,newY-5,7,7);
    //ofDrawEllipse(newX+4,newY-3,5,5);
    
    x = newX;
    y = newY;
    
}

void Turtle::turnLeft(){
    //	cout << "turn left" << endl;
    float wind = (sin(ofGetElapsedTimeMillis()/3000.000)*2);
    curAngle += angle+wind;
}

void Turtle::turnRight(){
    //	cout << "turn right" << endl;
    float wind = (sin(ofGetElapsedTimeMillis()/3000.000)*2);
    curAngle -= angle+wind;
}

void Turtle::drawFlower(int i, ofMesh& mesh){
    ofPushStyle();
    shared_ptr<ofPath> path(new ofPath);
    
    path->setFillColor(flowerColour);
    path->setCircleResolution(80);
    path->circle(x,y,2);
    //path->setStrokeWidth(1);
    path->draw();
    
    mesh = path->getTessellation();
    mesh.addColor(flowerColour);
    ofPopStyle();
    //ofSetColor(flowerColour);
    
    //  ofDrawEllipse(x,y,7,7);
    //  ofDrawEllipse(x-4,y-5,7,7);
    //ofDrawEllipse(newX+4,newY-3,5,5);
    
}



// 16 JULY JEN * * * * * * * * * * * * * * * * *

void Turtle::drawLeaf() {
    
    float drawnleafSize = leafSize;
    if (length <6) {
        drawnleafSize = leafSize*0.5;
    }
    ofSetColor(leafColour);
    ofDrawEllipse(x-4,y,drawnleafSize,drawnleafSize*2);
    ofDrawEllipse(x+4,y-2,drawnleafSize,drawnleafSize*2);
}

void Turtle::setLeafSize(float ls) {
    leafSize = ls;
}


void Turtle::setGrowLength(int l) {
    length = l;
}

void Turtle::setAngle(float a) {
    angle = a;
}

float Turtle::getAngle() {
    return angle;
}

void Turtle::drawLineAsRect(ofVec2f startVec, ofVec2f endVec,float thickness) {
    float angle = atan((endVec.y-startVec.y)/(endVec.x-startVec.x));
    ofPushMatrix();
    ofTranslate(startVec.x,startVec.y);
    ofRotate(ofRadToDeg(angle));
    float lineLength = (endVec.x - startVec.x)/cos(angle);
    
    ofRect(0,-thickness/2,lineLength,thickness);
    
    
    ofPopMatrix();
}
