#include "ofApp.h"

#define CELLS 30
//--------------------------------------------------------------
void ofApp::setup(){
    counter = 0;
    ofDisableAntiAliasing();
    ofEnableAlphaBlending();
    cellPoints.clear();
    vertexPoints.clear();
    
    voroMesh.clear();
    //points for voronoi2d
    
    //add cell points
    for (int i = 0; i < CELLS; i++) {
        ofVec2f tPoint = ofVec2f((int)ofRandom(ofGetWidth()), (int)ofRandom(ofGetHeight()));
        cellPoints.push_back( CellPoint(tPoint,i) );
        pointBag.push_back(tPoint);
        
    }
    
    voroRect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    voronoi.compute(pointBag, voroRect, 20.0f);
    
    voronoi.buildMesh(voroMesh);
    
    /*
     for (int i = 0; i < voronoi.cells.size(); i++) {
     
     ofPolyline temp;
     
     for (int j = 0; j < voronoi.cells[i].pts.size(); j++) {
     temp.addVertex(voronoi.cells[i].pts[j]);
     }
     CellPoint blub = CellPoint( temp.getCentroid2D(),i);
     cellPoints.push_back(blub);
     }
     */
    
    
    //add all cell vertices to vertexPoints, check for dublicates
    for (ofxSegmentIterator it = voronoi.edges(); it; ++it) {
        
        ofxSegment s = *it;
        ofVec2f pointA = s.p1;
        ofVec2f pointB = s.p2;
        
        bool testA;
        bool testB;
        
        //hmm vielleicht doch float
        if ( pointA != pointB) {
            
            cout << pointA << "   " << pointB << endl;
            
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
    
    cout << vertexPoints.size() << endl;
    
    for (int x = 0; x < vertexPoints.size(); x++) {
        cout << vertexPoints[x].point << endl;
    }
    
    //add cellPoint* to vertexPoints
    //for each vertexPoint add the two nearest cellPoints
    
    
    for (ofxSegmentIterator it = voronoi.edges(); it; ++it) {
        
        ofxSegment s = *it;
        vector<cellDist> cellCompare;
        cellCompare.clear();
        
        ofVec2f ptA,ptB;
        ptA = s.p1;
        ptB = s.p2;
        
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
            
            
            
            
            //  cout << cellCompare[0].distance - cellCompare[1].distance << endl;
            
            for (int k = 0; k < vertexPoints.size(); k++) {
                if (vertexPoints[k].point ==  ptA) {
                    bool test = false;
                    for (int l = 0; l < vertexPoints[k].ownCells.size(); l++) {
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[0].iD) {
                            test = true;
                            cout << "AAA1" << endl;
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
                            cout << "AAA2" << endl;
                            
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
                    bool test = false;
                    for (int l = 0; l < vertexPoints[k].ownCells.size(); l++) {
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[0].iD) {
                            test = true;
                            cout << "BBB1" << endl;
                            
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
                            cout << "BBB2" << endl;
                            
                            break;
                        }
                    }
                    if (test == false) {
                        vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[1].iD]);
                    }
                }
            }
            
        }
        
        
    }
    
    //add vertexPoints to Cellvector
    cout << vertexPoints.size() << endl;
    
    for (int i = 0; i < vertexPoints.size(); i++) {
        for (int j = 0; j < vertexPoints[i].ownCells.size(); j++) {
            //bool test = false;
            
            //for (int k = 0; vertexPoints[i].ownCells[j]->ownVertex.size(); k++) {
            
            vertexPoints[i].ownCells[j]->ownVertex.push_back(&vertexPoints[i]);
            
            //}
        }
    }
    
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(22,22, 11);
    
    //tempMesh.draw();
    ofxSegmentIterator it = voronoi.edges();
    for(; it; ++it){
        ofxSegment s = *it;
        ofSetColor(155,0,0);
        ofLine(s.p1, s.p2);
    }
    
    /*
     for (int i = 0; i <cellPoints.size() ; i++) {
     ofSetColor(122, 220, 0);
     ofEllipse(cellPoints[i].point, 2, 2);
     }
     */
    
    
    for (int i = 0; i < midPoints.size(); i++) {
        ofSetColor(0, 0, 255);
        ofEllipse(midPoints[i], 5, 5);
    }
    
    for (int i = 0; i <pointBag.size() ; i++) {
        ofSetColor(122, 220, 0);
        ofEllipse(pointBag[i], 2, 2);
    }
    
    
    for (int j = 0; j < cellPoints[counter%cellPoints.size()].ownVertex.size(); j++) {
        ofLine(cellPoints[counter%cellPoints.size()].point, cellPoints[counter%cellPoints.size()].ownVertex[j]->point);
    }
    
    
    
    
    for (int i = 0; i <vertexPoints.size() ; i++) {
        ofSetColor(255, 0, 0);
        ofEllipse(vertexPoints[i].point, 4, 4);
        
        ofSetColor(255, 225 ,225, 20);
        
        for (int j = 0; j < vertexPoints[i].ownCells.size(); j++) {
            // if (counter%cellPoints.size() == vertexPoints[i].ownCells[j]->iD){
              ofLine(vertexPoints[i].point, vertexPoints[i].ownCells[j]->point);
            //  }
        }
    }
    
    
    //voroMesh.drawWireframe();
    
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
    
    pointBag.push_back(ofVec2f(x, y));
    
    voronoi.compute(pointBag, voroRect,0.0);
    
    voroMesh.clear();
    voronoi.buildMesh(voroMesh);
    
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
