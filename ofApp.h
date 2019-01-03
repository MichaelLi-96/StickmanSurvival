#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "background.h"
#include "emitter.h"
#include "levelsystem.h"
#include "sprite.h"
#include "spritesystem.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "ParticleSystem.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// ofApp class to declare built in OpenFramework functions, include header files from other classes, and to initialize class objects
//
	class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void loadVbo();

		ofImage cursor;
		ofSoundPlayer hitSound;
		Background background;
		Emitter mainEmitter;
		LevelSystem levelSystem;

		ParticleEmitter particleEmitter;
		ofTexture  particleTex;
		ofVbo vbo;
		ofShader shader;
		vector<ofColor> colors;
};