#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);

	ofImage image;
	image.loadImage("image/crown.png");

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	image.draw(-image.getWidth() * 0.5, -image.getHeight() * 0.5);

	this->fbo.end();

	ofPixels pixels;
	this->fbo.readToPixels(pixels);

	int span = 15;
	for (int x = 0; x < this->fbo.getWidth(); x += span) {

		for (int y = 0; y < this->fbo.getHeight(); y += span) {

			if (pixels.getColor(x, y).a != 0) {

				this->locations.push_back(ofPoint(x - span * 0.5, y - span * 0.5));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (ofPoint location : this->locations) {

		float noise_seed = ofRandom(100);

		ofColor color;
		color.setHsb(ofNoise(noise_seed, ofGetFrameNum() * 0.05) * 255, 200, 255);
		ofSetColor(color);


		ofDrawRectangle(location, 10, 10);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}