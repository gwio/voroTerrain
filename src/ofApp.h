#pragma once

#include "ofMain.h"
#include "ofxVoronoi2D.h"
#include "voronoiData.h"

struct cellDist {
    float distance;
    int iD;
    ofVec2f midPoint;
    
    bool operator < (const cellDist& str) const {
        return (distance < str.distance);
    }
};

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
    
    
    ofxVoronoi2D voronoi;
    ofRectangle voroRect;
    vector<ofVec2f> voroStartPoints;

    
    vector<CellPoint> cellPoints;
    vector<VertexPoint> vertexPoints;
    vector<VoroEdge> edges;
    vector<ofVec2f> midPoints;

    
    int counter;
    
    ofMesh voroMesh;
    
    bool checkRand(ofVec2f);
    
    void generateVoro(vector<ofVec2f>*);

};
