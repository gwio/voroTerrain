//
//  voronoiData.cpp
//  voronoi_test
//
//  Created by Christian Gwiozda on 08.08.14.
//
//

#include "voronoiData.h"

//---------------------------------------------------------------------


CellPoint::CellPoint(ofVec2f point_, int id_) {
    point = point_;
    iD = id_;
    ownVertex.clear();
    ownEdges.clear();
    
}

void CellPoint::drawCellPoint() {
    
    ofEllipse(point, 10, 10);
}

void CellPoint::drawOwnVertex() {
    
    for (int i = 0; i < ownVertex.size(); i++) {

        ofLine(ownVertex[i]->point, point);
    }
}

void CellPoint::drawNeighbours() {
    
    ofSetColor(255, 255, 255);
    drawCellPoint();
    
    ofSetColor(ofColor::fromHsb(20, (sin(ofGetElapsedTimef()*5)*100)+150 ,255) );
    for (int i = 0; i < ownEdges.size(); i++) {
        ownEdges[i]->drawEdge();
        
        if ( (ownEdges[i]->cellA->point  -  point).lengthSquared() > 0 ) {
            ownEdges[i]->cellA->drawCellPoint();
        }
        
        if ( (ownEdges[i]->cellB->point  -  point).lengthSquared() > 0 ) {
            ownEdges[i]->cellB->drawCellPoint();
        }
    }
}

//---------------------------------------------------------------------


VertexPoint::VertexPoint(ofVec2f point_) {
    point = point_;
    ownCells.clear();
}

void VertexPoint::drawVertex() {
    
    ofEllipse(point, 4, 4);
}

void VertexPoint::drawOwnCells() {
    
    for (int i = 0; i < ownCells.size(); i++) {
        ofLine(ownCells[i]->point, point);
    }
}

//---------------------------------------------------------------------


VoroEdge::VoroEdge(){
    
}
VoroEdge::VoroEdge(VertexPoint* v1, VertexPoint* v2, CellPoint* c1, CellPoint*c2) {
    
    ptA = v1;
    ptB = v2;
    
    cellA = c1;
    cellB = c2;
}

void VoroEdge::drawEdge() {
    
    ofLine(ptA->point, ptB->point);
}