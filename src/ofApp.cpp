#include "ofApp.h"

#define CELLS 400
//--------------------------------------------------------------
void ofApp::setup(){
    counter = 0;
  //  ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    
    voroStartPoints.clear();
    
    for (int i= 0; i < CELLS; i++) {
        ofVec2f    tPoint = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        voroStartPoints.push_back(tPoint);
    }

    generateVoro(&voroStartPoints);
    
   }



//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(ofColor::fromHsb(150, 55, 60));
    
    //tempMesh.draw();
    
   
    
    /*
     for (int i = 0; i <cellPoints.size() ; i++) {
     ofSetColor(122, 220, 0);
     ofEllipse(cellPoints[i].point, 2, 2);
     }
     */
    
    
    for (int i = 0; i < cellPoints.size(); i++) {
        ofSetColor(255,255, 255,40);
        
       // cellPoints[i].drawCellPoint();
        ofSetColor(200, 200, 200,10);
       // cellPoints[i].drawOwnVertex();
        cellPoints[i].drawCellMesh();
    }
    
    
    
    ofSetColor(ofColor::fromHsb(20, (sin(ofGetElapsedTimef()*5)*100)+150 ,255) );
    cellPoints[counter%cellPoints.size()].drawOwnVertex();
    
    cellPoints[counter%cellPoints.size()].drawNeighbours();
    
    
    for (int i = 0; i <vertexPoints.size() ; i++) {
        ofSetColor(255, 0, 0);
        // vertexPoints[i].drawVertex();
        ofSetColor(255, 225 ,225, 20);
        
        //  vertexPoints[i].drawOwnCells();
    }
    
    
  /*
    for (int i = 0; i < edges.size(); i++) {
        ofSetColor(ofColor::fromHsb(120, 15, 220));
        edges[i].drawEdge();
    }
    */
    
    //voroMesh.drawWireframe();
    ofSetColor(255);
    ofDrawBitmapString( "vertices "+ ofToString(cellPoints[counter%cellPoints.size()].ownVertex.size())+ "  id:"+ofToString(cellPoints[counter%cellPoints.size()].iD), 40, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_RIGHT) {
        counter++;
    }
    
    if (key == OF_KEY_LEFT) {
        counter--;
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

void ofApp::generateVoro( vector<ofVec2f>* startPoints_) {
    
    
    cellPoints.clear();
    vertexPoints.clear();
    edges.clear();
    
    voroMesh.clear();
    //points for voronoi2d
    
    //add cell points
    
    
    for (int i = 0; i < startPoints_->size(); i++) {
        ofVec2f    tPoint = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        
        cellPoints.push_back( CellPoint(startPoints_->at(i),i) );
        
        
        
    }
    
    
    
    voroRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    voronoi.compute(*startPoints_, voroRect);
    
    
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
