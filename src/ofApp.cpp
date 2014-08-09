#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    counter = 0;
    ofDisableAntiAliasing();
    
    cellPoints.clear();
    vertexPoints.clear();
    
    voronoi.setBounds(0, 0, ofGetWidth(), ofGetHeight());
    
    //add cell points
    for (int i = 0; i < 8; i++) {
        CellPoint temp = CellPoint( ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()) ),i );
        cellPoints.push_back(temp);
       // voronoi.addPoint(ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight())));

    }
    
    
    for (int i = 0; i < cellPoints.size(); i++) {
        voronoi.addPoint(cellPoints[i].point);

    }
    voronoi.generateVoronoi();
    
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
    
    
    //add all cell vertices, check for dublicates
    for (int i = 0; i < voronoi.cells.size(); i++) {
        
        for (int j = 0; j < voronoi.cells[i].pts.size(); j++) {
            
            ofVec2f temp = voronoi.cells[i].pts[j];
            
            bool test = false;
            
            for (int k = 0; k < vertexPoints.size(); k++) {
                if (vertexPoints[k].point == temp) {
                    test = true;
                    break;
                }
            }
            
            if (test == false) {
                vertexPoints.push_back(temp);
            }
            
        }
        
    }
    
    //add cellPoint* to vertexPoints
    //for each vertexPoint add the two nearest cellPoints
    
    
    for (int i = 0; i < voronoi.cells.size(); i++) {
        
        
        for (int j = 0; j < voronoi.cells[i].pts.size(); j++) {
            vector<cellDist> cellCompare;
            cellCompare.clear();
            
            ofVec2f ptA,ptB;
            ptA = voronoi.cells[i].pts[j];
            if (j == voronoi.cells[i].pts.size()-1) {
                ptB = voronoi.cells[i].pts[0];
            } else {
                ptB = voronoi.cells[i].pts[j+1];
            }
            
            ofVec2f ptC = ptA-ptB;
            float len = ptC.length()/2;
            ofVec2f ptX = ptA-((ptC.normalize())*len);
            
            if ( !checkRand(ptX)) {
                midPoints.push_back(ptX);
                cout << ptX << endl ;
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
                    
                    
                    bool addZero = true;
                    bool addOne = true;
                    for (int l = 0; l < vertexPoints[k].ownCells.size(); l++) {
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[0].iD){
                            addZero = false;
                        }
                        if (vertexPoints[k].ownCells[l]->iD == cellCompare[1].iD){
                            addOne = false;
                        }
                    }
                    if (vertexPoints[k].point == ptA) {
                        //if( !checkCorner(vertexPoints[k].point) ) {
                        if ( (addZero) ) {
                            vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[0].iD]);
                        }
                        if ( (addOne)  ) {
                            vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[1].iD]);
                        }
                        //  break;
                    } else {
                        if (addZero) {
                            // vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[0].iD]);
                        }
                        //   break;
                        //  }
                    }
                    
                    if(vertexPoints[k].point == ptB) {
                        //  if( !checkCorner(vertexPoints[k].point) ) {
                        if ( (addZero) ) {
                            vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[0].iD]);
                        }
                        if ( (addOne) ) {
                           // vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[1].iD]);
                        }
                        //   break;
                    } else {
                        if (addZero) {
                            //   vertexPoints[k].ownCells.push_back(&cellPoints[cellCompare[0].iD]);
                        }
                        //   break;
                        //}
                    }
                    
                    
                    
                }
                
            }
            
            
        }
        
    }
    
    
    
    
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    voronoi.draw();
    
    
    for (int i = 0; i < cellPoints.size();i++) {
        ofSetColor(255);
        ofEllipse(cellPoints[i].point, 6, 6);
    }
    
    
    
    for (int i = 0; i < vertexPoints.size(); i++) {
        ofSetColor(100, 255, 0);
        ofEllipse(vertexPoints[i].point, 4, 4);
        for (int j = 0; j < vertexPoints[i].ownCells.size(); j++) {
            ofSetColor(ofColor::fromHsb(vertexPoints[i].ownCells[j]->iD*14, 255, 255));
            ofLine(vertexPoints[i].point, vertexPoints[i].ownCells[j]->point);
        }
        
    }
    for (int i=0; i < midPoints.size(); i++) {
        ofSetColor(255,0,0);
        ofEllipse(midPoints[i], 4, 4);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    counter++;
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

bool ofApp::checkCorner(ofVec2f p_) {
    return ( ((p_.x == 0) && (p_.y == 0)) ||
            ((p_.x == ofGetWidth()) && (p_.y == 0)) ||
            ((p_.x == ofGetWidth()) && (p_.y == ofGetHeight())) ||
            ((p_.x == 0) && (p_.y == ofGetHeight()))
            );
    
}

bool ofApp::checkRand(ofVec2f p_) {
    return (
            (p_.x < 0.5) ||
            (p_.x > ofGetWidth()-0.5 ) ||
            (p_.y < 0.5) ||
            (p_.y > ofGetHeight()-0.5 )
            );
}
