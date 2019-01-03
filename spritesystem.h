#pragma once
#include "ofMain.h"
#include "sprite.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

//  Dynamically manages all Sprites in a system using a vector
//
class SpriteSystem {
public:
	vector<Sprite> sprites;
	vector<ofImage> spriteAnim;
	int animSequence;
	bool reverseAnim;
	bool isMainEmitter;

	void add(Sprite spriteObj);
	void remove(int index);
	void update();
	void draw();
};