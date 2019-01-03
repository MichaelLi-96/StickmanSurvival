#include "spritesystem.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// Adds a sprite to the end of the SpriteSystem vector
//
void SpriteSystem::add(Sprite spriteObj) {
	sprites.push_back(spriteObj);
};

// Removes the sprite located at position index
//
void SpriteSystem::remove(int index) {
	sprites.erase(sprites.begin() + index);
};

// Updates the SpriteSystem by removing sprites that have exceeded their lifespan
// Moves the sprites within the SpriteSystem by shifting the sprites position by their velocity * speed every frame
//
void SpriteSystem::update() {

	if (sprites.size() == 0) return;
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;

	// Check which sprites have exceeded their lifespan and delete them
	// from the list. When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sprites.end()) {
		if (((s->lifespan != -1 && s->age() > s->lifespan)) || s->position.y >= ofGetHeight()) {
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}

	// Reverse the sprite Animation if has reached the end
	//
	if (!spriteAnim.empty()) {
		if (animSequence == 0) {
			reverseAnim = false;
		}
		if (animSequence == spriteAnim.size() - 1)
		{
			reverseAnim = true;
		}
	}

	// Tells the sprite system what animation image to load as the sprite image at each frame
	// Move the sprite depending on it's velocity and speed
	// Only rotates the sprite images if it is from the main emitter
	//
	for (int i = 0; i < sprites.size(); i++) {
		if (!spriteAnim.empty()) {
			sprites[i].image = spriteAnim[animSequence];
			if (isMainEmitter) {
				sprites[i].imageRotate();
			}
		}
		sprites[i].position += sprites[i].velocity * sprites[i].speed;

		// To make enemy sprites bounce off walls
		//
		if (!isMainEmitter && (sprites[i].position.x + sprites[i].width >= ofGetWidth() || sprites[i].position.x <= 0)) {
			sprites[i].velocity.x = sprites[i].velocity.x * -1;
		}
	}

	if (!spriteAnim.empty()) {
		if (!reverseAnim && ofGetFrameNum() % 5 == 0) {
			animSequence++;
		}
		if (reverseAnim && ofGetFrameNum() % 5 == 0) {
			animSequence--;
		}
	}
};

// Draws each sprite in the SpriteSystem
//
void SpriteSystem::draw() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}
};
