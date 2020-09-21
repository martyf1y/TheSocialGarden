#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofHideCursor();

    // Easily register for all search events.
    client.registerSearchEvents(this);
    client.setCredentialsFromFile("credentials.json");
    // Set the polling interval for 6 seconds.
    client.setPollingInterval(6000);
    ofxTwitter::SearchQuery query(searchString);
    query.setResultType(ofx::Twitter::SearchQuery::ResultType::RECENT);
    client.search(query);
    
    paragraph.setFont("kenyancoffeerg.ttf", fontSize);
    name.setFont("MaidenOrange.ttf", fontNameSize);
    grass.load("grassfield.jpeg");
    
    // Gradient things
    a1 = ofColor(0, 26, 38);
    a2 = ofColor(0, 26, 38);
    b1 = ofColor(35,5,12);
    b2 = ofColor(0, 65, 30);
    
    bgFBO.allocate(ofGetWidth(), ofGetHeight());
    bgFBO.begin();
    setGradient(0, 200, ofGetWidth(), ofGetHeight(), b1, b2, Y_AXIS);
    ofSetColor(255,255,255, 40);
    grass.draw(0, 0,ofGetWidth(),ofGetHeight());
    setGradient(0, 0, ofGetWidth(), 230, a1, a2, Y_AXIS);
    bgFBO.end();
    
    for(int i; i < plantNames.size(); i++){
        ourPlantSection[i] = plantSection();
        ourPlantSection[i].plantParagraph = paragraph;
        ourPlantSection[i].localPlantName = name; // This is paragraph object settings
        ourPlantSection[i].whichPlantAreWe = realPlantNames[i];
        ourPlantSection[i].whichPlantAreWeNum = i;
        ourPlantSection[i].messageFontSize = fontSize;
        ourPlantSection[i].nameFontSize = fontNameSize;
        ourPlantSection[i].willINeedToMove = false;
    }
    
    plantPotPosX[0] = ofGetWidth()/2-(ofGetWidth()/7)*3 + 20;
    plantPotPosX[1] = ofGetWidth()/2-(ofGetWidth()/9)*2;
    plantPotPosX[2] = ofGetWidth()/2-ofGetWidth()/9;
    plantPotPosX[3] = ofGetWidth()/2;
    plantPotPosX[4] = ofGetWidth()/2+ofGetWidth()/9;
    plantPotPosX[5] = ofGetWidth()/2+(ofGetWidth()/9)*2;
    plantPotPosX[6] = ofGetWidth()/2+(ofGetWidth()/7)*3 - 20;
    
    plantSectionDifference = 50;
    frontRowY = ofGetHeight();
    backRowY = ofGetHeight() - plantSectionDifference;
    weAreMovingTime = ofGetElapsedTimeMillis();
    
    //Fireflies
   
    for (int i=0; i<45; i++) {
        fireFly P = fireFly(2);
        arrayFireFlies.push_back(P);
    }
    for (int i=0; i<8; i++) {
        fireFly P = fireFly(3);
        arrayFireFlies.push_back(P);
    }
    for (int i=0; i<20; i++) {
        fireFly P = fireFly(ofRandom(4,5));
        arrayFireFlies.push_back(P);
    }
    
   // ofLogNotice("NEW TWEET #") << status.text();
    alltweets.push_back("#taupowinterfestival TAWHAI First family outing at the Festival - 11 days old and loving it!");
    ourPlantSection[4].plantTypeTweet.push_back("#taupowinterfestival TAWHAI First family outing at the Festival - 11 days old and loving it!");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // This checks that the plants have finished moving
    updatePlantMessage();

    // Do a check here, If all plants have stopped messaging (check their enum status) then move their Y coordinates and reset the back 3 plants to no place. If they have messages to do then put them into waiting room straight away
    if(weAreMoving &&
       ourPlantSection[0].willINeedToMove == false && //
       ourPlantSection[1].willINeedToMove == false && //
       ourPlantSection[2].willINeedToMove == false && //
       ourPlantSection[3].willINeedToMove == false &&
       ourPlantSection[4].willINeedToMove == false &&
       ourPlantSection[5].willINeedToMove == false &&
       ourPlantSection[6].willINeedToMove == false){        
        
        weAreMoving = false; // No more moving plants
        weAreMovingTime = ofGetElapsedTimeMillis();
        frontFourFront = !frontFourFront;
        
        for(int i = 0; i < plantNames.size(); i++){
            if(ourPlantSection[i].doIHaveASpot){
                ourPlantSection[i].willINeedToMove = true;
            }
        }
    }
    
    plantManager.update(3, 3, 3) ;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    
    bgFBO.draw(0,0);
    ofFill();
   
    // These are the stars, not the word dust!!
    for (int i=0; i<arrayFireFlies.size()-20; i++) {
        arrayFireFlies[i].display();
    }
   // plantManager.display(0);

    for (int i=arrayFireFlies.size()-20; i<arrayFireFlies.size(); i++) {
       // arrayFireFlies[i].display();
        if (i != fireFlyNum) {
            arrayFireFlies[i].move();
        }
    }
    if(moveThoseFireFlies){
        moveThoseFireFlies = arrayFireFlies[fireFlyNum].toPlant();
    }

    
    for(int i = 0; i < plantNames.size(); i++){
       // ourPlantSection[i].draw();
    }
    
   // ofDrawBitmapString(ofGetFrameRate(), 10, 10);
/*
    for(int i = 0; i < plantNames.size(); i++){
    ofDrawBitmapString(i, plantPotPosX[i], ofGetHeight()-10);
    ofDrawEllipse(plantPotPosX[i], ofGetHeight()-10, 20, 20);
    name.setText("Kaikawaka");
    name.setAlignment(ofxParagraph::ALIGN_CENTER);
    name.draw(plantPotPosX[i] - name.getWidth()/2,ofGetHeight()-fontNameSize-50);
    }
    */
    
    ofSaveScreen("gif/funtimes" + ofToString(ofGetElapsedTimeMillis()) + ".tga");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // plantManager.createNewPlant();
    
    /* if (key == '1') {
     ofSetBackgroundColor(0);
     plantManager.setColourScheme(1);
     }
     if (key == '2') {
     ofSetBackgroundColor(255);
     plantManager.setColourScheme(2);
     }*/
    
    /*
     KOWHAI
     HOROEKA
     MANUKA
     HARAKEKE
     TAWHAI
     KOHUHU
     KAIKAWAKA
     */
    
    if (key == '1') {
        plantManager.feedPlants(KOWHAI);
    }
    if (key == '2') {
        plantManager.feedPlants(HOROEKA);
        
    }
    if (key == '3') {
        plantManager.feedPlants(MANUKA);
        
    }
    if (key == '4') {
        plantManager.feedPlants(HARAKEKE);
        
    }
    if (key == '5') {
        plantManager.feedPlants(TAWHAI);
        
    }
    if (key == '6') {
        plantManager.feedPlants(KOHUHU);
        
    }
    if (key == '7') {
        plantManager.feedPlants(KAIKAWAKA);
        
    }
    
    if (key == 'm') {
     //   plantManager.movePlantsBack(ofGetHeight()- 50 - plantSectionDifference*2);
    }
    if (key == 'n') {
        int rand = int(ofRandom(7));
       // plantManager.createNewPlant(rand);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


void ofApp::onStatus(const ofxTwitter::Status& status){
    
    string checkForWords = status.text(); // Saves us from unwanted tweets with the hashtag
    std::transform(checkForWords.begin(), checkForWords.end(), checkForWords.begin(), ::tolower);
    for(int i = 0; i < plantNames.size(); i++){
        if(checkForWords.find(plantNames[i]) != string::npos){ // Checks that a plant is included
            ofLogNotice("NEW TWEET #") << status.text();
            alltweets.push_back(status.text());
            ourPlantSection[i].plantTypeTweet.push_back(status.text());
            }
        }
    }

void ofApp::onError(const ofxTwitter::Error& error){
    ofLogError("ofApp::onError") << "Error: " << error.code() << " " << error.message();
}
void ofApp::onException(const std::exception& notice){
    ofLogError("ofApp::onException") << "Exception: " << notice.what();
}
void ofApp::onMessage(const ofJson& json){
    // This is the raw message json and is ignored here.
}

void ofApp::setGradient(int x, int y, float w, float h, ofColor c1, ofColor c2, int axis ) {
    if (axis == Y_AXIS) {  // Top to bottom gradient
        for (int i = y; i <= y+h; i++) {
            float inter = ofMap(i, y, y+h, 0, 1);
            ofColor c = c1.lerp(c2, inter);
            ofSetColor(c);
            ofDrawLine(x, i, x+w, i);
        }
    }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}
