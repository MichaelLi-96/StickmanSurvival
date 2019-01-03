#pragma once
#include "emitter.h"
#include "ofMain.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

typedef enum { phaseOne, phaseTwo, phaseThree } Phase;

// A LevelSystem class to control the levels of the game
// Initializes 6 possible enemy emitters
//
class LevelSystem {
public:
	LevelSystem();
	vector<Emitter> enemyEmitters;
	Phase currentPhase;
	float elapsedWaitTime;
	float endOfPhaseTime;
	int levelCounter;
	int rateOfFire;
	double spriteSpeed;
	int spriteAmount;
	int emitterSpeed;
	ofTrueTypeFont smallFont;
	bool isInPhase;
	bool testForEndOfPhase;
	bool isGameOver;
	bool isIdle;
	bool isRandom;
	bool isWave;

	void draw();
	void update();
	void setFont(string path);
	void runPhaseOne();
	void runPhaseTwo();
	void runPhaseThree();
	void getElapsedWaitTime();
	void switchPhase();
	void clearPhase();
	void resetGame();

	Emitter enemyEmitter1;
	Emitter enemyEmitter2;
	Emitter enemyEmitter3;
	Emitter enemyEmitter4;
	Emitter enemyEmitter5;
	Emitter enemyEmitter6;
};
