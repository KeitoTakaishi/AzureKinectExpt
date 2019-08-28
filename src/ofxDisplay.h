#pragma once
#include "ofMain.h"

class ofxDisplay {
public:
	ofxDisplay();
	ofxDisplay(ofVec2f s);
	~ofxDisplay();
	void init(int w, int h);
	void setScale(ofVec2f s);
	void draw();

	void setSize(ofVec2f s) {
		size = s;
	}

	ofVec2f getSize() {
		return this->size;
	}
private:
	ofVec2f size;
	ofVec2f volVerts[4];
	ofVec2f texVerts[4];
};