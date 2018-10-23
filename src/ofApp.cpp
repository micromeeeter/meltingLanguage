#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i = 0; i < NUM; i++){
        string fileName = "text" + ofToString(i) + ".pdf";
        alphabet[i].load(fileName);
    }
    
    for(int i = 0; i < NUM; i++){
        ofPath& path = alphabet[i].getPathAt(0);
        const vector<ofPolyline > &tmpPoly = path.getOutline();
        for (int k = 0; k < tmpPoly.size(); k++){
            polyline[i].push_back(tmpPoly[k]);
        }
    }

    b_record = false;
    record_counter = 0;
    
    gui.setup();
    gui.add(sp_side.setup("sp_side", 0.4, 0., 1.));
    gui.add(sp_down.setup("sp_down", 0.4, 0., 1.));
    gui.add(scale.setup("scale", 0.5, 0.1, 2.));
    
    gui.setPosition(7, 70);

    showInfo = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    melt();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(0);
    
    if(showInfo){
        ofDrawBitmapStringHighlight("spacekey: capture typography as pdf", 10, 20);
        ofDrawBitmapStringHighlight("- key: delete the last char", 10, 40);
        ofDrawBitmapStringHighlight("[ key: delete at all", 10, 60);
        gui.draw();
    }
    if(b_record){
        ofBeginSaveScreenAsPDF("../font/font_" + ofToString(record_counter) + ".pdf", false);
    }
    
    ofTranslate(ofGetWidth()*0.5, ofGetHeight()*0.5);
    ofPushMatrix();
    ofScale(scale, scale);
    ofTranslate(-ofGetWidth()*0.5, -ofGetHeight()*0.5);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight()* 0.5 - 70);
    
    float x_offset = 0;
    for(int i = 0; i < counter; i++){
        x_offset += fontWidth[i];
    }
    x_offset *= 0.5;
    ofTranslate(-x_offset, 0);
    
    ofPushMatrix();
    for(int i = 0; i < counter; i++){
        cp_stack[i].draw();
        ofTranslate(fontWidth[i], 0);
    }
    
    ofPopMatrix();
    
    ofPopMatrix();
    ofPopMatrix();
    
    if(b_record){
        ofEndSaveScreenAsPDF();
        b_record = false;
        record_counter++;
    }
}

//--------------------------------------------------------------
void ofApp::melt(){
    
//    float weight = 0.9999;
    float sp_side_scaled = 1.0 - 0.0005 * sp_side;
    for(int i = 0; i < counter; i++){
        if(i == 0){
        }else{
            for(int j = 0; j < RESOLUTION; j++){
                cp_stack[i].operator[](j) = sp_side_scaled * cp_stack[i].operator[](j) + (1.- sp_side_scaled) * cp_stack[i-1].operator[](j);
            }
        }
    }
    for(int i = 0; i < counter; i++){
        if(i == counter-1){
        }else{
            for(int j = 0; j < RESOLUTION; j++){
                cp_stack[i].operator[](j) = sp_side_scaled * cp_stack[i].operator[](j) + (1.- sp_side_scaled) * cp_stack[i+1].operator[](j);
            }
        }
    }
    
    float sp_down_scaled = 0.000005 * sp_down;
    for(int i = 0; i < counter; i++){
        for(int j = 0; j < RESOLUTION; j++){
            cp_stack[i].operator[](j).y += (200. - cp_stack[i].operator[](j).y) * sp_down_scaled * sp_side_scaled * cp_stack[i].operator[](j).y;
        }
    }
}

//--------------------------------------------------------------
void ofApp::stackPolyline(int i){
    ofPolyline temp = polyline[i].at(0).getResampledByCount(RESOLUTION);
    temp.close();
    stack.push_back(temp);
    cp_stack.push_back(temp);
    
    fontWidth.push_back(alphabet[i].getWidth());
    
    counter++;
}

//--------------------------------------------------------------
void ofApp::reset(){
    stack.clear();
    cp_stack.clear();
    
    fontWidth.clear();
    
    counter = 0;
}

//--------------------------------------------------------------
void ofApp::del(){
    if(stack.size() > 0){
        stack.pop_back();
        cp_stack.pop_back();
        
        fontWidth.pop_back();
        
        counter--;
    }
}

//--------------------------------------------------------------
void ofApp::record(){
    b_record = true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case 'a':
            stackPolyline(0);
            break;
        case 'b':
            stackPolyline(1);
            break;
        case 'c':
            stackPolyline(2);
            break;
        case 'd':
            stackPolyline(3);
            break;
        case 'e':
            stackPolyline(4);
            break;
        case 'f':
            stackPolyline(5);
            break;
        case 'g':
            stackPolyline(6);
            break;
        case 'h':
            stackPolyline(7);
            break;
        case 'i':
            stackPolyline(8);
            break;
        case 'j':
            stackPolyline(9);
            break;
        case 'k':
            stackPolyline(10);
            break;
        case 'l':
            stackPolyline(11);
            break;
        case 'm':
            stackPolyline(12);
            break;
        case 'n':
            stackPolyline(13);
            break;
        case 'o':
            stackPolyline(14);
            break;
        case 'p':
            stackPolyline(15);
            break;
        case 'q':
            stackPolyline(16);
            break;
        case 'r':
            stackPolyline(17);
            break;
        case 's':
            stackPolyline(18);
            break;
        case 't':
            stackPolyline(19);
            break;
        case 'u':
            stackPolyline(20);
            break;
        case 'v':
            stackPolyline(21);
            break;
        case 'w':
            stackPolyline(22);
            break;
        case 'x':
            stackPolyline(23);
            break;
        case 'y':
            stackPolyline(24);
            break;
        case 'z':
            stackPolyline(25);
            break;
        case '-':
            del();
            break;
        case '[':
            reset();
            break;
        case ' ':
            record();
            break;
        case '1':
            showInfo = !showInfo;
            break;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
