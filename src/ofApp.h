#pragma once

#include "ofMain.h"
#include "terrainGen.h"

//#include "ofxVoronoi2D.h"
//#include "voronoiData.h"



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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    
    TerrainGen terrainGenerator;
    vector<ofVec2f> voroStartPoints;
    
    bool switchWire;
    
    ofFbo screen;
    ofPixels pix;
    ofImage wholeImg;

};
