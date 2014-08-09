//
//  voronoiData.cpp
//  voronoi_test
//
//  Created by Christian Gwiozda on 08.08.14.
//
//

#include "voronoiData.h"


CellPoint::CellPoint(ofVec2f point_, int id_) {
    point = point_;
    iD = id_;
    
}

VertexPoint::VertexPoint(ofVec2f point_) {
    point = point_;
    ownCells.clear();
}