//
//  Plant.cpp
//  plantStructure
//
//  Created by JLG on 8/07/17.
//
/*
 KOWHAI
 HOROEKA
 MANUKA
 HARAKEKE
 TAWHAI
 KOHUHU
 KAIKAWAKA
 */
//
//  Trees:
//
//       %% *%%
//    %(*%*%(*%*%
//   %%%  %|%(*%&
//         |/  $
//         |
//         |
//
//  1.  KOWHAI     Dragon's Gold Kowhai
//  2.  HOROEKA    Lancewood
//  3.  MANUKA     Tea Tree
//  4.  TAWHAI     Tawhai NZ Beech
//  5.  KAIKAWAKA  Kaikawaka NZ cedar
//
//  Bushes / Shrubs:
//
//       ** ***
//     ** * * ***
//      * ***** *
//
//  6.  KOHUHU     Heart-Shaped Kohuhu / Pittosporum
//
//  Ferns / Flax:
//
//     \ \ \|// ///
//      \ \ | / //
//       \ \|/ //
//
//  7. HARAKEKE    NZ Flax
//

#include "Plant.hpp"

Plant::Plant(){
    id = 0;
    x = ofGetWidth()/2;
    y = ofGetHeight()/2;
    
}

Plant::Plant(int iid, int iage, PlantType type, float ix, float iy) {
    id = iid;
    x = ix;
    y = iy;
    z = 0;
    plantType = type;
    
    
    status = 0; // new plant
    
    
    age = iage;
    growLevel = 1;
    
    //Set up turtle
    turtle = Turtle("F", "-", "+", "G", "L");
    
    
    /*
     SETUP:
     
     L SYSTEM Rules
     Original Plant Angle
     Plant Name
     Colour etc.
     
     
     KOWHAI
     HOROEKA
     MANUKA
     HARAKEKE
     TAWHAI
     KOHUHU
     KAIKAWAKA
     */
    
    axiom = "F";
    
    switch( plantType )
    {
        case KOWHAI:   // 1
            rules = {
                "0.33 -> F -> FF[++F+FF][-FG]",
                "0.33 -> F -> FF[+F+LFF][F-FG]",
                "0.34 -> F -> F[+F+F][F-FG+F][F]"
            };
            
            /*
             rules = {
             "0.33 -> F -> FF[++F+GFLFG][L-FL]G",
             "0.33 -> F -> FF[++FFG][L-FL]G",
             "0.34 -> F -> FF[++LF+FLFG][L-FL]G"
             };*/
            
            
            //rules = {"F-> FF[F]F[-F][+FF]"};
            originalAngle = ofRandom(17,25);
            originalLength = 5;
            maxHeight = 30;
            maxLevel = 3;
            
            branchThickness = 2;
            maxGrowLength = 11;
            maxLevel = 3;
            maxLevel1Size = 5;
            maxLevel2Size = 9;
            leafSize = 2;
            
            plantName = "KOWHAI";
            //schemeColour1 = ofColor(6,150,119);
            //schemeColour2 = ofColor(16,170,119);
            
            /*
             
             KOWHAI - Dragon's Gold Kowhai
             
             Small bushy tree
             
             Colours
             
             Flowers  = ofColor(211,191,35);
             Branches = ofColor(117,106,81);
             Leaves   = ofColor(88,152,64);
             
             
             */
            
            turtle.setColours(ofColor(211,191,35), ofColor(117,106,81), ofColor(88,152,64), ofColor(88,152,64));
            
            break;
            
        case HOROEKA:     // 2  lancewood
            rules = {
                "F ->FFF[-F]F[+F]F[-F][+F]" };
            
            
            originalAngle = 150;
            originalLength = 2;
            maxHeight = 40;
            
            branchThickness = 2;
            maxGrowLength = 7;
            maxLevel = 3;
            maxLevel1Size = 3;
            maxLevel2Size = 5;
            leafSize = 3;
            
            plantName = "HOROEKA";
            
            /*
             
             HOROEKA - Lancewood
             
             Medium sized tree with growth concentrated upwards
             Spikey downward growth as a young tree.
             
             Colours
             
             Flowers  = n/a
             Branches = ofColor(112,70,39);
             Leaves   = ofColor(85,91,41);
             Juvenile leaves = ofColor(54,79,91);
             
             
             */
            
            turtle.setColours(ofColor(54,79,91), ofColor(112,70,39), ofColor(85,91,41), ofColor(54,79,91));
            
            break;
            
        case MANUKA:   // 3
            rules = {
                "0.33 -> F->  F+[[FL]-GF]-[+[FFG]--LF]",
                "0.33 -> F->  F+[+F-[+F]-GFG+FG]-[+[FL+F]--F] ",
                "0.34 -> F->  F+[+F-[+F]-GFG+FG]-[+[F+LF]--LF] "
            };
            
            originalAngle = 20;
            originalLength = 6;
            
            branchThickness = 2;
            maxGrowLength = 15;
            maxLevel = 3;
            maxLevel1Size = 9;
            maxLevel2Size = 12;
            leafSize = 1;
            plantName = "MANUKA";
            
            /*
             
             MANUKA - Tea Tree
             
             Medium well-spread tree
             
             Colours
             
             Flowers  = ofColor(216,87,129);
             Branches = ofColor(44,44,32);
             Leaves   = ofColor(134,141,105);
             
             
             */
            
            turtle.setColours(ofColor(216,87,129), ofColor(44,44,32), ofColor(134,141,105), ofColor(134,141,105));
            
            
            
            break;
        case HARAKEKE:   // 4
            
            rules ={
                
                "0.33 -> F -> [FF+F][F+F+F[FF--F]F+F][-F+F[+F-F]]",
                "0.33 -> F -> [FF+F][F[FF--F]F+F][-F+F[+F-F]]",
                "0.34 -> F -> [FF+F][F[FF--F]F+F][-F[F+F]F]"
            };
            
            //rules = { "F -> [FF]F[-FG]"};
            //originalAngle = 30;
            
            originalAngle = ofRandom(11,24);
            originalLength = 10;
            maxHeight = 60;
            maxLevel = 3;
            
            branchThickness = 3;
            maxGrowLength = 20;
            maxLevel1Size = 11;
            maxLevel2Size = 16;
            
            
            plantName = "HARAKEKE";
            schemeColour1 = ofColor(255,10,85);
            schemeColour1 = ofColor(190,40,87);
            
            /*
             
             HARAKEKE - NZ Flax
             
             Medium wide-spread flax with red-black flowers that spring up on a long skinny stalk
             
             Colours
             
             Flowers  = ofColor(129,28,36);
             Leaves   = ofColor(45,79,24);
             
             */
            
            turtle.setColours(ofColor(129,28,36), ofColor(45,79,24), ofColor(45,79,24), ofColor(45,79,24));
            
            
            break;
        case TAWHAI:   // 5
            rules = {
                "0.33 -> F-> F[FF]F[F-FL][+F]",
                "0.33 -> F-> F[+F+F]F[+L]F[+FL]",
                "0.34 -> F-> F[FF]F[F+L+F][F-L-F][F+F]"
            };
            
            /*
             rules = {
             "F-> FFFF[F[-A]BFF]L",
             "B-> F[-F][+F++F]-L",
             "A-> FF-[+F-F---F]LA"
             };
             
             */
            
            originalAngle = ofRandom(18,22);
            originalLength = 4;
            maxHeight = 50;
            maxLevel = 3;
            
            plantName = "TAWHAI";
            
            /*
             
             TAWHAI - NZ Beech
             
             Tall tree with limbs stretching out to the sides (when given room to grow)
             Leaves are jagged round shapes
             
             Colours
             
             Flowers    = ofColor(240,16,29);
             Branches   = ofColor(146,150,137);
             Leaves     = ofColor(68,116,3);
             Alt Leaves = ofColor(125,85,62);
             
             */
            
            turtle.setColours(ofColor(240,16,29), ofColor(146,150,137), ofColor(68,116,3), ofColor(125,85,62));
            
            
            break;
        case KOHUHU:   // 6
            rules = {
                "0.33 -> F -> FF[+F][+F][-F+FL-LFL+L]",
                "0.33 -> F -> F[+F][+F]F[-F+F+[+F]F+L]",
                "0.34 -> F -> FF[F][+F][-F-LFL+[L]FL]"
            };
            originalAngle = 33;
            originalLength = 2;
            maxHeight = 30;
            maxLevel = 3;
            
            branchThickness = 3;
            maxGrowLength = 8;
            maxLevel1Size = 4;
            maxLevel2Size = 7;
            
            plantName = "KOHUHU";
            
            /*
             
             KOHUHU - Heart-Shaped Kohuhu / Pittosporum
             
             Small-medium bush with stickly thin branches and heart-shaped leaves.
             
             Colours
             
             Flowers    = ofColor(219,212,53);
             Branches   = ofColor(154,108,103);
             Leaves     = ofColor(68,116,3);
             Alt Leaves = ofColor(144,172,117);
             
             */
            
            turtle.setColours(ofColor(219,212,53), ofColor(154,108,103), ofColor(68,116,3), ofColor(144,172,117));
            
            
            
            break;
        case KAIKAWAKA:   // 7  CEDAR
            rules = {
                "0.33 -> F-> FFF[-F-[++FL]---F][+++[--F]+++F]",
                "0.33 -> F-> FFF[-[+F+L]-F][+++[--F]+++F]",
                "0.34 -> F-> FFF[-[+FL]F---FG][+++F]"
            };
            
            /*
             "0.33 -> F -> FF[FL+LFL+FL+FFL][-F]L",
             "0.33 -> F -> FF[F+FLL+FL+FLF][-L]",
             "0.34 -> F -> FF[F+F+FL+FFLFLL][-L]G"
             */
            
            /*rules = {
             "0.25 -> F -> FFF+[+F]LFG",
             "0.25 -> F -> FFF+[-F+F-F]",
             "0.25 -> F -> FF[-F+FL-FL]",
             "0.25 -> F -> FFF+[-F+F-F]G"
             };*/
            originalAngle = 8;
            maxHeight = 30;
            maxLevel = 3;
            
            branchThickness = 2.5;
            originalLength = 3;
            leafSize = 6;
            
            maxGrowLength = 8;
            maxLevel1Size = 4;
            maxLevel2Size = 7;
            
            plantName = "KAIKAWAKA";
            // schemeColour1 = ofColor(66,200,80);
            // schemeColour2 = ofColor(66,240,119);
            
            
            /*
             
             KAIKAWAKA - NZ Mountain Cedar
             
             Tall Tree with long trunk
             
             Colours
             
             Flowers    = ofColor(219,212,53);
             Branches   = ofColor(154,108,103);
             Leaves     = ofColor(68,116,3);
             Alt Leaves = ofColor(144,172,117);
             
             */
            
            turtle.setColours(ofColor(219,212,53), ofColor(154,108,103), ofColor(68,116,3), ofColor(68,116,3));
            
            break;
            
            
            
        default:
            rules = { "F -> F[F-F]"};
           // cout <<  "oooh default treee" << endl;
            originalAngle = 22;
            plantName = "Default";
            
            break;
    }
    
    // take this out
    //maxHeight = 100;
    
    //Give turtle some data
    turtle.setGrowLength(originalLength);
    turtle.setAngle(originalAngle);
    
    growAngle = originalAngle;
    
    //Push RESULTS back into array
    
    /* rules = { "F -> F[F-F]"};
     
     {F: ['F[+F]F[-F]F', 'F[+F]F', 'F[-F]F'] }
     {F: {'F[+F]F[-F]F':.33, 'F[+F]F':.33, 'F[-F]F':.34} }
     */
    
    
    result = ofxLSystemGrammar::buildSentences(rules, growLevel, axiom);
    
    // draw Turtle
    //positions = turtle.draw(vbo, mesh, result.back(), x, y, 270);	// input string, x, y, starting angle
    
    
    
    // Create RULE
    // rules = { "F -> F[F][FFF][FF]F[-F]F+GF",
    //    "F -> [-F]F+[FF]-F"
    //};
    
    //bloody overkill
    //vector<string> r1 = ofxLSystemGrammar::buildSentences(rules, growLevel, "F");
    // vector<string> r2 = ofxLSystemGrammar::buildSentences(rules, growLevel, "F");
    // vector<string> r3 = ofxLSystemGrammar::buildSentences(rules, growLevel, "F");
    
}

void Plant::update(float level, float length, float angle) {
    
    
    if (status <4) {
        
        if (prevGrowLevel !=growLevel || prevGrowLength !=growLength || prevGrowAngle != growAngle) {
            somethingChanged = true;
        }
        
        
        moveMyselfBack();
        
        if (status <2) {
            //new guy, grow quicker
            growMyself(0.005);
        } else {
            //old bugger, grow slowly
            growMyself(0.00005); //super slowly... ??
        }
        
    }
    
    
}

void Plant::moveMyselfBack() {
    
    if (movingToDest) {
        
        // MOVE BACK AND SHRINK?
       // z -=0.03;
        
        // Y CHECK
        if (z > destZ) {
            z -= moveBackAmount;
            if(destX > ofGetWidth()*0.5){
                destX += moveBackAmount*0.5;
            }
            else if(destX > ofGetWidth()*0.5){
                destX -= moveBackAmount*0.5;
            }
            // cout << destY << endl;
            
        } else {
           // destYReached=true;
        }
        
        moveBackAmount = 0.03;
        
        bool destYReached = false;
        bool destXReached = false;
        
        // Y CHECK
        if (y > destY) {
            y -= moveBackAmount;
            
            // cout << destY << endl;
            
        } else {
            destYReached=true;
        }
    
        // X CHECK
        if (x > (destX+2)) {
            x -= moveBackAmount;
        } else if (x < (destX-2)) {
            x += moveBackAmount;
        } else {
            destXReached = true;
        }
        
        if (destYReached && destXReached) {
            
            //queue plant for archiving
            cout << "Archiving PLANT" << endl;
            status = 3;
            
        }
    }
    
}

void Plant::display(ofVbo& vbo) {
    
    // display plant if not super dead
    if (status < 4) {
        
        ofPushMatrix();
        ofTranslate(0,0,z);
        
        drawPlant(vbo);
        
        ofPopMatrix();
    }
    
}

void Plant::drawPlant(ofVbo& vbo) {
    
    //L SYSTEM UPDATE - to be done per plant every frame ...
    
    turtle.setAngle(growAngle);
    turtle.setGrowLength(growLength);
    //string text = ofToString(turtle.getAngle());
    
    //Call on system growth level if changed // or if anything else has changed
    if (somethingChanged) {
        somethingChanged=false;
        
        //result = ofxLSystemGrammar::buildSentences(rules, growLevel, axiom);
        
        //Draw Turtle Graphics
        /*
         for (int i=0; i < result.size(); i++) {
         positions = turtle.draw(result[i], 100+(i*310), ofGetHeight()-100, 270);	// input string, x, y, starting angle
         }*/
        
        mesh.clear();
        //mesh.setMode();
        
        if (growLevel==2 && !gotResult2) {
            result = ofxLSystemGrammar::buildSentences(rules, growLevel, axiom);
            gotResult2 = true;
        }
        
        
        if (growLevel==3 && !gotResult) {
            result = ofxLSystemGrammar::buildSentences(rules, growLevel, axiom);
            gotResult=true;
        }
        
        //  if (growLevel<2) {
        //Draw Turtle Graphics
        //   positions = turtle.draw(mesh, result.back(), x, y, 270);
        //  }
        
        
        prevGrowLevel = growLevel;
        prevGrowLength = growLength;
        prevGrowAngle = growAngle;
        
        /*
         float circx, circy, circz;
         
         //Just draw the points where the turtle goes
         for (int i=1; i< positions.size(); i++) {
         
         ofPolyline circle;
         circle.arc(0,0,10,10,0,360);
         
         for(int i=0; i<circle.getVertices().size()-1; i++){
         mesh.addVertex(circle[i]+positions[i]);
         mesh.addVertex(circle[i+1]+positions[i]);
         mesh.addVertex(ofVec3f(0,0)+positions[i]);
         }
         //ofSetColor(schemeColour1);
         //ofDrawEllipse(positions[i].x, positions[i].y,5,5);
         //ofSetColor(schemeColour2);
         //ofDrawLine(positions[i-1].x, positions[i-1].y,positions[i].x, positions[i].y);
         
         
         // mesh.addVertex(positions[i]);
         }
         */
        
        
        
    }
    
    
    //Draw Turtle Graphics
    positions = turtle.draw(vbo, mesh, result.back(), x, y, 270, branchThickness);
    
    
    
    //Draw Turtle Graphics
    // positions = turtle.draw(result.back(), x, y, 270);
    
    //  vbo = mesh;
    // mesh.draw();
    // mesh.drawWireframe();
    //mesh.clear();
    
    //mesh.clear();
    
    //ofPolyline circle;
    //clear the mesh
    
    /*
     circle.arc(0,0,50,50,0,360);
     for(int i=0; i<circle.getVertices().size(); i+=2){
     mesh.addVertex(positions[i]);
     mesh.addVertex(circle[i+1]);
     mesh.addVertex(ofVec3f(0,0));
     mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
     }*/
    
    //   mesh.draw();
    
}

void Plant::setColours(ofColor c1, ofColor c2, ofColor c3) {
    
    schemeColour1 = c1;
    schemeColour2 = c2;
    schemeColour3 = c3;
    
    //  ofSetColor(leafColour);
}

void Plant::checkGrowLevel() {
    
    //Move up to next grow level =
    if (growLength > maxLevel1Size) {
        growLevel=2;
    }
    if (growLength > maxLevel2Size) {
        growLevel=maxLevel;
    }
    
}

void Plant::growMyself(float g) {
    
    
    switch( plantType )
    {
        case KOWHAI:
            break;
            
        case HOROEKA:
            if (growLength<maxLevel2Size) {
                growAngle = 150;
                rules = {
                    "F ->FFF[-F]F[+F]F[-F]"};
            }
            else {
                growAngle = 8;
                
                rules = {
                    "0.33 -> F ->FFF[-[++FL]---FL][++[--F]++FL]",
                    "0.33 -> F ->FFF[-[++FL]---FL][++[--F]L]",
                    "0.33 -> F ->FFF[-[++FL]--L-FL][--FL]"
                };
            }
            break;
        case MANUKA:
            
            break;
        case HARAKEKE:
            
            break;
        case TAWHAI:
            break;
        case KOHUHU:
            g = g*0.5;
            break;
        case KAIKAWAKA:
            break;
            
        default:
            break;
    }
    
        if ((currentHeight >= maxGrowLength && growLength > 0)) {
        // stop growing, this plant is at max or min height
        

    } else {
        growLength+=g;
        currentHeight=growLength;
    }
    
    checkGrowLevel();
    
}

void Plant::updateStatus() {
    
    status +=1;
    
    if (status == 1 ) {
        // z  = -100;
        
    }
    if (status == 2) {
        //   z  = -200;
    }
    
  //  cout << "update status " << status << endl;
    
    //   if (status >= 4) {
    //      status = 4; //
    //   }
    
    somethingChanged = true;
    
}

void Plant::setStatus(int s) {
    status = s;
}

int Plant::getStatus() {
    return status;
}

void Plant::setDestination(int dx, int dy, float dz) {
    destX = dx;
    destY = dy;
    destZ = dz;
    movingToDest=true;
}

void Plant::setPosition(float newX, float newY) {
    
  //  cout << "new position being set" << newX << endl;
    
    x = newX;
    y = newY;
}

void Plant::setYPosition(float newY) {
    
    y = newY;
}

ofVec2f Plant::getPos() {
    return ofVec2f(x,y);
}


PlantType Plant::getPlantType() {
    return plantType;
}

int Plant::getAge() {
    return age;
}

void Plant::killMe() {
    
    
    
    
}
