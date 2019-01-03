#pragma once
#include "ofMain.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// General purpose Sprite class (similar to a Particle)
//
class Sprite {
public:
	ofImage image;
	ofVec2f velocity;
	ofVec2f position;
	string name;
	float birthtime;
	float lifespan;
	float width;
	float height;
	float speed;
	float rotationDegree;
	int sinCounter;
	bool hasImage;

	float age();
	void imageRotate();
	void draw();
};
