#include "ofApp.h"
#include "ofxCTHD512.h"


//--------------------------------------------------------------
void ofApp::setup(){
	table.init("cue.xml");
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	table.drawGUI(0, 0);
	table.drawCue(200, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
