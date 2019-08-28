#include "ofxTexture.h"

ofxTexture::ofxTexture() {
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(2, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void ofxTexture::DebugTexture(int w, int h, int ch) {
	unsigned char *pixels;
	ofVec3f size = ofVec3f(w, h, 1);
	int num = size.x*size.y*size.z*ch;
	pixels = new unsigned char[num];
	for (int z = 0; z < size.z; z++) {
		for (int y = 0; y < size.y; y++) {
			for (int x = 0; x < size.x; x++) {
				int index = (x + y * size.x + z * size.x*size.y) * ch;
				pixels[index] = 255*x/w;
				pixels[index + 1] = 0.0;
				pixels[index + 2] = 255 * y/h;
				//pixels[index + 3] = 255.0;
			}
		}
	}
	if (ch == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	}
	else if(ch == 4){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<unsigned char*> (pixels));
}

void ofxTexture::Upload(uint8_t* data, int w, int h, int ch, int textureMode) {
	uint8_t *pixels;
	unsigned short *depth;
	ofVec2f size = ofVec2f(w, h);
	
	if (textureMode == 0) {
		int num = w * h * 4;
		pixels = new uint8_t[num];
		for (int y = 0; y < 720; y++) {
			for (int x = 0; x < 1280; x++) {
				int index = (x + y * w) * 4;
				//bgra
				pixels[index] = data[index + 2];
				pixels[index + 1] = data[index + 1];
				pixels[index + 2] = data[index];
				pixels[index + 3] = 255.0;
			}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<unsigned char*>(pixels));
	}

	//depth
	/*
	else if (textureMode == 1) {
		int num = w * h * 2;
		pixels = new uint8_t[num];
		int offSet = 0;
		for (int y = 0; y < 512; y++) {
			for (int x = 0; x < 512; x++) {
				int index = (x + y * w) * 2;
				int _index = (x + y * w) * 2;

				
				if (debug % 1000 == 0) {
					std::cout << unsigned(data[index]) << std::endl;
					std::cout << unsigned(data[index + 1]) << std::endl;
				}

				pixels[index] = data[_index + 1];
				pixels[index + 1] = data[_index];
				//pixels[index + 2] = 0.0;
				//pixels[index + 3] = 0.0;
			}
			debug++;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R16, w, h, 0, GL_RG, GL_UNSIGNED_BYTE, reinterpret_cast<unsigned char*>(pixels));
	}
	*/
	
	else if (textureMode == 1) {
		int num = w * h * 1;
		depth = new unsigned short[num];
		int offSet = 0;
		for (int y = 0; y < 512; y++) {
			for (int x = 0; x < 512; x++) {
				int index = (x + y * w) * 2;
				int ind = (x + y * w);
				//low data[index], up data[index + 1]
				unsigned short depth16 = (unsigned short)data[index];
				unsigned short depth16up = (unsigned short)data[index + 1];
				depth16up = depth16up << 8;
				depth16 = (depth16 | depth16up);
				depth[ind] = depth16;
			}
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, depth);
	}
	
}


void ofxTexture::Update(uint8_t* data, int w, int h) {
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_BGRA, GL_UNSIGNED_BYTE, data);
	//glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,w,h,GL_RGB,GL_UNSIGNED_BYTE,reinterpret_cast<unsigned char*> (data)); 
}


void ofxTexture::showInfo() {
	cout << "texID : " << texID << endl;	
}