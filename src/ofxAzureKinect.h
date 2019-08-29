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

	enum DepthCameraMode {
		DEPTH_MODE_NFOV_2X2BINNED = 0,
		DEPTH_MODE_NFOV_UNBINNED = 1,
		DEPTH_MODE_WFOV_2X2BINNED = 2,
		DEPTH_MODE_WFOV_UNBINNED = 3,
		//K4A_DEPTH_MODE_PASSIVE_IR = 4,
	};

	//texture‚Ì—pˆÓ
	void init();
	//depth mode ‚Ì‘I‘ð
	void selectDepthMode(DepthCameraMode depthMode);
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


	//accessor

	
private:
	uint32_t deviceCount;
	k4a_device_t device;
	DepthCameraMode depthCameraMode;
	const int32_t TIMEOUT_IN_MS = 1000;
	k4a_device_configuration_t config;
	k4a_capture_t capture;


	k4a_image_t color_image;
	k4a_image_t depth_image;
	
	bool isRecored;
	bool isUpload;


	ofxTexture* colorTexture;// for colorTexture
	
	ofShader shader;
	ofEasyCam cam;
};

