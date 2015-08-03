#include "ofApp.h"
//1500 seems ok
#define CELLS 500
#define mapSquareSize 1000


//--------------------------------------------------------------
void ofApp::setup(){
    //ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    
    voroStartPoints.clear();
    for (int i= 0; i < CELLS; i++) {
        ofVec2f    tPoint = ofVec2f(ofRandom(mapSquareSize), ofRandom(mapSquareSize) );
        voroStartPoints.push_back(tPoint);
    }
    
    
    terrainGenerator.start(mapSquareSize, mapSquareSize, voroStartPoints,3,4,50);
    
    
    switchWire = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor::deepSkyBlue);
    if (!switchWire) {
        
        terrainGenerator.terrainMap.draw(0,0);
        
    }
    
    if (switchWire) {
        for (int i = 0; i < terrainGenerator.cellPoints.size(); i++) {
            terrainGenerator.cellPoints[i].drawCellMesh();
        }
        ofPushStyle();
        ofSetColor(255, 255, 255);
        for (int i = 0; i < terrainGenerator.rivers.size(); i++) {
            terrainGenerator.rivers.at(i).draw();
        }
        ofSetColor(255, 0, 0);
        for (int i = 0; i < terrainGenerator.coastLines.size(); i++) {
            terrainGenerator.coastLines.at(i).draw();
        }
        ofPopStyle();
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == 's' ){
        
        ofSaveImage(pix, ofToString( ofGetElapsedTimef()+ofRandom(1000))+ ".png");
    }
    
    if (key == '1') {
        switchWire = !switchWire;
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
    
    voroStartPoints.clear();
    for (int i= 0; i < CELLS; i++) {
        ofVec2f    tPoint = ofVec2f(ofRandom(mapSquareSize), ofRandom(mapSquareSize));
        voroStartPoints.push_back(tPoint);
    }
    terrainGenerator.start(mapSquareSize, mapSquareSize, voroStartPoints,3,4,50);
    
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








