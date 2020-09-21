#pragma once

#include "ofMain.h"
#include "ofxTwitter.h"
#include "plantSection.h"
#include "PlantManager.hpp"
#include "fireFlies.h"

// weAreMovingEndTIme back to 300000
// plant timer to 5000 and 15000
// Check x and y destination for plant
// Move back amount
// Growth increase
// Change moving back speeds

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
   /// Twitter functions
    void onStatus(const ofxTwitter::Status& status);
    void onError(const ofxTwitter::Error& error);
    void onException(const std::exception& exception);
    void onMessage(const ofJson& json);
    
    int prevGrowLevel=0;
    
    // PLANT things
    PlantManager plantManager = *new PlantManager();
    

    
    
    //// Plant manager functions
   // void checkNewTweets();
    void givePlantASpot(int plantI);
    void updatePlantMessage();
    bool checksIfMessageHasToWait = false;
  //  bool newTweetsIncoming = false;
    bool weAreMoving = false; // Jenna this is the shift for the row from front to back
    int weAreMovingEndTIme = 300000;
    int weAreMovingTime;
    ////////// Twitter stuff ///////////
    ofxTwitter::SearchClient client;
    vector <string> alltweets;
    ofxParagraph paragraph, name;
    //uint64_t count = 0;
    uint64_t countMissed = 0;
    int totalTweet;
    int fontSize = 20;
    int fontNameSize = 20;
    //string searchString = "#taupowinterfestival filter:safe";
    string searchString = "#taupowinterfestival";

  //  string searchString = "kowhai OR horoeka OR manuka OR harakeke OR tawhai OR kohuhu OR kaikawaka filter:safe";

    // The 5 plant variables
    const int plantSlotsNum = 7;
  
    
    // OK So this is acutally relative to each plant. So Rabbit will always be first in the array but have different location
   // std::vector<std::string> plantNames = {"carrot", "internet", "trump", "america", "help", "new", "goat"};
    
    std::vector<std::string> plantNames = {"kowhai", "horoeka", "manuka", "harakeke", "tawhai", "kohuhu", "kaikawaka"};

    std::vector<std::string> realPlantNames = {"Kowhai", "Horoeka", "Manuka", "Harakeke", "Tawhai", "Kohuhu", "Kaikawaka"};
    plantSection ourPlantSection[7];
    
    /// These relate to the position of the plant sections. The X position will always be the same but the y will change depending on what is the current state.
    int plantPotPosX[7];
    bool plantPosTaken[7] = {false, false, false, false, false, false, false};
    bool frontFourFront = true;
    bool moveThoseFireFlies = false;
    int plantSectionDifference;
    int frontRowY;
    int backRowY;
    int fireFlyNum;
    
    
    // Gradient
    void setGradient(int x, int y, float w, float h, ofColor c1, ofColor c2, int axis);
    ofImage bgImage;
    ofColor a1, a2, b1, b2;
    int Y_AXIS = 1;
    
    ofImage grass;
    
    vector <fireFly> arrayFireFlies; // ArrayList poop; // Star Particles
    ofFbo bgFBO;

};
