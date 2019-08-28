#include "ofxDisplay.h"

ofxDisplay::ofxDisplay(ofVec2f size) {
	setSize(size);
	volVerts[0] = ofVec2f(size.x / 2.0, size.y / 2.0);
	volVerts[1] = ofVec2f(-size.x / 2.0, size.y / 2.0);
	volVerts[2] = ofVec2f(-size.x / 2.0, -size.y / 2.0);
	volVerts[3] = ofVec2f(size.x / 2.0, -size.y / 2.0);


	texVerts[0] = ofVec2f(1.0, 1.0);
	texVerts[1] = ofVec2f(0.0, 1.0);
	texVerts[2] = ofVec2f(0.0, 0.0);
	texVerts[3] = ofVec2f(1.0, 0.0);
}

void ofxDisplay::init(int w, int h) {
	volVerts[0] = ofVec2f(w/2.0, h/2.0);
	volVerts[1] = ofVec2f(-w/2.0, h/2.0);
	volVerts[2] = ofVec2f(-w/2.0, -h/2.0);
	volVerts[3] = ofVec2f(w/2.0, -h/2.0);

	
	texVerts[0] = ofVec2f(1.0, 1.0);
	texVerts[1] = ofVec2f(0.0, 1.0);
	texVerts[2] = ofVec2f(0.0, 0.0);
	texVerts[3] = ofVec2f(1.0, 0.0);
}

void ofxDisplay::setScale(ofVec2f s) {
	setSize(s);
	volVerts[0] = ofVec2f(size.x / 2.0, size.y / 2.0);
	volVerts[1] = ofVec2f(-size.x / 2.0, size.y / 2.0);
	volVerts[2] = ofVec2f(-size.x / 2.0, -size.y / 2.0);
	volVerts[3] = ofVec2f(size.x / 2.0, -size.y / 2.0);
}


void ofxDisplay::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, sizeof(ofVec2f), volVerts);
	glTexCoordPointer(2, GL_FLOAT, sizeof(ofVec2f), texVerts);
	
	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}