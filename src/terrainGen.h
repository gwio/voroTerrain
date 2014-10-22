//
//  terrainGen.h
//  voronoi_test
//
//  Created by Christian Gwiozda on 19.08.14.
//
//

#pragma once


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
    //add width, height, startPoints vector, int random watercells, int add radnom watercell to coast, int number of rivers
    TerrainGen();

    void start(int,int,vector<ofVec2f>,int,int,int);
    
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
    void findCoastLines(vector<CellPoint>*);

    
    //for use in forest game
    
    vector<ofPolyline> coastLines;
    
    
    void makeObjectMap();
    ofFbo tempFbo;
    ofPixels pixTemp;
    
    ofImage terrainMap;
    ofImage waterMap;
    ofImage coastMap;
    
    ofImage treeMap;
    
};

