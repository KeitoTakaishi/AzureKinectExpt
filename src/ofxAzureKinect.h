#pragma once

#include <k4a/k4a.h>
#include <k4a/k4a.hpp>
#include "ofMain.h"
#include "ofxTexture.h"
#include "ofxDisplay.h"

class ofxAzureKinect
{
public:
	ofxAzureKinect();
	~ofxAzureKinect();

	//texture‚Ì—pˆÓ
	void init();
	//camera start, opne
	bool open();
	void captureImage();
	void captureDepth();
	void preview();
	//write pixle data
	void recorder(string path, ofVec2f res, int ch, uint8_t* pixles);

	void reloadShader();

	ofxDisplay*  colorDisplay;
	ofxDisplay*  depthDisplay;
private:
	uint32_t deviceCount;
	k4a_device_t device;
	const int32_t TIMEOUT_IN_MS = 1000;
	k4a_device_configuration_t config;
	k4a_capture_t capture;

	k4a_image_t color_image;
	k4a_image_t depth_image;
	
	bool isRecored;

	ofxTexture* imageTexture;
	//ofxDisplay*  colorDisplay;
	//ofxDisplay*  depthDisplay;
	ofShader shader;
	ofEasyCam cam;
};

