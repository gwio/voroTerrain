//
//  terrainGen.cpp
//  voronoi_test
//
//  Created by Christian Gwiozda on 19.08.14.
//
//

#include "terrainGen.h"

TerrainGen::TerrainGen() {
    
}


void TerrainGen::start(vector<ofVec2f> voroStartPoints_, int waterCells_, int coastPass_, int rivers_){
    
    voroStartPoints.clear();
    counter = 0;
    voroStartPoints = voroStartPoints_;
    //make a function, and 3* smooth cell centroid -> voronoiStartPoint
    for (int i = 0; i < 3 ; i++) {
        generateVoro(voroStartPoints);
    }
    
    //make terrain from voronoiData
    
    //add int random watercells, int add radnom watercell to coast, int number of rivers
    generateTerrain(waterCells_,coastPass_,rivers_);
    
    
    
}

void TerrainGen::generateVoro( vector<ofVec2f> startPoints_) {
    
    
    cellPoints.clear();
    vertexPoints.clear();
    edges.clear();
    
    //points for voronoi2d
    
    //add cell points
    
    
    for (int i = 0; i < startPoints_.size(); i++) {
        
        cellPoints.push_back( CellPoint(startPoints_.at(i),i) );
        
        //  pointBag.push_back();
        
        
    }
    
    
    
    voroRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    voronoi.compute(startPoints_, voroRect, 1.0);
    
    
    //add all cell vertices to vertexPoints, check for dublicates
    for (ofxSegmentIterator it = voronoi.edges(); it; ++it) {
        
        ofxSegment s = *it;
        
        string PAx = ofToString(s.p1.x,2);
        string PAy = ofToString(s.p1.y,2);
        
        string PBx = ofToString(s.p2.x,2);
        string PBy = ofToString(s.p2.y,2);
        
        ofVec2f pointA = ofVec2f( ofToFloat(PAx), ofToFloat(PAy));
        ofVec2f pointB = ofVec2f( ofToFloat(PBx), ofToFloat(PBy));
        
        bool testA;
        bool testB;
        
        //hmm vielleicht doch float
        if ( pointA != pointB) {
            
            
            testA = false;
            for (int  i = 0; i < vertexPoints.size(); i++) {
                if (( vertexPoints[i].point ==  pointA) || (vertexPoints[i].point-pointA).length() < 0.02) {
                    testA = true;
                    break;
                }
            }
            if (testA == false ) {
                vertexPoints.push_back(pointA);
            }
            
            
            testB = false;
            for (int  i = 0; i < vertexPoints.size(); i++) {
                if (( vertexPoints[i].point ==  pointB) || (vertexPoints[i].point-pointB).length() < 0.02) {
                    testB = true;
                    break;
                }
                
            }
            
            if (testB == false ) {
                vertexPoints.push_back(pointB);
            }
            
            
            
        }
        
    }
    
    
    
    
    //add cellPoint* to vertexPoints
    //for each vertexPoint add the two nearest cellPoints
    
    
    for (ofxSegmentIterator it = voronoi.edges(); it; ++it) {
        
        ofxSegment s = *it;
        vector<cellDist> cellCompare;
        cellCompare.clear();
        
        ofVec2f ptA,ptB;
        
        
        string PAx = ofToString(s.p1.x,2);
        string PAy = ofToString(s.p1.y,2);
        
        string PBx = ofToString(s.p2.x,2);
        string PBy = ofToString(s.p2.y,2);
        
        ptA = ofVec2f( ofToFloat(PAx), ofToFloat(PAy));
        ptB = ofVec2f( ofToFloat(PBx), ofToFloat(PBy));
        
        if (ptA != ptB) {
            
            ofVec2f ptC = ptA-ptB;
            float len = ptC.length()/2;
            ofVec2f ptX = ptA-((ptC.normalize())*len);
            
            
            
            for (int k = 0; k < cellPoints.size(); k++) {
                cellDist temp;
                temp.distance = (ptX-cellPoints[k].point).length();
                temp.iD = k;
                temp.midPoint = ptX;
                cellCompare.push_back(temp);
                
            }
            
            sort(cellCompare.begin(),cellCompare.end());
            
            //prepare VoroEdge
            VoroEdge tempEdge = VoroEdge();
            tempEdge.cellA = &cellPoints[cellCompare[0].iD];
            tempEdge.cellB = &cellPoints[cellCompare[1].iD];
            
            bool testA = false;
            bool testB = false;
            
            for (int k = 0; k < vertexPoints.size(); k++) {
                if ( (vertexPoints[k].point ==  ptA) ||  (vertexPoints[k].point-ptA).length() < 0.02 ) {
                    testA= true;
                    //add vertexA zo Edge
                    tempEdge.ptA = &vertexPoints[k];
                    bool test = false;
                    for (int l = 0; l < vertexPoints[k].ownCells.size(); l++) {
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[0].iD) {
                            test = true;
                            break;
                        }
                    }
                    if (test == false) {
                        vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[0].iD]);
                    }
                    test = false;
                    for (int l = 0; l < vertexPoints[k].ownCells.size(); l++) {
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[1].iD) {
                            test = true;
                            break;
                        }
                    }
                    if (test == false) {
                        vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[1].iD]);
                    }
                }
            }
            
            for (int k = 0; k < vertexPoints.size(); k++) {
                if ( (vertexPoints[k].point ==  ptB) ||  (vertexPoints[k].point-ptB).length() < 0.02 ) {
                    testB=true;
                    //add vertexB to edge
                    tempEdge.ptB = &vertexPoints[k];
                    bool test = false;
                    for (int l = 0; l < vertexPoints[k].ownCells.size(); l++) {
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[0].iD) {
                            test = true;
                            break;
                        }
                    }
                    if (test == false) {
                        vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[0].iD]);
                    }
                    test = false;
                    for (int l = 0; l < vertexPoints[k].ownCells.size(); l++) {
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[1].iD) {
                            test = true;
                            break;
                        }
                    }
                    if (test == false) {
                        vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[1].iD]);
                    }
                }
            }
            if (testA&&testB) {
                edges.push_back(tempEdge);
            }
            
        }
        
        
    }
    
    //add vertexPoints to Cells
    
    for (int i = 0; i < vertexPoints.size(); i++) {
        for (int j = 0; j < vertexPoints[i].ownCells.size(); j++) {
            vertexPoints[i].ownCells[j]->ownVertex.push_back(&vertexPoints[i]);
        }
    }
    
    //add voroEdges to Cells and add edges to vertexPoints
    
    for (int i = 0; i < edges.size(); i++) {
        edges[i].cellA->ownEdges.push_back(&edges[i]);
        edges[i].cellB->ownEdges.push_back(&edges[i]);
        
        edges[i].ptA->ownEdges.push_back(&edges[i]);
        edges[i].ptB->ownEdges.push_back(&edges[i]);
        
    }
    
    //generate cellMeshes
    for (int i = 0; i < cellPoints.size(); i++) {
        cellPoints[i].makeCellMesh();
    }
    
    
    //add cellpoints entroids to new startpoints
    
    voroStartPoints.clear();
    
    for (int i = 0; i < cellPoints.size(); i++) {
        
        voroStartPoints.push_back(cellPoints[i].centroid);
    }
    
}


CellPoint *TerrainGen::findCoast(CellPoint *point_) {
    
    float curEle = point_->elevation;
    CellPoint *curCell = point_;
    for (int i = 0; i < point_->ownEdges.size(); i++) {
        if (point_->ownEdges[i]->cellA != point_) {
            if (point_->ownEdges[i]->cellA->elevation < curEle) {
                curEle = point_->ownEdges[i]->cellA->elevation;
                curCell = point_->ownEdges[i]->cellA;
            }
        }
        
        if (point_->ownEdges[i]->cellB != point_) {
            if (point_->ownEdges[i]->cellB->elevation < curEle) {
                curEle = point_->ownEdges[i]->cellB->elevation;
                curCell = point_->ownEdges[i]->cellB;
            }
        }
        
    }
    return curCell;
    
}

void TerrainGen::generateRivers(int num_) {
    //generate river
    
    int thatcell = highestCell;
    cellPoints[highestCell].riverStart =true;
    rivers.clear();
    riverPoints.clear();
    riverPoints.resize(num_);
    for (int k = 0; k < num_; k++) {
        
        
        riverPoints[k].push_back(cellPoints[thatcell].point);
        
        CellPoint *next = findCoast(&cellPoints[thatcell]);
        for (int i = 0; i < 40; i++) {
            
            riverPoints[k].push_back(next->point);
            
            if (next->water) {
                riverPoints[k].push_back(next->point);
                break;
            }
            next = findCoast(next);
            
        }
        
        ofPolyline temp;
        rivers.push_back(temp);
        for (int i = 0; i < riverPoints[k].size(); i++) {
            rivers.at(k).addVertex(riverPoints[k][i]);
        }
        
        
        for(int a = 0; a < cellPoints.size(); a++) {
            if ( (!cellPoints[a].water) && (!cellPoints[a].riverStart) && (cellPoints[a].elevation > (cellPoints[highestCell].elevation*0.7)) ){
                thatcell = a;
                cellPoints[a].riverStart = true;
                break;
            }
        }
    }
    
    
}

//
void TerrainGen::generateTerrain(int waterCells, int coastPass, int rivers_) {
    
    //makes water and coast cells
    terrainSetWater(waterCells,coastPass);
    
    //test for vertexPoint with more then 2 coastEdges
    bool coastTest = false;
    
    for (int i = 0; i < vertexPoints.size(); i++) {
        if (vertexPoints[i].coastEdges > 2) {
            cout << "coastLines" << endl;
            coastTest = true;
            for (int j = 0; j < vertexPoints[i].ownCells.size(); j++) {
                vertexPoints[i].ownCells.at(j)->water = true;
            }
        }
        
    }
    //rerun coastLineGeneration
    if (coastTest) {
        terrainSetWater(0, 0);
    }
    
    //set elevation an highest cell
    terrainSetElevation();
    
    //run rivers
    generateRivers(rivers_);
    
    findCoastLines(&cellPoints);
}

void TerrainGen::terrainSetWater(int loneWaterCells, int coastPass) {
    
    
    
    //sketch for terrain generation
    //makes water
    for (int i = 0; i < cellPoints.size(); i++) {
        for (int j = 0; j < cellPoints[i].ownVertex.size(); j++) {
            if ( checkCoast( cellPoints[i].ownVertex.at(j)->point )){
                cellPoints[i].water = true;
                cellPoints[i].elevation = -10;
                cellPoints[i].hasHeight = true;
                cellPoints[i].setCellColor(ofColor::deepSkyBlue);
                break;
            }
        }
    }
    
    //add a few random water cells
    for (int k= 0; k < loneWaterCells; k++) {
        
        int cellCounter = (int)ofRandom(cellPoints.size());
        for (int i = 0; i < voroStartPoints.size()/200; i++) {
            if ( !cellPoints[i].water) {
                cellPoints[(i+cellCounter)%voroStartPoints.size()].water = true;
                cellPoints[(i+cellCounter)%voroStartPoints.size()].elevation = -10;
                cellPoints[(i+cellCounter)%voroStartPoints.size()].hasHeight = true;
                cellPoints[(i+cellCounter)%voroStartPoints.size()].setCellColor(ofColor::deepSkyBlue);
            }
        }
    }
    
    //a few more random water cells, fractal like
    //add a few random water cells
    for (int k = 0; k < coastPass; k++) {
        for (int i = 0; i < cellPoints.size(); i++) {
            if ((cellPoints[i].water)  && ((int)ofRandom(3+k) == 1) ){
                for (int j = 0; j < cellPoints[i].ownEdges.size(); j++) {
                    if (!cellPoints[i].ownEdges[j]->cellA->water) {
                        cellPoints[i].ownEdges[j]->cellA->water = true;
                        cellPoints[i].ownEdges[j]->cellA->elevation = -10;
                        cellPoints[i].ownEdges[j]->cellA->hasHeight = true;
                        cellPoints[i].ownEdges[j]->cellA->setCellColor(ofColor::deepSkyBlue);
                    }
                    if (!cellPoints[i].ownEdges[j]->cellB->water) {
                        cellPoints[i].ownEdges[j]->cellB->water = true;
                        cellPoints[i].ownEdges[j]->cellB->elevation = -10;
                        cellPoints[i].ownEdges[j]->cellB->hasHeight = true;
                        cellPoints[i].ownEdges[j]->cellB->setCellColor(ofColor::deepSkyBlue);
                    }
                }
                
            }
        }
    }
    
    
    //set the coast
    
    for (int i = 0; i < cellPoints.size(); i++) {
        if ( !cellPoints[i].water){
            for (int j = 0; j < cellPoints[i].ownEdges.size(); j++) {
                if ( ((cellPoints[i].ownEdges[j]->cellA->water) || (cellPoints[i].ownEdges[j]->cellB->water)) ){
                    cellPoints[i].elevation = 0;
                    cellPoints[i].hasHeight = false;
                    cellPoints[i].setCellColor(ofColor::burlyWood);
                    cellPoints[i].isCoast = true;
                    break;
                }
            }
        }
    }
    
    //set edge to isCoast
    // set coastEdges for vertexPoints to 0
    
    for (int i = 0; i < vertexPoints.size(); i++) {
        vertexPoints[i].coastEdges = 0;
    }
    
    //count coastEdges for each vertex
    for (int i = 0; i < cellPoints.size(); i++) {
        if (cellPoints[i].isCoast) {
            for (int j = 0; j < cellPoints[i].ownEdges.size(); j++) {
                if (  ((cellPoints[i].ownEdges[j]->cellA->water) || (cellPoints[i].ownEdges[j]->cellB->water)) ){
                    cellPoints[i].ownEdges[j]->isCoast = true;
                    cellPoints[i].ownEdges[j]->ptA->coastEdges++;
                    cellPoints[i].ownEdges[j]->ptB->coastEdges++;
                    
                }
                
            }
        }
    }
    
    
    
    
    
}

void TerrainGen::terrainSetElevation() {
    float colorVal = ofRandom(255);
    
    for (int i = 0; i < cellPoints.size(); i++) {
        float distToCoast = 100000*1000;
        
        if(   (!cellPoints[i].hasHeight) ) {
            
            for (int j = 0; j < cellPoints.size(); j++) {
                if( ( (cellPoints[j].isCoast) )) {
                    
                    float tempLen = (cellPoints[i].centroid - cellPoints[j].centroid).length();
                    
                    if (tempLen < distToCoast) {
                        distToCoast = tempLen;
                    }
                }
                
            }
            float elevationTemp = ofMap(distToCoast, 0, 400, 50, 255);
            cellPoints[i].elevation = elevationTemp;
            cellPoints[i].hasHeight = true;
            cellPoints[i].setCellColor(ofColor::fromHsb( colorVal, 205-elevationTemp,elevationTemp*1.4));
        }
    }
    
    //get highest cell
    float maxEle = 0;
    for (int i = 0; i < cellPoints.size(); i++) {
        if (cellPoints[i].elevation > maxEle) {
            maxEle = cellPoints[i].elevation;
            highestCell = i;
        }
    }
}



bool TerrainGen::checkRand(ofVec2f p_) {
    return (
            (p_.x < 0.5) ||
            (p_.x > ofGetWidth()-0.5 ) ||
            (p_.y < 0.5) ||
            (p_.y > ofGetHeight()-0.5 )
            );
}

bool TerrainGen::checkCoast(ofVec2f p_) {
    return (
            (p_.x < ofRandom(20,150)) ||
            (p_.x > ofGetWidth()-ofRandom(20,150)) ||
            (p_.y < ofRandom(20,150)) ||
            (p_.y > ofGetHeight()-ofRandom(20,150))
            );
}


void TerrainGen::findCoastLines(vector<CellPoint>* cellPoints_) {
    
    coastLines.clear();
    
    int debugCounter = 0;
    
    ofPolyline tempPLine;
    
    VoroEdge *currentEdge;
    VertexPoint *currentPoint;
    VertexPoint *endPoint;
    
    for (int i = 0; i < edges.size(); i++) {
        while (edges[i].isCoast && !edges[i].coastHasPath) {
            tempPLine.clear();

            currentEdge = &edges[i];
            currentPoint = edges[i].ptA;
            endPoint = edges[i].ptB;
            tempPLine.addVertex(edges[i].ptA->point);
            edges[i].coastHasPath = true;
            //break;
            
            
            while ((currentPoint != endPoint) && (debugCounter < 100000)){
                debugCounter++;
                //  cout << debugCounter << endl;
                
                for (int j = 0; j < currentPoint->ownEdges.size(); j++) {
                    
                    if ( (currentPoint->ownEdges.at(j)->isCoast) && (currentEdge != currentPoint->ownEdges.at(j)) ) {
                        
                        if (currentPoint->ownEdges.at(j)->ptA != currentPoint ) {
                            tempPLine.addVertex(currentPoint->ownEdges.at(j)->ptA->point);
                            currentEdge = currentPoint->ownEdges.at(j);
                            currentPoint = currentPoint->ownEdges.at(j)->ptA;
                            currentEdge->coastHasPath = true;
                            cout << currentPoint->coastEdges << endl;
                            
                            break;
                        }
                        
                        
                        if (currentPoint->ownEdges.at(j)->ptB != currentPoint ) {
                            tempPLine.addVertex(currentPoint->ownEdges.at(j)->ptB->point);
                            currentEdge = currentPoint->ownEdges.at(j);
                            currentPoint = currentPoint->ownEdges.at(j)->ptB;
                            currentEdge->coastHasPath = true;
                            cout << currentPoint->coastEdges << endl;
                            
                            break;
                        }
                    }
                    
                    
                }
                
            }
            //tempPLine.addVertex(endPoint);
            tempPLine.close();
            coastLines.push_back(tempPLine);

        }
    }
    
    
    
    
    
    
    
    
    
    
    
}