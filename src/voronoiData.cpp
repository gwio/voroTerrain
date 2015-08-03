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
    cellMesh.clear();
    water = false;
    hasHeight = false;
    isCoast = false;
    riverStart = false;
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

void CellPoint::makeCellMesh() {
    
    cellMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    ofColor temp = ofColor::fromHsb(ofRandom(255), 100, 155);
    
    for (int i = 0; i < ownEdges.size(); i++) {
        cellMesh.addColor(temp);
        cellMesh.addVertex(point);
        
        cellMesh.addColor(temp);
        cellMesh.addColor(temp);
        
        cellMesh.addVertex(ownEdges[i]->ptA->point);
        cellMesh.addVertex(ownEdges[i]->ptB->point);
        
    }
    
    centroid = cellMesh.getCentroid();
}

void CellPoint::drawCellMesh() {
    
    if (cellMesh.getNumVertices() != 0) {
        cellMesh.draw();
        //cellMesh.drawWireframe();
    }
}

void CellPoint::drawWire() {
    
    if (cellMesh.getNumVertices() != 0) {
        cellMesh.drawWireframe();
    }
}

void CellPoint::setCellColor(ofColor col_) {
    
    
    
    if (cellMesh.getNumVertices() != 0) {
        cellMesh.clearColors();
        for (int i = 0; i < cellMesh.getNumVertices(); i++) {
            cellMesh.addColor(col_);
        }
    }
}

//---------------------------------------------------------------------


VertexPoint::VertexPoint(ofVec2f point_) {
    point = point_;
    ownCells.clear();
    ownEdges.clear();
    coastEdges = 0;
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
    isCoast = false;
    coastHasPath = false;
}


VoroEdge::VoroEdge(VertexPoint* v1, VertexPoint* v2, CellPoint* c1, CellPoint*c2) {
    
    ptA = v1;
    ptB = v2;
    
    cellA = c1;
    cellB = c2;
    
    isCoast = false;
}

void VoroEdge::drawEdge() {
    
    ofLine(ptA->point, ptB->point);
}