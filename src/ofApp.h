#pragma once


#include "ofMain.h"
#include<fstream>
#include <Windows.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>
#include "ofxTexture.h"
#include "ofxDisplay.h"
#include "ofxAzureKinect.h"

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void exit();

		ofxAzureKinect* kinect;
		ofVec2f scale = ofVec2f(1020, 720);
};
	
