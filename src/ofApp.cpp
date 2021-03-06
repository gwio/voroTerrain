#include "ofApp.h"
//1500 seems ok
#define CELLS 1500


//--------------------------------------------------------------
void ofApp::setup(){
    //ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    
    voroStartPoints.clear();
    for (int i= 0; i < CELLS; i++) {
        ofVec2f    tPoint = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        voroStartPoints.push_back(tPoint);
    }
    
    
    terrainGenerator.start(voroStartPoints,3,4,50);
    
    switchWire = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor::deepSkyBlue);

    
    for (int i = 0; i < terrainGenerator.cellPoints.size(); i++) {
        if (switchWire) {
            terrainGenerator.cellPoints[i].drawWire();
        } else {
            terrainGenerator.cellPoints[i].drawCellMesh();
        }
    }
    
    
    ofPushStyle();
    ofSetColor(ofColor::fromHsb(132, 200, 200,50));
    ofSetLineWidth(4);
    for (int i = 0; i < terrainGenerator.rivers.size(); i++) {
        terrainGenerator.rivers[i].draw();
    }
    ofPopStyle();
    
    
    
    for (int i = 0; i < terrainGenerator.coastLines.size(); i++) {
        ofSetColor(ofColor::white);
        ofSetLineWidth(1);
        terrainGenerator.coastLines[i].draw();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == 's' ){
        ofImage temp;
        temp.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        temp.resize(ofGetWidth(), ofGetHeight());
        temp.saveImage( ofToString( ofGetElapsedTimef()+ofRandom(1000))+ ".png");
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
        ofVec2f    tPoint = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        voroStartPoints.push_back(tPoint);
    }
    terrainGenerator.start(voroStartPoints,3,4,50);
    
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








