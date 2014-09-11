#include "ofApp.h"
//1500 seems ok
#define CELLS 500


//--------------------------------------------------------------
void ofApp::setup(){
        ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    
    voroStartPoints.clear();
    for (int i= 0; i < CELLS; i++) {
        ofVec2f    tPoint = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        voroStartPoints.push_back(tPoint);
    }
    
    
    terrainGenerator.start(voroStartPoints,2,3,30);
    
   
    
    
   }



//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor::fromHsb(150, 55, 60));
  //  ofBackground(ofColor::deepSkyBlue);
    
    //tempMesh.draw();
    
    
    
    
    
    for (int i = 0; i < terrainGenerator.cellPoints.size(); i++) {
       terrainGenerator.cellPoints[i].drawCellMesh();
        
        ofSetColor(255,255, 255,40);
        
        //cellPoints[i].drawCellPoint();
        ofSetColor(200, 200, 200,50);
        //cellPoints[i].drawOwnVertex();
        
    }
    
    
    
    //cellPoints[counter%cellPoints.size()].drawOwnVertex();
    
    // cellPoints[counter%cellPoints.size()].drawNeighbours();
    
    
    
    ofPushStyle();
    ofSetColor(ofColor::fromHsb(132, 200, 200,50));
    
    ofSetLineWidth(4);
    
    
    for (int i = 0; i < terrainGenerator.rivers.size(); i++) {
        terrainGenerator.rivers[i].draw();
    }
    ofPopStyle();
    
    
    for (int i = 0; i < terrainGenerator.coastLines.size(); i++) {
        ofSetColor(ofColor::orangeRed );
        terrainGenerator.coastLines[i].draw();
    }
    //voroMesh.drawWireframe();
    ofSetColor(255);
    // ofDrawBitmapString( "vertices "+ ofToString(cellPoints[counter%cellPoints.size()].ownVertex.size())+ "  id:"+ofToString(cellPoints[counter%cellPoints.size()].iD), 40, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    if (key == 's' ){
        ofImage temp;
        temp.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        temp.resize(ofGetWidth()/2, ofGetHeight()/2);
        temp.saveImage( ofToString( ofGetElapsedTimef()+ofRandom(1000))+ ".png");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}








