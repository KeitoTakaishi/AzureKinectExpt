#pragma once

#include "ofMain.h"

class ofxTexture {
public:
	ofxTexture();
	~ofxTexture() {
		glDeleteTextures(1, &texID);
	}

	void DebugTexture(int w, int h, int ch);
	void Upload(uint8_t* data, int w, int h, int ch, int textureMode);

	void Update(uint8_t* data, int w, int h);
	

	void showInfo();
	GLuint* getTexID;

private:
	unsigned char *pixels;
	GLuint texID;

	int debug = 0;
};