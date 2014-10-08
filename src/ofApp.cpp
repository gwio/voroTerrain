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
    
    //  terrainGenerator.start(voroStartPoints,0,0,30);
    
    
    
    switchWire = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
      ofBackground(ofColor::deepSkyBlue);
    
  //  ofBackground(0, 0, 0,0);
    //tempMesh.draw();
    
    
    
    
 /*
    for (int i = 0; i < terrainGenerator.cellPoints.size(); i++) {
        
        if (switchWire) {
            terrainGenerator.cellPoints[i].drawWire();
            
        } else {
            terrainGenerator.cellPoints[i].drawCellMesh();
        }
        
    }
    */
    
    
    
    ofPushStyle();
    ofSetColor(ofColor::fromHsb(132, 200, 200,50));
    
    ofSetLineWidth(4);
    
    
    for (int i = 0; i < terrainGenerator.rivers.size(); i++) {
        terrainGenerator.rivers[i].draw();
    }
    ofPopStyle();
    
    
    
   /*
    for (int i = 0; i < terrainGenerator.edges.size(); i++) {
        if (terrainGenerator.edges.at(i).isCoast) {
            ofSetColor(ofColor::mediumSpringGreen );
            
            terrainGenerator.edges.at(i).drawEdge();
        }
    }
    
    for (int i = 0; i < terrainGenerator.coastLines.size(); i++) {
        ofSetColor(ofColor::orangeRed );
        ofSetColor(ofColor::black );
        ofSetLineWidth(2);
        terrainGenerator.coastLines[i].draw();
    }
    */
    
    terrainGenerator.terrainMap.draw(0, 0);
    
    terrainGenerator.rockMap.draw(0, 0);
    terrainGenerator.treeMap.draw(0, 0);

    
    /*
     for (int i = 0; i < terrainGenerator.vertexPoints.size(); i++) {
     if (terrainGenerator.vertexPoints.at(i).coastEdges == 2) {
     ofSetColor(ofColor(0, 0, 255,50));
     } else if (terrainGenerator.vertexPoints.at(i).coastEdges < 2)  {
     ofSetColor(ofColor(255, 0, 0,50));
     }
     ofEllipse(terrainGenerator.vertexPoints.at(i).point, 6, 6);
     }
     //
     //voroMesh.drawWireframe();
     ofSetColor(255,50);
     // ofDrawBitmapString( "vertices "+ ofToString(cellPoints[counter%cellPoints.size()].ownVertex.size())+ "  id:"+ofToString(cellPoints[counter%cellPoints.size()].iD), 40, 40);
     
     */
    
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








