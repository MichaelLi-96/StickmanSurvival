#include "emitter.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// Setup for an emitter object, assign default values to variables
//
Emitter::Emitter() {
	moveDirection = MoveStop; 
	animSequence = 0;
	spriteFireCounter = 0;
	isMainEmitter = false;
	hasImage = false;
	hasSpriteImage = false;
	isPressed = false;
	isIdle = true;
	isGameOver = false;
	fire = false;
}

// If the game is not idle and not game over, draw the sprite system and the emitter
// If an image path has been supplied draw the image, else draw a rectangle
//
void Emitter::draw() {
	if(!isIdle && !isGameOver) {
		spriteSystem.draw();
		if (hasImage) {
			emitterImage.draw(position, width, height);
		}
		else {
			ofDrawRectangle(position, width, height);
		}
	}
};

// For only the main emitter, update the position of the emitter when arrow keys are pressed or the mouse drags the emitter
// If the emitter fires, create a sprite and assign values to all it's variables, add it to the sprite system, and play a firing sound
// Lastly, update the sprite system
//
void Emitter::update() {
	ofVec2f direction;

	if (isMainEmitter) {
		if (animSequence == 5) {
			animSequence = 0;
		}

		switch (moveDirection) {
		case MoveUp:
			direction = ofVec2f(0, -speed);
			updateAnimSequence(upAnim, 10);
			break;
		case MoveDown:
			direction = ofVec2f(0, speed);
			updateAnimSequence(downAnim, 10);
			break;
		case MoveLeft:
			direction = ofVec2f(-speed, 0);
			updateAnimSequence(leftAnim, 10);
			break;
		case MoveRight:
			direction = ofVec2f(speed, 0);
			updateAnimSequence(rightAnim, 10);
			break;
		case MoveStop:
			animSequence = 0;
			break;
		}

		// Updates the position of the emitter as it is being moved by arrow keys
		// The emitter can only move within the bounds of the window
		// The emitter will stop if it touches the window boundaries
		//
		if (position.x + direction.x >= 0 &&
			position.y + direction.y >= 0 &&
			position.x + direction.x + width <= ofGetWidth() &&
			position.y + direction.y + height <= ofGetHeight()) {
			position += direction;
		}

		// Fires a sprite from the emitter if the space bar is pressed, fires multiple sprites if held
		//
		if (fire) {
			addSprite();
		}
	}
	// If enemy emitter
	else {
		direction = ofVec2f(speed, 0);
		if (position.x + direction.x >= 0 &&
			position.y + direction.y >= 0 &&
			position.x + direction.x + width <= ofGetWidth() &&
			position.y + direction.y + height <= ofGetHeight()) {
			position += direction;
		}
		else {
			setEmitterSpeed(-speed);
		}
		addSprite();
	}

	spriteSystem.update();
};

// Adds a sprite to the SpriteSystem and assign values to properties of the newly created sprite
// Plays a fire sound right after the sprite is added to the SpriteSystem if is the main emitter
//
void Emitter::addSprite() {
	if (spriteSystem.sprites.empty() || spriteSystem.sprites.back().age() > rateOfFire) {
		Sprite sprite;
		sprite.birthtime = ofGetSystemTimeMillis();
		sprite.hasImage = hasSpriteImage;
		sprite.image = spriteImage;
		sprite.name = spriteName;
		sprite.width = spriteWidth;
		sprite.height = spriteHeight;
		sprite.speed = spriteSpeed;
		sprite.lifespan = spriteLifespan;
		sprite.position = ofVec2f(position.x + width / 2 - spriteWidth / 2, position.y + height / 2 - spriteHeight / 2);
		sprite.velocity = spriteVelocity;
		sprite.sinCounter = 0;

		if (isMainEmitter) {
			sprite.velocity.rotate(rotationDegree);
			sprite.rotationDegree = rotationDegree;
			sprite.imageRotate();
			spriteSystem.add(sprite);
			fireSound.play();
		}
		else {
			if (spriteFireCounter < maxSpriteFireAmount) {
				spriteSystem.add(sprite);
				spriteFireCounter++;
			}
		}
	}
}

// Update the emitters direction of movement
//
void Emitter::move(MoveDir dir) {
	moveDirection = dir;
};

// Sets the emitter as the main emitter
//
void Emitter::setAsMainEmitter() {
	isMainEmitter = true;
	spriteSystem.isMainEmitter = true;
}

// Loads the initial image of the emitter
// Sets the width and height to the size of the image
//
void Emitter::setEmitterImage(string path) {
	hasImage = true;
	emitterImage.load(path);
	width = emitterImage.getWidth();
	height = emitterImage.getHeight();
}

// Tells the emitter what animation image to load as the emitter image at what frame
//
void Emitter::updateAnimSequence(vector<ofImage> anim, int animPerFrames) {
	if (!anim.empty()) {
		if (ofGetFrameNum() % animPerFrames == 0 || animSequence == 0) {
			emitterImage = anim[animSequence];
			animSequence++;
		}
	}
}

// Saves the width and height of the emitter
//
void Emitter::setEmitterSize(float width, float height) {
	this->width = width;
	this->height = height;
}

// Sets the position of the emitter of where it first gets drawn 
//
void Emitter::setInitialEmitterPosition(ofVec2f startingPoint) {
	this->startingPoint = startingPoint;
	position = startingPoint;
}

// Sets the life total of the emitter
//
void Emitter::setMaxLife(int maxLife) {
	this->maxLife = maxLife;
}

// Sets the initial speed of the emitter
//
void Emitter::setEmitterSpeed(float speed) {
	this->speed = speed;
}

// Sets the degree of rotation to emit sprites from
//
void Emitter::setRotationDegree(float rotationDegree) {
	this->rotationDegree = rotationDegree;
}

// Sets the emitter's rate of fire of sprites
//
void Emitter::setRateofFire(float rateOfFire) {
	this->rateOfFire = rateOfFire;
}

// Loads the fire sound of the emitter for when it fires sprites
//
void Emitter::setFireSound(string path) {
	fireSound.load(path);
}

// Loads the initial image of the sprite
// Sets the sprites width and height to the size of the image
//
void Emitter::setSpriteImage(string path) {
	hasSpriteImage = true;
	spriteImage.load(path);
	spriteWidth = spriteImage.getWidth();
	spriteHeight = spriteImage.getHeight();
}

// Saves the name of the sprite associated with the emitter
//
void Emitter::setSpriteName(string spriteName) {
	this->spriteName = spriteName;
}

// Saves the width and height of the sprite associated with the emitter
//
void Emitter::setSpriteSize(float spriteWidth, float spriteHeight) {
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
}

// Saves the lifespan of the sprite associated with the emitter
//
void Emitter::setSpriteLifespan(float spriteLifespan) {
	this->spriteLifespan = spriteLifespan;
}

// Saves the velocity of the sprite associated with the emitter
//
void Emitter::setSpriteVelocity(ofVec2f spriteVelocity) {
	this->spriteVelocity = spriteVelocity;
}

// Saves the speed of the sprite associated with the emitter
//
void Emitter::setSpriteSpeed(float spriteSpeed) {
	this->spriteSpeed = spriteSpeed;
}

// Sets the maximum amount of sprites an enemy emitter can fire
//
void Emitter::setMaxSpriteFireAmount(int maxSpriteFireAmount) {
	this->maxSpriteFireAmount = maxSpriteFireAmount;
}

// Resets game start conditions
//
void Emitter::resetGame() {
	if (isMainEmitter) {
		emitterImage = upAnim[0];
	}
	position = startingPoint;
	spriteSystem.sprites.clear();
	isIdle = true;
	isGameOver = false;
}

// Returns true if the mouse click was inside the emitter image, false if not
//
bool Emitter::inside(int x, int y) {
	if ((x > position.x && x < position.x + width) && (y > position.y && y < position.y + height)) {
		xLengthToImageOrigin = x - position.x;
		yLengthToImageOrigin = y - position.y;
		return true;
	}
	else {
		return false;
	}
};
