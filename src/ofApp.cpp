#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(30);
	kinect = new ofxAzureKinect();
	kinect->init();
	int depthMode;
	cout << "please select depthMode" << endl;
	cout << "containts" << endl;
	cout << "NFOV_2X2BINNE : 0, NFOV_UNBINNE : 1, WFOV_2X2BINNED : 2, WFOV_UNBINNED : 3" << endl;
	cin >> depthMode;
	kinect->selectDepthMode((ofxAzureKinect::DepthCameraMode)depthMode);
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