#include "levelsystem.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// Setup for the level system class, assign default values to variables, load enemy animation images
//
LevelSystem::LevelSystem() {
	currentPhase = phaseOne;
	rateOfFire = 900;
	spriteSpeed = 4;
	spriteAmount = 4;
	emitterSpeed = 2;
	isInPhase = false;
	testForEndOfPhase = true;
	isGameOver = false;
	isIdle = true;
	isRandom = false;
	isWave = false;
	levelCounter = 1;

	ofDirectory allSpriteAnim("/images/monster");
	allSpriteAnim.listDir();
	for (int i = 0; i < allSpriteAnim.size(); i++) {
		ofImage spriteAnimImage;
		spriteAnimImage.load(allSpriteAnim.getPath(i));
		enemyEmitter1.spriteSystem.spriteAnim.push_back(spriteAnimImage);
		enemyEmitter2.spriteSystem.spriteAnim.push_back(spriteAnimImage);
		enemyEmitter3.spriteSystem.spriteAnim.push_back(spriteAnimImage);
		enemyEmitter4.spriteSystem.spriteAnim.push_back(spriteAnimImage);
		enemyEmitter5.spriteSystem.spriteAnim.push_back(spriteAnimImage);
		enemyEmitter6.spriteSystem.spriteAnim.push_back(spriteAnimImage);
	}
}

// Draws the enemy emitters and their sprites
// Draws the current level when phase one occurs
//
void LevelSystem::draw() {
	if (!isIdle) {
		if (!isGameOver) {
			if (currentPhase == phaseOne) {
				string levelCount = ofToString(levelCounter);
				string levelText = "Level " + levelCount;
				smallFont.drawString(
					levelText,
					(ofGetWidth() * 0.5) - (smallFont.stringWidth(levelText) / 2),
					(ofGetHeight() * 0.20)
				);
			}
			for (int i = 0; i < enemyEmitters.size(); i++) {
				enemyEmitters[i].draw();
			}
		}
	}
}

// Updates the enemy emitters and phases
//
void LevelSystem::update() {
	if (!enemyEmitters.empty()) {
		for (int i = 0; i < enemyEmitters.size(); i++) {
			if (isRandom) {
				enemyEmitters[i].setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitters[i].spriteWidth / 2, ofGetWidth() - +enemyEmitters[i].spriteWidth / 2), 0));
			}
			if (isWave) {
				if (!enemyEmitters[i].spriteSystem.sprites.empty()) {
					for (int j = 0; j < enemyEmitters[i].spriteSystem.sprites.size(); j++) {
						float sinOffset = sin(enemyEmitters[i].spriteSystem.sprites[j].sinCounter);
						enemyEmitters[i].spriteSystem.sprites[j].position.x += (sinOffset * 10);
						if (ofGetFrameNum() % 8 == 0) {
							enemyEmitters[i].spriteSystem.sprites[j].sinCounter++;
						}
					}
				}
			}
			enemyEmitters[i].update();
			testForEndOfPhase = testForEndOfPhase && 
								enemyEmitters[i].spriteSystem.sprites.empty() && 
								(enemyEmitters[i].spriteFireCounter == enemyEmitters[i].maxSpriteFireAmount);
		}
		if (testForEndOfPhase == false) {
			testForEndOfPhase = true;
		}
		else {
			clearPhase();
			switchPhase();
		}
	}

	getElapsedWaitTime();
	if (isInPhase || elapsedWaitTime < 1500) {
		return;
	}

	switch (currentPhase) {
	case phaseOne:
		runPhaseOne();
		break;
	case phaseTwo:
		runPhaseTwo();
		break;
	case phaseThree:
		runPhaseThree();
		break;
	}
	//cout << elapsedWaitTime << endl;
}

// Loads the font of the game
//
void LevelSystem::setFont(string path) {
	smallFont.load(path, 25);
}

// Phase one setup
//
void LevelSystem::runPhaseOne() {
	isInPhase = true;
	isRandom = true;

	enemyEmitter1.setEmitterSize(0, 0);
	enemyEmitter1.setEmitterSpeed(0);
	enemyEmitter1.setRateofFire(rateOfFire);
	enemyEmitter1.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter1.setSpriteName("enemies");
	enemyEmitter1.setSpriteSize(enemyEmitter1.spriteWidth * 0.5, enemyEmitter1.spriteHeight * 0.5);
	enemyEmitter1.setSpriteLifespan(100000);
	enemyEmitter1.setSpriteSpeed(spriteSpeed);
	enemyEmitter1.setSpriteVelocity(ofVec2f(0, 1));
	enemyEmitter1.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter1.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter1.spriteWidth / 2, ofGetWidth() - +enemyEmitter1.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter1);

	enemyEmitter2.setEmitterSize(0, 0);
	enemyEmitter2.setEmitterSpeed(0);
	enemyEmitter2.setRateofFire(rateOfFire);
	enemyEmitter2.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter2.setSpriteName("enemies");
	enemyEmitter2.setSpriteSize(enemyEmitter2.spriteWidth * 0.5, enemyEmitter2.spriteHeight * 0.5);
	enemyEmitter2.setSpriteLifespan(100000);
	enemyEmitter2.setSpriteSpeed(spriteSpeed);
	enemyEmitter2.setSpriteVelocity(ofVec2f(0, 1));
	enemyEmitter2.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter2.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter2.spriteWidth / 2, ofGetWidth() - +enemyEmitter2.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter2);

	enemyEmitter3.setEmitterSize(0, 0);
	enemyEmitter3.setEmitterSpeed(0);
	enemyEmitter3.setRateofFire(rateOfFire);
	enemyEmitter3.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter3.setSpriteName("enemies");
	enemyEmitter3.setSpriteSize(enemyEmitter3.spriteWidth * 0.5, enemyEmitter3.spriteHeight * 0.5);
	enemyEmitter3.setSpriteLifespan(100000);
	enemyEmitter3.setSpriteSpeed(spriteSpeed);
	enemyEmitter3.setSpriteVelocity(ofVec2f(0, 1));
	enemyEmitter3.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter3.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter3.spriteWidth / 2, ofGetWidth() - +enemyEmitter3.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter3);

	enemyEmitter4.setEmitterSize(0, 0);
	enemyEmitter4.setEmitterSpeed(0);
	enemyEmitter4.setRateofFire(rateOfFire);
	enemyEmitter4.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter4.setSpriteName("enemies");
	enemyEmitter4.setSpriteSize(enemyEmitter4.spriteWidth * 0.5, enemyEmitter4.spriteHeight * 0.5);
	enemyEmitter4.setSpriteLifespan(100000);
	enemyEmitter4.setSpriteSpeed(spriteSpeed);
	enemyEmitter4.setSpriteVelocity(ofVec2f(0, 1));
	enemyEmitter4.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter4.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter4.spriteWidth / 2, ofGetWidth() - +enemyEmitter4.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter4);

	enemyEmitter5.setEmitterSize(0, 0);
	enemyEmitter5.setEmitterSpeed(0);
	enemyEmitter5.setRateofFire(rateOfFire);
	enemyEmitter5.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter5.setSpriteName("enemies");
	enemyEmitter5.setSpriteSize(enemyEmitter5.spriteWidth * 0.5, enemyEmitter5.spriteHeight * 0.5);
	enemyEmitter5.setSpriteLifespan(100000);
	enemyEmitter5.setSpriteSpeed(spriteSpeed);
	enemyEmitter5.setSpriteVelocity(ofVec2f(0, 1));
	enemyEmitter5.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter5.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter5.spriteWidth / 2, ofGetWidth() - +enemyEmitter5.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter5);

	enemyEmitter6.setEmitterSize(0, 0);
	enemyEmitter6.setEmitterSpeed(0);
	enemyEmitter6.setRateofFire(rateOfFire);
	enemyEmitter6.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter6.setSpriteName("enemies");
	enemyEmitter6.setSpriteSize(enemyEmitter6.spriteWidth * 0.5, enemyEmitter6.spriteHeight * 0.5);
	enemyEmitter6.setSpriteLifespan(100000);
	enemyEmitter6.setSpriteSpeed(spriteSpeed);
	enemyEmitter6.setSpriteVelocity(ofVec2f(0, 1));
	enemyEmitter6.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter6.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter6.spriteWidth / 2, ofGetWidth() - +enemyEmitter6.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter6);

	for (int i = 0; i < enemyEmitters.size(); i++) {
		enemyEmitters[i].isIdle = false;
	}
}

// Phase two setup
//
void LevelSystem::runPhaseTwo() {
	isInPhase = true;
	isRandom = true;

	enemyEmitter1.setEmitterSize(0, 0);
	enemyEmitter1.setInitialEmitterPosition(ofVec2f((ofGetWidth() * 0.1) - (enemyEmitter1.width / 2), 0));
	enemyEmitter1.setEmitterSpeed(0);
	enemyEmitter1.setRateofFire(rateOfFire);
	enemyEmitter1.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter1.setSpriteName("enemies");
	enemyEmitter1.setSpriteSize(enemyEmitter1.spriteWidth * 0.5, enemyEmitter1.spriteHeight * 0.5);
	enemyEmitter1.setSpriteLifespan(100000);
	enemyEmitter1.setSpriteSpeed(spriteSpeed);
	enemyEmitter1.setSpriteVelocity(ofVec2f(1, 0.6));
	enemyEmitter1.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitters.push_back(enemyEmitter1);

	enemyEmitter2.setEmitterSize(0, 0);
	enemyEmitter2.setInitialEmitterPosition(ofVec2f((ofGetWidth() * 0.2) - (enemyEmitter2.width / 2), 0));
	enemyEmitter2.setEmitterSpeed(0);
	enemyEmitter2.setRateofFire(rateOfFire);
	enemyEmitter2.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter2.setSpriteName("enemies");
	enemyEmitter2.setSpriteSize(enemyEmitter2.spriteWidth * 0.5, enemyEmitter2.spriteHeight * 0.5);
	enemyEmitter2.setSpriteLifespan(100000);
	enemyEmitter2.setSpriteSpeed(spriteSpeed);
	enemyEmitter2.setSpriteVelocity(ofVec2f(1, 0.6));
	enemyEmitter2.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitters.push_back(enemyEmitter2);

	enemyEmitter3.setEmitterSize(0, 0);
	enemyEmitter3.setInitialEmitterPosition(ofVec2f((ofGetWidth() * 0.3) - (enemyEmitter3.width / 2), 0));
	enemyEmitter3.setEmitterSpeed(0);
	enemyEmitter3.setRateofFire(rateOfFire);
	enemyEmitter3.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter3.setSpriteName("enemies");
	enemyEmitter3.setSpriteSize(enemyEmitter3.spriteWidth * 0.5, enemyEmitter3.spriteHeight * 0.5);
	enemyEmitter3.setSpriteLifespan(100000);
	enemyEmitter3.setSpriteSpeed(spriteSpeed);
	enemyEmitter3.setSpriteVelocity(ofVec2f(1, 0.6));
	enemyEmitter3.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitters.push_back(enemyEmitter3);

	enemyEmitter4.setEmitterSize(0, 0);
	enemyEmitter4.setInitialEmitterPosition(ofVec2f((ofGetWidth() * 0.7) - (enemyEmitter4.width / 2), 0));
	enemyEmitter4.setEmitterSpeed(0);
	enemyEmitter4.setRateofFire(rateOfFire);
	enemyEmitter4.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter4.setSpriteName("enemies");
	enemyEmitter4.setSpriteSize(enemyEmitter4.spriteWidth * 0.5, enemyEmitter4.spriteHeight * 0.5);
	enemyEmitter4.setSpriteLifespan(100000);
	enemyEmitter4.setSpriteSpeed(spriteSpeed);
	enemyEmitter4.setSpriteVelocity(ofVec2f(-1, 0.6));
	enemyEmitter4.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitters.push_back(enemyEmitter4);

	enemyEmitter5.setEmitterSize(0, 0);
	enemyEmitter5.setInitialEmitterPosition(ofVec2f((ofGetWidth() * 0.8) - (enemyEmitter5.width / 2), 0));
	enemyEmitter5.setEmitterSpeed(0);
	enemyEmitter5.setRateofFire(rateOfFire);
	enemyEmitter5.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter5.setSpriteName("enemies");
	enemyEmitter5.setSpriteSize(enemyEmitter5.spriteWidth * 0.5, enemyEmitter5.spriteHeight * 0.5);
	enemyEmitter5.setSpriteLifespan(100000);
	enemyEmitter5.setSpriteSpeed(spriteSpeed);
	enemyEmitter5.setSpriteVelocity(ofVec2f(-1, 0.6));
	enemyEmitter5.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitters.push_back(enemyEmitter5);

	enemyEmitter6.setEmitterSize(0, 0);
	enemyEmitter6.setInitialEmitterPosition(ofVec2f((ofGetWidth() * 0.9) - (enemyEmitter6.width / 2), 0));
	enemyEmitter6.setEmitterSpeed(0);
	enemyEmitter6.setRateofFire(rateOfFire);
	enemyEmitter6.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter6.setSpriteName("enemies");
	enemyEmitter6.setSpriteSize(enemyEmitter6.spriteWidth * 0.5, enemyEmitter6.spriteHeight * 0.5);
	enemyEmitter6.setSpriteLifespan(100000);
	enemyEmitter6.setSpriteSpeed(spriteSpeed);
	enemyEmitter6.setSpriteVelocity(ofVec2f(-1, 0.6));
	enemyEmitter6.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitters.push_back(enemyEmitter6);

	for (int i = 0; i < enemyEmitters.size(); i++) {
		enemyEmitters[i].isIdle = false;
	}
}

// Phase three setup
//
void LevelSystem::runPhaseThree() {
	isInPhase = true;
	isWave = true;
	isRandom = true;

	enemyEmitter1.setEmitterSize(0, 0);
	enemyEmitter1.setEmitterSpeed(0);
	enemyEmitter1.setRateofFire(rateOfFire);
	enemyEmitter1.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter1.setSpriteName("enemies");
	enemyEmitter1.setSpriteSize(enemyEmitter1.spriteWidth * 0.5, enemyEmitter1.spriteHeight * 0.5);
	enemyEmitter1.setSpriteLifespan(100000);
	enemyEmitter1.setSpriteSpeed(spriteSpeed);
	enemyEmitter1.setSpriteVelocity(ofVec2f(0, 0.8));
	enemyEmitter1.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter1.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter1.spriteWidth / 2, ofGetWidth() - +enemyEmitter1.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter1);

	enemyEmitter2.setEmitterSize(0, 0);
	enemyEmitter2.setEmitterSpeed(0);
	enemyEmitter2.setRateofFire(rateOfFire);
	enemyEmitter2.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter2.setSpriteName("enemies");
	enemyEmitter2.setSpriteSize(enemyEmitter2.spriteWidth * 0.5, enemyEmitter2.spriteHeight * 0.5);
	enemyEmitter2.setSpriteLifespan(100000);
	enemyEmitter2.setSpriteSpeed(spriteSpeed);
	enemyEmitter2.setSpriteVelocity(ofVec2f(0, 0.8));
	enemyEmitter2.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter2.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter2.spriteWidth / 2, ofGetWidth() - +enemyEmitter2.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter2);

	enemyEmitter3.setEmitterSize(0, 0);
	enemyEmitter3.setEmitterSpeed(0);
	enemyEmitter3.setRateofFire(rateOfFire);
	enemyEmitter3.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter3.setSpriteName("enemies");
	enemyEmitter3.setSpriteSize(enemyEmitter3.spriteWidth * 0.5, enemyEmitter3.spriteHeight * 0.5);
	enemyEmitter3.setSpriteLifespan(100000);
	enemyEmitter3.setSpriteSpeed(spriteSpeed);
	enemyEmitter3.setSpriteVelocity(ofVec2f(0, 0.8));
	enemyEmitter3.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter3.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter3.spriteWidth / 2, ofGetWidth() - +enemyEmitter3.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter3);

	enemyEmitter4.setEmitterSize(0, 0);
	enemyEmitter4.setEmitterSpeed(0);
	enemyEmitter4.setRateofFire(rateOfFire);
	enemyEmitter4.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter4.setSpriteName("enemies");
	enemyEmitter4.setSpriteSize(enemyEmitter4.spriteWidth * 0.5, enemyEmitter4.spriteHeight * 0.5);
	enemyEmitter4.setSpriteLifespan(100000);
	enemyEmitter4.setSpriteSpeed(spriteSpeed);
	enemyEmitter4.setSpriteVelocity(ofVec2f(0, 0.8));
	enemyEmitter4.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter4.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter4.spriteWidth / 2, ofGetWidth() - +enemyEmitter4.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter4);

	enemyEmitter5.setEmitterSize(0, 0);
	enemyEmitter5.setEmitterSpeed(0);
	enemyEmitter5.setRateofFire(rateOfFire);
	enemyEmitter5.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter5.setSpriteName("enemies");
	enemyEmitter5.setSpriteSize(enemyEmitter5.spriteWidth * 0.5, enemyEmitter5.spriteHeight * 0.5);
	enemyEmitter5.setSpriteLifespan(100000);
	enemyEmitter5.setSpriteSpeed(spriteSpeed);
	enemyEmitter5.setSpriteVelocity(ofVec2f(0, 0.8));
	enemyEmitter5.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter5.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter5.spriteWidth / 2, ofGetWidth() - +enemyEmitter5.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter5);

	enemyEmitter6.setEmitterSize(0, 0);
	enemyEmitter6.setEmitterSpeed(0);
	enemyEmitter6.setRateofFire(rateOfFire);
	enemyEmitter6.setSpriteImage("/images/monster/monster1.png");
	enemyEmitter6.setSpriteName("enemies");
	enemyEmitter6.setSpriteSize(enemyEmitter6.spriteWidth * 0.5, enemyEmitter6.spriteHeight * 0.5);
	enemyEmitter6.setSpriteLifespan(100000);
	enemyEmitter6.setSpriteSpeed(spriteSpeed);
	enemyEmitter6.setSpriteVelocity(ofVec2f(0, 0.8));
	enemyEmitter6.setMaxSpriteFireAmount(spriteAmount);
	enemyEmitter6.setInitialEmitterPosition(ofVec2f(ofRandom(0 + enemyEmitter6.spriteWidth / 2, ofGetWidth() - +enemyEmitter6.spriteWidth / 2), 0));
	enemyEmitters.push_back(enemyEmitter6);

	for (int i = 0; i < enemyEmitters.size(); i++) {
		enemyEmitters[i].isIdle = false;
	}
}

// Gets the wait time for transition period between phases
//
void LevelSystem::getElapsedWaitTime() {
	elapsedWaitTime = ofGetSystemTimeMillis() - endOfPhaseTime;
}

// Switches the current phase to the next phase
// If last phase, increase difficulty
//
void LevelSystem::switchPhase() {
	if (currentPhase == phaseOne) {
		currentPhase = phaseTwo;
	}
	else if (currentPhase == phaseTwo) {
		currentPhase = phaseThree;
	}
	else if (currentPhase == phaseThree) {
		levelCounter++;
		if (rateOfFire > 500) {
			rateOfFire = rateOfFire - 100; //50
			spriteSpeed = spriteSpeed + 0.5; //0.1
			spriteAmount = spriteAmount + 2; //2
			emitterSpeed = emitterSpeed + 2; //0.5
		}
		else {
			spriteSpeed = spriteSpeed + 0.5; //0.1
			spriteAmount = spriteAmount + 2; //2
			emitterSpeed = emitterSpeed + 2; //0.5
		}
		currentPhase = phaseOne;
	}
}

// After a phase is over, empty out enemy emitters vector and start transition timer
//
void LevelSystem::clearPhase() {
	enemyEmitters.clear();
	isInPhase = false;
	isRandom = false;
	isWave = false;
	endOfPhaseTime = ofGetSystemTimeMillis();
}

// Resets game start conditions
//
void LevelSystem::resetGame() {
	clearPhase();
	currentPhase = phaseOne;
	rateOfFire = 900;
	spriteSpeed = 3;
	spriteAmount = 4;
	emitterSpeed = 2;
	levelCounter = 1;
	endOfPhaseTime = 0;
	isGameOver = false;
	isIdle = true;
	isRandom = false;
	isWave = false;
}
