#include "sprite.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// Returns the current age of the sprite
//
float Sprite::age() {
	return (ofGetSystemTimeMillis() - birthtime);
};

// Rotates the sprite only once when it is first drawn to the position of the mouse
//
void Sprite::imageRotate() {
	float num = floor(rotationDegree / 90);
	float remainder = fmod(rotationDegree, 90) / 90;
	float total = num + remainder;
	image.rotate90(total);
}

// Draws the sprite in the middle of the emitter
// If the image path is supplied draw the image, else draw a rectangle
//
void Sprite::draw() {
	if (hasImage) {
		image.draw(position.x, position.y, width, height);
	}
	else {
		ofDrawRectangle(position.x, position.y, width, height);
	}
};
