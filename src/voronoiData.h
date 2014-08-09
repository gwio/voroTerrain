//
//  voronoiData.h
//  voronoi_test
//
//  Created by Christian Gwiozda on 08.08.14.
//
//

#ifndef __voronoi_test__voronoiData__
#define __voronoi_test__voronoiData__


#include "ofMain.h"


class VertexPoint;

class CellPoint {
public:
    CellPoint(ofVec2f,int);
    ofVec2f point;
    int iD;
    //vector<EdgePoint> ownEdgePoints;
  //  VoronoiRegion* region;
};

class VertexPoint {
    
public:
    VertexPoint(ofVec2f);
    ofVec2f point;
    vector<CellPoint*> ownCells;
};



#endif /* defined(__voronoi_test__voronoiData__) */
