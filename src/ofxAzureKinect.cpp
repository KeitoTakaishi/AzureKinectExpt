#include "ofxAzureKinect.h"



ofxAzureKinect::ofxAzureKinect()
{
	ofLogVerbose("ofxKinect") << " creating ofxKinect";
	deviceCount = 0;
	device = NULL;
	capture = NULL;
	std::cout << "RecoredOption : Yes:0, Mo:1 " << std::endl;
	cin >> isRecored;
	isUpload = false;
}


ofxAzureKinect::~ofxAzureKinect()
{
	k4a_device_close(device);
}

void ofxAzureKinect::init() {
	//confif setting
	this->config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	this->config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
	this->config.color_resolution = K4A_COLOR_RESOLUTION_720P;
	this->config.camera_fps = K4A_FRAMES_PER_SECOND_30;

	//image texture
	this->colorTexture = new ofxTexture();
	this->colorTexture->showInfo();
	

	//display
	this->colorDisplay = new ofxDisplay(ofVec2f(1280, 720));
	
	//shader
	shader.load("shadersGL2/shader");
}


void ofxAzureKinect::selectDepthMode(DepthCameraMode depthMode) {
	this->depthCameraMode = depthMode;

	switch (this->depthCameraMode)
	{
	case DEPTH_MODE_NFOV_2X2BINNED:
		this->config.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
		this->depthDisplay = new ofxDisplay(ofVec2f(320, 288));
		break;
	case DEPTH_MODE_NFOV_UNBINNED:
		this->config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
		this->depthDisplay = new ofxDisplay(ofVec2f(640, 576));
		break;
	case DEPTH_MODE_WFOV_2X2BINNED:
		this->config.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
		this->depthDisplay = new ofxDisplay(ofVec2f(512, 512));
		break;
	case DEPTH_MODE_WFOV_UNBINNED:
		cout << "DepthMode : " << "K4A_DEPTH_MODE_WFOV_UNBINNED" << endl;
		this->config.depth_mode = K4A_DEPTH_MODE_WFOV_UNBINNED;
		this->depthDisplay = new ofxDisplay(ofVec2f(1024, 1024));
		break;
	}
	
}

bool ofxAzureKinect::open() {
	deviceCount = k4a_device_get_installed_count();
	if (deviceCount == 0) {
		std::cout << "No Device installed" << std::endl;
		return 0;
	}
	std::cout << "DeviceCount : " << deviceCount << endl;


	//device open
	if (K4A_RESULT_SUCCEEDED != k4a_device_open(K4A_DEVICE_DEFAULT, &device)) {
		std::cout << "Failed to Open device" << endl;
		return 0;
	}

	//camera start
	if (K4A_RESULT_SUCCEEDED != k4a_device_start_cameras(device, &config))
	{
		std::cout << "Failed to Start device" << std::endl;
		return 0;
	}

	std:cout << "Open Devicce" << std::endl;
	return true;
}


void ofxAzureKinect::captureImage(){
	k4a_device_get_capture(device, &capture, TIMEOUT_IN_MS);
	color_image = k4a_capture_get_color_image(capture);

	if (color_image) {
		//std::cout << "Image Info" << std::endl;
		ofVec2f res = ofVec2f(k4a_image_get_width_pixels(color_image), k4a_image_get_height_pixels(color_image));
		//cout << "w : " << res.x << ", " << "h :" << res.y << endl;
		uint8_t *pixles = k4a_image_get_buffer(color_image);
		
		if (pixles == nullptr) {
			cout << "could't get pixel data" << endl;
		}

		if (!isRecored) {
			recorder("Recored.txt", res, 4, pixles);
			isRecored = true;
		}

		if (!isUpload) {
			colorTexture->Upload(pixles, res.x, res.y, 4, 0);
			isUpload = true;
		}
		else {
			colorTexture->Update(pixles, res.x, res.y, 0);
		}
		k4a_image_release(color_image);
		k4a_capture_release(capture);
	}
}

void ofxAzureKinect::captureDepth() {
	
	
	if (k4a_device_get_capture(device, &capture, TIMEOUT_IN_MS) == K4A_WAIT_RESULT_SUCCEEDED) {
		depth_image = k4a_capture_get_depth_image(capture);
		if (depth_image) {
			ofVec2f res = ofVec2f(k4a_image_get_width_pixels(depth_image), k4a_image_get_height_pixels(depth_image));
			std::cout << "DepthImage : " << res.x << ", " << res.y << endl;

			uint8_t *pixles = k4a_image_get_buffer(depth_image);

			if (pixles == nullptr) {
				cout << "could't get pixel data" << endl;
			}
			if (!isRecored) {
				recorder("Recored.txt", res, 4, pixles);
				isRecored = true;
			}
			if (!isUpload) {
				colorTexture->Upload(pixles, res.x, res.y, 4, 1);
				isUpload = true;
			}
			else {
				colorTexture->Upload(pixles, res.x, res.y, 4, 1);
				//colorTexture->Update(pixles, res.x, res.y, 1);
			}
			k4a_capture_release(capture);
		}
		else {
			cout << "failed to capture depth image" << endl;
		}
		k4a_image_release(depth_image);
	}
	
}

void ofxAzureKinect::preview() {
	cam.begin();
	//cam.disableMouseInput();
	shader.begin();
	shader.setUniform1f("tex0", 1);

	ofPushMatrix();
	depthDisplay->draw();
	ofPopMatrix();
	//colorDisplay->draw();
	shader.end();
	cam.end();
}

void ofxAzureKinect::recorder(string path, ofVec2f res, int ch, uint8_t* pixles) {
	int pixleNum = res.x*res.y*ch;
	ofstream fout;
	fout.open(path, ios::out | ios::binary | ios::trunc);
	for (int i = 0; i < pixleNum; i++) {
		fout << (int)pixles[i];
		fout << ",";
		if ((i + 1) % 4 == 0) {
			fout << "\n";
		}
	}
	cout << "closed" << endl;
	fout.close();
}


void ofxAzureKinect::reloadShader() {
	shader.load("shadersGL2/shader");
}