#include "background.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// Setup for a background object, assign default values to variables
//
Background::Background() {
	width = ofGetWidth();
	height = ofGetHeight();
	scoreTitle = "Score: ";
	score = 0;
	hurtFrameTimer = 0;
	hasLifeImage = false;
	hasBackgroundHurtImage = false;
	isHurt = false;
	isIdle = true;
	isGameOver = false;
}

// Draw the background with the width and height of the window, draws hurt background when main emitter is hurt
// If idle draws the idle screen, else draws the score title on the top left corner
//
void Background::draw() {
	if (isHurt) {
		backgroundHurtImage.draw(0, 0, width, height);
	}
	else {
		backgroundImage.draw(0, 0, width, height);
	}

	if (!isGameOver) {
		if (isIdle) {
			titleFont.drawString(
				"Stickman Survival",
				(width / 2) - (titleFont.stringWidth("Stickman Survival") / 2),
				(height * 0.35) - titleFont.stringHeight("Stickman Survival")
			);
			bigFont.drawString(
				"Press Space to Begin!",
				(width / 2) - (bigFont.stringWidth("Press Space to Begin!") / 2),
				(height / 2) - bigFont.stringHeight("Press Space to Begin!")
			);
			smallFont.drawString(
				"WASD or Arrow Keys to Move",
				(width / 2) - (smallFont.stringWidth("WASD or Arrow Keys to Move") / 2),
				(height / 2)
			);
			smallFont.drawString(
				"Mouse Click or Space to Shoot",
				(width / 2) - (smallFont.stringWidth("Mouse Click or Space to Shoot") / 2),
				(height / 2) + 50
			);
			smallFont.drawString(
				"Mouse to Aim",
				(width / 2) - (smallFont.stringWidth("Mouse to Aim") / 2),
				(height / 2) + 100
			);
		}
		else {
			smallFont.drawString(scoreTitle, 20, smallFont.stringHeight("Score: ") + 20);

			if (hasLifeImage) {
				ofVec2f lifeImageSize = ofVec2f(50, 50);
				int spacing = 20;
				int widthOffset = mainEmitterMaxLife * (lifeImageSize.x + spacing);
				for (int i = 0; i < mainEmitterCurrentLife; i++) {
					lifeImage.draw(width - widthOffset + ((lifeImageSize.x + spacing) * i), 10, lifeImageSize.x, lifeImageSize.y);
				}
				smallFont.drawString("Lives: ", width - smallFont.stringWidth("Lives: ") - (widthOffset + spacing), smallFont.stringHeight("Lives: ") + 20);
			}
			else {
				int defaultLifeImageSize = 20;
				int spacing = 20;
				int widthOffset = (mainEmitterMaxLife - 0.5) * ((defaultLifeImageSize * 2) + spacing);
				for (int i = 0; i < mainEmitterCurrentLife; i++) {
					ofDrawCircle(width - widthOffset + (((defaultLifeImageSize * 2) + spacing) * i), defaultLifeImageSize + 10, defaultLifeImageSize);
				}
				smallFont.drawString("Lives: ", width - smallFont.stringWidth("Lives: ") - (widthOffset + (((defaultLifeImageSize * 2) + spacing) / 2)), smallFont.stringHeight("Lives: ") + 20);
			}
		}
	}
	else {
		bigFont.drawString(
			"Game Over!",
			(width / 2) - (bigFont.stringWidth("Game Over!") / 2),
			(height / 2) - (bigFont.stringHeight("Game Over!"))
		);
		smallFont.drawString(
			"Press the Enter Key to Play Again",
			(width / 2) - (smallFont.stringWidth("Press the Enter Key to Play Again") / 2),
			(height / 2)
		);
		smallFont.drawString(scoreTitle, 20, smallFont.stringHeight("Score: ") + 20);
	}
};

// Updates the background to the width and height of the window
// Updates the score and appends it to the score title
// Tells the background when the main emitter is hurt
//
void Background::update() {
	scoreTitle = scoreTitle.substr(0, 7).append(ofToString(score));
	width = ofGetWidth();
	height = ofGetHeight();

	if (mainEmitterCurrentLife == 0) {
		isGameOver = true;
	}

	if (isHurt) {
		if (hurtFrameTimer < 45) {
			if (ofGetFrameNum() % 1 == 0) {
				hurtFrameTimer++;
			}
		}
		else {
			isHurt = false;
			hurtFrameTimer = 0;
		}
	}
};

// Loads the image of the background
// Sets the background width and height to the window size and starts the game
//
void Background::setBackgroundImage(string path) {
	backgroundImage.load(path);
	width = ofGetWidth();
	height = ofGetHeight();
}

// Loads the hurt image of the background
//
void Background::setBackgroundHurtImage(string path) {
	backgroundHurtImage.load(path);
	hasBackgroundHurtImage = true;
}

// Loads the image of the main emitter life
//
void Background::setLifeImage(string path) {
	hasLifeImage = true;
	lifeImage.load(path);
}


// Loads the font of the game
//
void Background::setFont(string path) {
	titleFont.load(path, 60);
	bigFont.load(path, 45);
	smallFont.load(path, 25);
}

// Loads the fire sound of the emitter for when it fires sprites
//
void Background::setMusic(string path) {
	music.load(path);
	music.setLoop(true);
}

// Gets the life total of the main emitter
//
void Background::getMainEmitterMaxLife(int mainEmitterMaxLife) {
	this->mainEmitterMaxLife = mainEmitterMaxLife;
	this->mainEmitterCurrentLife = mainEmitterMaxLife;
}

// Resets game start conditions
//
void Background::resetGame() {
	score = 0;
	isHurt = false;
	hurtFrameTimer = 0;
	isIdle = true;
	isGameOver = false;
}