#pragma once

#include "ofMain.h"
#include "ofxPDF.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    static const int NUM = 26;
    static const int RESOLUTION = 300;
    ofxPDF alphabet[NUM];
    vector<ofPolyline> polyline[NUM];   //raw data
    vector<ofPolyline> stack, cp_stack, passage;
    vector<float> fontWidth;
    
    int counter;
    
    void stackPolyline(int i);

    void melt();
    
    void reset();
    void del();
    
    void record();
    bool b_record;
    int record_counter;
    
    //gui
    ofxPanel gui;
    ofxFloatSlider sp_side, sp_down, scale;
    bool showInfo;
    
};
