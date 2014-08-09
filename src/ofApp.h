#pragma once

#include "ofMain.h"
#include "ofxVoronoi.h"
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
    
    
    ofxVoronoi voronoi;
    
    vector<CellPoint> cellPoints;
    vector<VertexPoint> vertexPoints;
    
    int counter;
    
    bool checkCorner(ofVec2f);
    bool checkRand(ofVec2f);

    vector<ofVec2f> midPoints;
};
