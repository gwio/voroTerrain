//
//  terrainGen.h
//  voronoi_test
//
//  Created by Christian Gwiozda on 19.08.14.
//
//

#ifndef __voronoi_test__terrainGen__
#define __voronoi_test__terrainGen__

#include "ofMain.h"
#include "voronoiData.h"
#include "ofxVoronoi2D.h"

struct cellDist {
    float distance;
    int iD;
    ofVec2f midPoint;
    
    bool operator < (const cellDist& str) const {
        return (distance < str.distance);
    }
};

class TerrainGen {
    
public:
    //add int random watercells, int add radnom watercell to coast, int number of rivers
    TerrainGen();

    void start(vector<ofVec2f>,int,int,int);
    
    //basic voronoi stuff
    ofxVoronoi2D voronoi;
    ofRectangle voroRect;
    
    vector<ofVec2f> voroStartPoints;
    vector<CellPoint> cellPoints;
    vector<VertexPoint> vertexPoints;
    vector<VoroEdge> edges;
    
    
    void generateVoro(vector<ofVec2f>);
    
    int counter;
    
    
    //terrain stuff
    //add int random watercells, int add radnom watercell to coast, int number of rivers
    void generateTerrain(int,int,int);
    
    void terrainSetWater(int , int);
    void terrainSetElevation();
    void generateRivers(int);
    
    //terrain helper
    bool checkRand(ofVec2f);
    bool checkCoast(ofVec2f);
    
    CellPoint *findCoast(CellPoint*);
    
    vector< vector<ofVec2f> > riverPoints;
    vector<ofPolyline> rivers;
    
    int highestCell;

    
    
};

#endif /* defined(__voronoi_test__terrainGen__) */
