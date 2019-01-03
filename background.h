#pragma once
#include "ofMain.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// A Background class to display a background of an image
//
class Background {
public:
	Background();
	ofImage backgroundImage;
	ofImage backgroundHurtImage;
	ofImage lifeImage;
	ofTrueTypeFont titleFont;
	ofTrueTypeFont bigFont;
	ofTrueTypeFont smallFont;
	ofSoundPlayer music;
	string scoreTitle;
	int score;
	int mainEmitterMaxLife;
	int mainEmitterCurrentLife;
	int hurtFrameTimer;
	float width;
	float height;
	bool hasLifeImage;
	bool hasBackgroundHurtImage;
	bool isHurt;
	bool isIdle;
	bool isGameOver;

	void draw();
	void update();
	void setBackgroundImage(string path);
	void setBackgroundHurtImage(string path);
	void setLifeImage(string path);
	void setFont(string path);
	void setMusic(string path);
	void getMainEmitterMaxLife(int lifeTotal);
	void resetGame();
};
