#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(30);
	kinect = new ofxAzureKinect();
	kinect->init();
	kinect->open();
}

//--------------------------------------------------------------
void ofApp::update(){
	//kinect->captureImage();
	kinect->captureDepth();
}

//--------------------------------------------------------------
void ofApp::draw(){
	kinect->preview();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		kinect->reloadShader();
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	delete kinect;
}