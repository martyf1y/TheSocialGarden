//
//  PlantManager.cpp
//  plantStructure
//
//  Created by JLG on 8/07/17.
//
//

#include "PlantManager.hpp"

// retrieve array of lines

//only the first 2 rows of plants will get the most interactivity
// otherwise plant is muted and not growing much
// the longer they are alive, the less they can grow

// work out growth ranges / averages
// length
// flowers - number, - size, colour
// leaves
// mature state of tree === dead brown colour


PlantManager::PlantManager(){
    
    
    // ALLOCATE FBO
    //plantFbo.allocate( ofGetWidth(), ofGetHeight() );
    
    // secondplantFbo.allocate(ofGetWidth(),ofGetHeight());
    plantImage.load("myDeadTree.png");
    plantFbo.allocate(ofGetWidth(),570);

     plantFbo.begin();
      ofClear(0,0,0,0);
    plantImage.draw(0,0);
      plantFbo.end();
    secondplantFbo.allocate(ofGetWidth(),570);
    secondplantFbo.begin();
    ofClear(0,0,0,0);
    secondplantFbo.end();
    secondplantFbo = plantFbo;
    //      ofPixels pixels;
    //  plantFbo.readToPixels(pixels);
    
    // set up plant array - do not touch.
    for (int i=0; i<numDifferentPlants; i++) {
        vector<Plant> plant;
        arrayOfPlants.push_back(plant);
    }
    
    
}

void PlantManager::update(int level, float length, float angle) {
    
    // update all plants in different arrays
    for (int i=0; i<arrayOfPlants.size(); i++) {
        
        for (int ii=0; ii < arrayOfPlants[i].size(); ii++) {
            arrayOfPlants[i][ii].update(level, length, angle);
            
            float myx = arrayOfPlants[i][ii].getPos().x;
            float myy = arrayOfPlants[i][ii].getPos().y;
            
            
          //  cout << "Plant type: " << arrayOfPlants[i][ii].getPlantType() << ". I am status " << arrayOfPlants[i][ii].getStatus() << " and my X Y is: " << myx << " " << myy << endl;
            
        }
    }
    
    // 16 JULY JEN * * * * * * * * * * * * * * * * *
    
    //CHECK if status 3, "KILLED - waiting to be saved (to image)"
    for (int i=0; i<arrayOfPlants.size(); i++) {
        for (int ii=0; ii < arrayOfPlants[i].size(); ii++) {
            
            if (arrayOfPlants[i][ii].getStatus() == 3) {
                
                savePlant(arrayOfPlants[i][ii]);
                
                //set this plant to status 4,"SUPER DEAD - being taken out of array"
                arrayOfPlants[i][ii].setStatus(4);
                
                //get the fuck out of here
                break;
                
            }
        }
    }
}

void PlantManager::feedPlants(int typeNum) {
    
    // 15 JULY JEN * * * * * * * * * * * * * * * * *
    
    PlantType type = PlantType (typeNum);
    Boolean plantFoundinArray = false;
    
    // Only feed particular plant type that is coming in
    for (int i=0; i<arrayOfPlants.size(); i++) {
        if (arrayOfPlants[i].size() != 0) {
            
            if (arrayOfPlants[i][0].getPlantType() == type) {
                //We have found the right array of plants, now change them:
                plantFoundinArray = true;
                for (int ii=0; ii < arrayOfPlants[i].size(); ii++) {
                    
                    //  cout << "grow plant " << ii << endl;
                    if (arrayOfPlants[i][ii].getStatus() < 3) {
                        arrayOfPlants[i][ii].growMyself(0.5);
                    }
                }
                break;
            }
        }
    }
    
    if (!plantFoundinArray) {
        cout << "Plant type not stored yet" << endl;
        
        // but if there is a slot available .. I can create one?
    }
}

void PlantManager::display(float zAxis) {
    
    
    //DRAW DEAD PLANT
    
    ofSetColor(255, 255, 255, 255);
    plantFbo.draw(0,0);
    
    
    //draw to this vbo instead of each plant drawing itself
    ofVbo vbo;
    
    //DISPLAY PLANTS
    
    // display all plants in different arrays
    for (int i=0; i<arrayOfPlants.size(); i++) {
        
        for (int ii=0; ii < arrayOfPlants[i].size(); ii++) {
            arrayOfPlants[i][ii].display(vbo);
        }
        
    }
    
    //then draw vbo
    vbo.draw(GL_LINES,0,1);
}


void PlantManager::setColourScheme(int scheme) {
    
    if (scheme == 1) {
        c1 = ofColor(8,25,89);
        c2 = ofColor(3,99,148);
        c3 = ofColor(6,150,119);
        
    } else {
        c1 = ofColor(115,156,204);
        c2 = ofColor(34,87,100);
        c3 = ofColor(155,195,98);
    }
}

void PlantManager::createNewPlant(int type, int plantX, int plantY) {
    
    
    PlantType i = PlantType(type);
    
    // cout << "YOu have requested a new " << i << endl;
    
    //type = MANUKA; //for testing
    
    // create new plant in a slot number
    
    /*
     KOWHAI
     HOROEKA
     MANUKA
     HARAKEKE
     TAWHAI
     KOHUHU
     KAIKAWAKA
     */
    
    Plant *p; // new plant object
    
    switch( type )
    {
        case KOWHAI:
            p = new Plant(arrayOfPlants[0].size(),ageOfPlants,KOWHAI,plantX,plantY);
            arrayOfPlants[0].push_back(*p);
            break;
            
        case HOROEKA:
            p = new Plant(arrayOfPlants[1].size(),ageOfPlants,HOROEKA,plantX,plantY);
            arrayOfPlants[1].push_back(*p);
            
            break;
            
        case MANUKA:
            p = new Plant(arrayOfPlants[2].size(),ageOfPlants,MANUKA,plantX,plantY);
            arrayOfPlants[2].push_back(*p);
            
            break;
        case HARAKEKE:
            p = new Plant(arrayOfPlants[3].size(),ageOfPlants,HARAKEKE,plantX,plantY);
            arrayOfPlants[3].push_back(*p);
            
            break;
        case TAWHAI:
            p = new Plant(arrayOfPlants[4].size(),ageOfPlants,TAWHAI,plantX,plantY);
            arrayOfPlants[4].push_back(*p);
            
            break;
        case KOHUHU:
            p = new Plant(arrayOfPlants[5].size(),ageOfPlants,KOHUHU,plantX,plantY);
            arrayOfPlants[5].push_back(*p);
            
            break;
        case KAIKAWAKA:
            p = new Plant(arrayOfPlants[6].size(),ageOfPlants,KAIKAWAKA,plantX,plantY);
            arrayOfPlants[6].push_back(*p);
            
            break;
            
        default:
            cout << "random plant generation falling out" << endl;
            break;
    }
    
    //add counter so we know how old plants are, so we can remove them in order
    ageOfPlants++;
    
}

void PlantManager::movePlantsBack(int typeOfPlant, int newY) {
    
    //move a plant from the front to the back
    
    //  for (int i=0; i<arrayOfPlants.size(); i++) {
    
    //if there is something in the array....
    if( arrayOfPlants[typeOfPlant].size() != 0) {
        //set y position to incoming
        // set the newest ...
        
        arrayOfPlants[typeOfPlant][arrayOfPlants[typeOfPlant].size()-1].setYPosition(newY);
    }
    //  }
    
}

void PlantManager::updateOldPlants(int typeOfPlant) {
    
    
    
    // ARBOR AGED CARE
    
    //if there is something in the array....
    if( arrayOfPlants[typeOfPlant].size() != 0) {
        
        //set this newest plant to the oldest status
        arrayOfPlants[typeOfPlant][arrayOfPlants[typeOfPlant].size()-1].setStatus(2);
        
        // set dest Y
        int destY = setPlantYDestination();
        //set dest X
        int margin = 50;
        int destX = int(ofRandom(margin,ofGetWidth()-margin));
        float destZ = ofDist(arrayOfPlants[typeOfPlant][arrayOfPlants[typeOfPlant].size()-1].getPos().x, arrayOfPlants[typeOfPlant][arrayOfPlants[typeOfPlant].size()-1].getPos().y, destX, destY);
        destZ *=0.7;
       // destX = destZ
      //  cout << "y " << destY << endl;
      //  cout << "x " << destX << endl;
        
        arrayOfPlants[typeOfPlant][arrayOfPlants[typeOfPlant].size()-1].setDestination(destX,destY, destZ);
    }
    
    
    // KILL ORDER - Remove dead plants if necessary
    
    for (int i=0; i<arrayOfPlants.size(); i++) {
        for (int ii=0; ii < arrayOfPlants[i].size(); ii++) {
            
            
            if (arrayOfPlants[i][ii].getStatus() == 4 ) { // DEAD ZONE
                
                //kill order
                removePlant();
                
            }
        }
    }
    
}

void PlantManager::savePlant(Plant& thisPlant) {
    
    
 //   cout << "getting to killPLANT" << endl;
    
    ofVbo localvbo;
    
    //kill me now
    
    plantFbo.allocate(ofGetWidth(),570);
    plantFbo.begin();
    ofClear(0,0,0,0);
    ofSetColor(255, 255, 255);
    
    secondplantFbo.draw(0,0);    // draw what we had previously
    thisPlant.display(localvbo);
    localvbo.draw(GL_LINES,0,1); //draw the plant lines and things
    
    plantFbo.end();
    
    ofPixels pixels;
    plantFbo.readToPixels(pixels);
    
    secondplantFbo = plantFbo; // set new image based on what we just wrote to pixels
    
    plantImage = pixels;
    ofSaveImage(pixels,"myDeadTree.png"); // save so we can see what's going on.
    ofSaveImage(pixels,"myDeadTree" + ofGetTimestampString() + ".png"); // save so we can see what's going on.

    
}

void PlantManager::removePlant() {
    
    std::vector<Plant>::iterator it;
    
    for (int i=0; i<arrayOfPlants.size(); i++) {
        
        for (it = arrayOfPlants[i].begin(); it != arrayOfPlants[i].end(); /* DONT increment here*/) {
            int status = (*it).getStatus();
            if (status == 4) {
                // store the return value from erase!!
                it = arrayOfPlants[i].erase(it);
            }
            else
            {
                // increment here rather than in the for loop incrementer
                it++;
            }
        }
    }
}

int PlantManager::setPlantYDestination() {
    
    
  //  cout << ofGetDay() << endl;
  //  cout << ofGetHours() << endl;
  //  cout << ofGetMinutes() << endl;
    
    // 7 days (sun, mon, tues, wed, thurs, fri, sat)
    // 5 hours (5-6pm, 6-7pm, 7-8pm, 8-9pm, 9-10pm)
    // 60 minutes in an hour
    
    // Grand total to divide by: 2100 segments
    
    int minimumY = 250; //ofGetHeight()*0.3;
    int maximumY = 550; //ofGetHeight()*0.7;
    
    //  cout << " minY  " << minimumY << endl;
    //  cout << " maxY  " << maximumY << endl;
    
    float divisionSize = (maximumY - minimumY);
    // cout << " division size " << divisionSize << endl;
    //set Y destination
    
    // DAY
    float daySize = divisionSize/7;
    //cout << "day size " << daySize << endl;
    int day = ofMap(ofGetDay(),16,22,1,7);  // map days 16th to 22nd and make into numbers 1-7
    //int day = ofMap(ofGetMouseX(),0,ofGetWidth(),1,7);
    float dayY = minimumY + day*daySize;
    // cout << "This is the DAY Y " << dayY << endl;
    
    // HOUR
    float hourSize = daySize/5;
    int hour = ofMap(ofGetHours(),17,21,1,5); // map hours 17:00 to 21:59 to numbers 1-5
    //int hour = ofMap(ofGetMouseY(),0,ofGetHeight(),1,5);
    
    float hourY = dayY + hour*hourSize;
    // cout << "This is the HOUR Y " << hourY << endl;
    
    // MINUTE
    float minSize = hourSize/60;
    int min = ofGetMinutes(); // mins 0 to 59
    float minY = hourY + min*minSize;
    // cout << "This is the MIN Y " << minY << endl;
    
    
    int dest = int(minY);
    //ofSetColor(0,0,255);
   // ofDrawEllipse(ofGetWidth()/2,dest,30,30);
    
    return dest;
}
