#pragma once
#include "ofMain.h"
#include "spritesystem.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

// General purpose Emitter class for emitting sprites; particle emitter
//
class Emitter {
public:
	Emitter();
	SpriteSystem spriteSystem;
	MoveDir moveDirection;
	vector<ofImage> upAnim;
	vector<ofImage> downAnim;
	vector<ofImage> leftAnim;
	vector<ofImage> rightAnim;
	ofImage emitterImage;
	ofImage spriteImage;
	ofVec2f startingPoint;
	ofVec2f position;
	ofVec2f spriteVelocity;
	ofSoundPlayer fireSound;
	string spriteName;
	float width, height; // (px)
	float speed; // (px per frame)
	float spriteLifespan; // (millisec)
	float spriteWidth, spriteHeight; // (px)
	float spriteSpeed; // (px per frame)
	float rateOfFire; // (millisec btwn each shot)
	float rotationDegree; // (degrees rotated per frame)
	int animSequence;
	int spriteFireCounter;
	int maxSpriteFireAmount;
	int maxLife;
	int xLengthToImageOrigin;
	int yLengthToImageOrigin;
	bool isMainEmitter;
	bool hasImage;
	bool hasSpriteImage;
	bool isPressed;
	bool isIdle;
	bool isGameOver;
	bool fire;

	void draw();
	void update();
	void addSprite();
	void move(MoveDir dir);
	void setAsMainEmitter();
	void setEmitterImage(string path);
	void updateAnimSequence(vector<ofImage> anim, int animPerFrames);
	void setEmitterSize(float width, float height);
	void setInitialEmitterPosition(ofVec2f startingPoint);
	void setMaxLife(int maxLife);
	void setEmitterSpeed(float speed);
	void setRotationDegree(float rotationDegree);
	void setRateofFire(float rateOfFire);
	void setFireSound(string path);
	void setSpriteImage(string path);
	void setSpriteName(string spriteName);
	void setSpriteSize(float spriteWidth, float spriteHeight);
	void setSpriteLifespan(float spriteLifespan);
	void setSpriteVelocity(ofVec2f spriteVelocity);
	void setSpriteSpeed(float spriteSpeed);
	void setMaxSpriteFireAmount(int maxSpriteFireAmount);
	void resetGame();
	bool inside(int x, int y);
};