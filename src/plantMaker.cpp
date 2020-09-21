//
//  plantMaker.cpp
//  TheSocialGarden0_1
//
//  Created by Matt Martin on 9/07/17.
//
//

#include "ofApp.h"
//--------------------------------------------------------------

void ofApp::updatePlantMessage() {
    
    for(int i = 0; i < plantNames.size(); i++){
        
        if(weAreMovingEndTIme < ofGetElapsedTimeMillis() - weAreMovingTime){
            weAreMoving = true;
            
            // This means we are only moving the ones that have a spot and are in waiting room.
            // We do not wait for all of them. They move by themselves
            if(ourPlantSection[i].localPlantState == waitingRoom && ourPlantSection[i].doIHaveASpot == true){
                
                if(ourPlantSection[i].iGrowHere.y > backRowY && ourPlantSection[i].iGrowHere.y < frontRowY -plantSectionDifference +5){ // If we have reached destination
                    
                    ourPlantSection[i].willINeedToMove = false; // We dont need to move, we have made it
                    ourPlantSection[i].doIHaveASpot = true;
                    ourPlantSection[i].iGrowHere.y = backRowY;
                    plantPosTaken[ourPlantSection[i].thisIsMySpot] = true;
                }
                else if(ourPlantSection[i].iGrowHere.y <= backRowY - plantSectionDifference){ // meaning the 4 row are at back. We want the even array #s
                    
                    ourPlantSection[i].willINeedToMove = false; // We dont need to move, we have made it
                    ourPlantSection[i].doIHaveASpot = false;
                    plantPosTaken[ourPlantSection[i].thisIsMySpot] = false;
                    plantManager.updateOldPlants(i);
                }
                else if(ourPlantSection[i].willINeedToMove){
                    ourPlantSection[i].iGrowHere.y -= 1;
                    //tell plant manager to move TYPE of plant back (only 1 of status 0), to THIS Y position
                    plantManager.movePlantsBack(i, ourPlantSection[i].iGrowHere.y);
                }
            }
        }
        
        
        
        
        switch ( ourPlantSection[i].localPlantState ) {
            case waitingRoom:
                
                // We make sure there is no empty message and that we have been permitted to move forward
                if(!ourPlantSection[i].plantTypeTweet.empty() &&
                   !weAreMoving){
                    
                    // We check that this is the next message to be sent away. We get the same historic entry of each array to check that they are the next to go. Both will be erased by the end of the transition. All other messages will have to wait until this one has reached ParticlesBursting
                    if(alltweets[alltweets.size()-1] == ourPlantSection[i].plantTypeTweet[ourPlantSection[i].plantTypeTweet.size()-1] ){
                        // Yay we are next in line!
                        
                        givePlantASpot(i); // Give plant a space on the 7 spots
                        
                        // Add in variables starting points, even if they are the same as last time.
                        // PLANT NAME IS ALWAYS SAME AS ORDER OF ARRAY!!!!!!! ONLY POSITION CHANGES
                        ourPlantSection[i].wordsInGroundPos.set(plantPotPosX[ourPlantSection[i].thisIsMySpot], ofGetHeight());
                        
                        ourPlantSection[i].wordsInGroundTarget = ourPlantSection[i].iGrowHere;
                        ourPlantSection[i].messagePositionX = ofGetWidth()/2;
                        ourPlantSection[i].messagePositionY = 10 + ourPlantSection[i].messageHeight;
                        
                        ourPlantSection[i].willINeedToMove = true; // This means we will need to move this plant upwards when the rows change
                        ourPlantSection[i].localPlantState = wordsInDirt; // Lets move on
                        
                        // We make a firefly move to the plant
                        fireFlyNum = ofRandom(arrayFireFlies.size() - 20, arrayFireFlies.size()-1);
                        
                        arrayFireFlies[fireFlyNum].target = ourPlantSection[i].iGrowHere;
                        arrayFireFlies[fireFlyNum].maxSpeed = ofRandom(6.5, 8.0);
                        arrayFireFlies[fireFlyNum].maxForce = arrayFireFlies[fireFlyNum].maxSpeed*0.030;
                        moveThoseFireFlies = true;
                    }
                }
                break;
            case wordsInDirt:
                if(!moveThoseFireFlies){
                    moveThoseFireFlies = false;
                    fireFlyNum = 0;

                    plantManager.feedPlants(ourPlantSection[i].whichPlantAreWeNum);
                    
                    ourPlantSection[i].localPlantState = ParticlesBursting;
                    ourPlantSection[i].thisPlantTweet = ourPlantSection[i].plantTypeTweet[ourPlantSection[i].plantTypeTweet.size()-1]; // This is where we allocate the tweet message
                    ourPlantSection[i].nextWord();
                    totalTweet --; // This makes sure can see new tweets
                }
                break;
            case ParticlesBursting:
                ourPlantSection[i].particleUpdate();
                if(ourPlantSection[i].arrayDustParticles.size() <= 0){
                    ourPlantSection[i].localPlantState = WordsStayUp;
                    ourPlantSection[i].timerStart = ofGetElapsedTimeMillis();
                    alltweets.pop_back();// ERASE TWEET
                    ourPlantSection[i].plantTypeTweet.pop_back();
                    alltweets.size()>=1?ourPlantSection[i].timerEnd=5000:ourPlantSection[i].timerEnd=15000;
                }
                
                break;
            case WordsStayUp:
                ourPlantSection[i].wordsUpdate();
                if(ourPlantSection[i].plantWordAlpha <= 0){
                    
                    ourPlantSection[i].localPlantState = waitingRoom;
                    ourPlantSection[i].plantWordAlpha = 195;
                }
                // cout << "WE MADE IT: " << i << endl;
                break;
            default:
                cout<<"Error, bad input, quitting\n";
                break;
        }
    }
}

void ofApp::givePlantASpot(int plantI){
    // If we dont have a spot then find us one.
    while(!ourPlantSection[plantI].doIHaveASpot){ // We check the spots until one is empty, may need to change this
        int randomPos;
        randomPos = ofRandom(0,7);
        if(!plantPosTaken[randomPos]){
            plantPosTaken[randomPos] = true;
            ourPlantSection[plantI].doIHaveASpot = true; // Yay we can take this spot
            ourPlantSection[plantI].thisIsMySpot = randomPos; // Tells the section what spot it has
            ourPlantSection[plantI].iGrowHere.set(plantPotPosX[ourPlantSection[plantI].thisIsMySpot], frontRowY);
            plantManager.createNewPlant(ourPlantSection[plantI].whichPlantAreWeNum, ourPlantSection[plantI].iGrowHere.x, ourPlantSection[plantI].iGrowHere.y);
        }
    }
}
