#include "ofApp.h"

#define CELLS 700
//--------------------------------------------------------------
void ofApp::setup(){
    voroStartPoints.clear();
    counter = 0;
      ofDisableAntiAliasing();
    ofEnableAlphaBlending();

    for (int i= 0; i < CELLS; i++) {
        ofVec2f    tPoint = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        voroStartPoints.push_back(tPoint);
    }
    
    
    
    generateVoro(voroStartPoints);
    
    voroStartPoints.clear();
    
    
    //genereate new Voronoi from cell centroids


    for (int i = 0; i < cellPoints.size(); i++) {
        
        voroStartPoints.push_back(cellPoints[i].centroid);
    }
    
    generateVoro(voroStartPoints);
    
    voroStartPoints.clear();
    
    
    //genereate new Voronoi from cell centroids
    for (int i = 0; i < cellPoints.size(); i++) {
        
        voroStartPoints.push_back(cellPoints[i].centroid);
    }
    
    generateVoro(voroStartPoints);
    
    

    
    //sketch for terrain generation
    
    for (int i = 0; i < cellPoints.size(); i++) {
        for (int j = 0; j < cellPoints[i].ownVertex.size(); j++) {
            if ( checkCoast( cellPoints[i].ownVertex[j]->point )){
                cellPoints[i].water = true;
                cellPoints[i].hasHeight = true;
                cellPoints[i].setCellColor(ofColor::deepSkyBlue);
                break;
            }
        }
    }
    
    //add a few random water cells
    for (int i = 0; i < cellPoints.size(); i++) {
        if ((cellPoints[i].water)  && ((int)ofRandom(4) == 1) ){
            for (int j = 0; j < cellPoints[i].ownEdges.size(); j++) {
                if (!cellPoints[i].ownEdges[j]->cellA->water) {
                    cellPoints[i].ownEdges[j]->cellA->water = true;
                    cellPoints[i].ownEdges[j]->cellA->hasHeight = true;
                    cellPoints[i].ownEdges[j]->cellA->setCellColor(ofColor::deepSkyBlue);
                }
                if (!cellPoints[i].ownEdges[j]->cellB->water) {
                    cellPoints[i].ownEdges[j]->cellB->water = true;
                    cellPoints[i].ownEdges[j]->cellB->hasHeight = true;
                    cellPoints[i].ownEdges[j]->cellB->setCellColor(ofColor::deepSkyBlue);
                }
            }
            
        }
    }
    
    //and again
    for (int i = 0; i < cellPoints.size(); i++) {
        if ((cellPoints[i].water)  && ((int)ofRandom(6) == 1) ){
            for (int j = 0; j < cellPoints[i].ownEdges.size(); j++) {
                if (!cellPoints[i].ownEdges[j]->cellA->water) {
                    cellPoints[i].ownEdges[j]->cellA->water = true;
                    cellPoints[i].ownEdges[j]->cellA->hasHeight = true;
                    cellPoints[i].ownEdges[j]->cellA->setCellColor(ofColor::deepSkyBlue);
                }
                if (!cellPoints[i].ownEdges[j]->cellB->water) {
                    cellPoints[i].ownEdges[j]->cellB->water = true;
                    cellPoints[i].ownEdges[j]->cellB->hasHeight = true;
                    cellPoints[i].ownEdges[j]->cellB->setCellColor(ofColor::deepSkyBlue);
                }
            }
            
        }
    }
    
    
    //set highest elevation
    /*
    float tempDist;
    tempDist = 1000*1000;
    int centerCell;
    ofVec2f centerP = ofVec2f(ofGetWidth()/2 + ofRandom(-100,100), ofGetHeight()/2 + ofRandom(-100,100) );
    for (int i = 0; i < cellPoints.size(); i++) {
        float tempLen = (cellPoints[i].point-centerP).lengthSquared();
        if ( tempLen < tempDist) {
            tempDist = tempLen;
            centerCell = i;
        };
    }
    */
    
   // cellPoints[centerCell].elevation = 255;
   // cellPoints[centerCell].hasHeight = true;
   // cellPoints[centerCell].setCellColor(ofColor::whiteSmoke);
    
    
    //set the coast
    
    for (int i = 0; i < cellPoints.size(); i++) {
        if ( !cellPoints[i].water){
            for (int j = 0; j < cellPoints[i].ownEdges.size(); j++) {
                if ( ((cellPoints[i].ownEdges[j]->cellA->water) || (cellPoints[i].ownEdges[j]->cellB->water)) ){
                    cellPoints[i].elevation = 0;
                    cellPoints[i].hasHeight = true;
                    cellPoints[i].setCellColor(ofColor(40));
                    cellPoints[i].isCoast = true;
                    break;
                }
            }
        }
    }
    
    //set elevation for the rest
    
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
                //cout << distToCoast << endl;

            }
           // cout << distToCoast << endl;
            float elevationTemp = ofMap(distToCoast, 0, 500, 50, 255);
            cellPoints[i].elevation = elevationTemp;
            cellPoints[i].hasHeight = true;
            cellPoints[i].setCellColor(ofColor::fromHsb( 40, 60,elevationTemp));
        }
    }
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor::fromHsb(150, 55, 60));
    ofBackground(ofColor::deepSkyBlue);
    
    //tempMesh.draw();
    
    
    
  
    
    for (int i = 0; i < cellPoints.size(); i++) {
        cellPoints[i].drawCellMesh();
        
        ofSetColor(255,255, 255,40);
        
         //cellPoints[i].drawCellPoint();
        ofSetColor(200, 200, 200,50);
        //cellPoints[i].drawOwnVertex();
       
    }
    
    
    
    //cellPoints[counter%cellPoints.size()].drawOwnVertex();
    
   // cellPoints[counter%cellPoints.size()].drawNeighbours();
    

    
    
   
    
    
   

    //voroMesh.drawWireframe();
    ofSetColor(255);
   // ofDrawBitmapString( "vertices "+ ofToString(cellPoints[counter%cellPoints.size()].ownVertex.size())+ "  id:"+ofToString(cellPoints[counter%cellPoints.size()].iD), 40, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_RIGHT) {
        counter++;
    }
    
    if (key == OF_KEY_LEFT) {
        counter--;
    }
    
    if (key == 's' ){
        ofImage temp;
        temp.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        temp.resize(ofGetWidth()/2, ofGetHeight()/2);
        temp.saveImage( ofToString( ofGetElapsedTimef()+ofRandom(1000))+ ".png");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}



bool ofApp::checkRand(ofVec2f p_) {
    return (
            (p_.x < 0.5) ||
            (p_.x > ofGetWidth()-0.5 ) ||
            (p_.y < 0.5) ||
            (p_.y > ofGetHeight()-0.5 )
            );
}

bool ofApp::checkCoast(ofVec2f p_) {
    return (
            (p_.x < ofRandom(50,200)) ||
            (p_.x > ofGetWidth()-ofRandom(50,200)) ||
            (p_.y < ofRandom(50,200)) ||
            (p_.y > ofGetHeight()-ofRandom(50,200))
            );
}

void ofApp::generateVoro( vector<ofVec2f> startPoints_) {
    
    
    cellPoints.clear();
    vertexPoints.clear();
    edges.clear();
    
    voroMesh.clear();
    //points for voronoi2d
    
    //add cell points
    
    
    for (int i = 0; i < CELLS; i++) {
        
        cellPoints.push_back( CellPoint(startPoints_.at(i),i) );
        
      //  pointBag.push_back();
        
        
    }
    
    
    
    voroRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    voronoi.compute(startPoints_, voroRect);
    
    
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
                if ( vertexPoints[i].point ==  pointA ){
                    testA = true;
                    break;
                }
            }
            if (testA == false ) {
                vertexPoints.push_back(pointA);
            }
            
            
            testB = false;
            for (int  i = 0; i < vertexPoints.size(); i++) {
                if ( vertexPoints[i].point ==  pointB ){
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
            
            //  if ( !checkRand(ptX)) {
            midPoints.push_back(ptX);
            
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
            
            
            
            for (int k = 0; k < vertexPoints.size(); k++) {
                if (vertexPoints[k].point ==  ptA) {
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
                if (vertexPoints[k].point ==  ptB) {
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
            
            edges.push_back(tempEdge);
            
        }
        
        
    }
    
    //add vertexPoints to Cells
    
    for (int i = 0; i < vertexPoints.size(); i++) {
        for (int j = 0; j < vertexPoints[i].ownCells.size(); j++) {
            vertexPoints[i].ownCells[j]->ownVertex.push_back(&vertexPoints[i]);
        }
    }
    
    //add voroEdges to Cells
    
    for (int i = 0; i < edges.size(); i++) {
        edges[i].cellA->ownEdges.push_back(&edges[i]);
        edges[i].cellB->ownEdges.push_back(&edges[i]);
        
        
    }
    
    for (int i = 0; i < cellPoints.size(); i++) {
        cellPoints[i].makeCellMesh();
    }
    
}
