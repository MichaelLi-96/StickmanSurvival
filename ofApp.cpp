#include "ofApp.h"

// Michael Li - CS 134 SJSU
// 11/6/2018

// Loads the background, images/sounds, animation images, assign values to emitter and particle emitter variables
// MUST specify a emitter size and sprite size if they have no loaded images
//
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofHideCursor();
	cursor.load("/images/cursor/crosshair.png");
	hitSound.load("/sounds/coin.aiff");
	hitSound.setVolume(0.2f);

	// texture loading
	//
	ofDisableArbTex();     // disable rectangular textures

	// load textures
	//
	if (!ofLoadImage(particleTex, "ParticleFiles/images/dot.png")) {
		cout << "Particle Texture File: ParticleFiles/images/dot.png not found" << endl;
		ofExit();
	}

	// load the shader
	//
#ifdef TARGET_OPENGLES
	shader.load("ParticleFiles/shaders_gles/shader");
#else
	shader.load("ParticleFiles/shaders/shader");
#endif

	ofDirectory emitterUpAnim("/images/hero/up");
	emitterUpAnim.listDir();
	for (int i = 0; i < emitterUpAnim.size(); i++) {
		ofImage spriteAnimImage;
		spriteAnimImage.load(emitterUpAnim.getPath(i));
		mainEmitter.upAnim.push_back(spriteAnimImage);
	}
	ofDirectory emitterDownAnim("/images/hero/down");
	emitterDownAnim.listDir();
	for (int i = 0; i < emitterDownAnim.size(); i++) {
		ofImage spriteAnimImage;
		spriteAnimImage.load(emitterDownAnim.getPath(i));
		mainEmitter.downAnim.push_back(spriteAnimImage);
	}
	ofDirectory emitterLeftAnim("/images/hero/left");
	emitterLeftAnim.listDir();
	for (int i = 0; i < emitterLeftAnim.size(); i++) {
		ofImage spriteAnimImage;
		spriteAnimImage.load(emitterLeftAnim.getPath(i));
		mainEmitter.leftAnim.push_back(spriteAnimImage);
	}
	ofDirectory emitterRightAnim("/images/hero/right");
	emitterRightAnim.listDir();
	for (int i = 0; i < emitterRightAnim.size(); i++) {
		ofImage spriteAnimImage;
		spriteAnimImage.load(emitterRightAnim.getPath(i));
		mainEmitter.rightAnim.push_back(spriteAnimImage);
	}
	ofDirectory allSpriteAnim("/images/bullet");
	allSpriteAnim.listDir();
	for (int i = 0; i < allSpriteAnim.size(); i++) {
		ofImage spriteAnimImage;
		spriteAnimImage.load(allSpriteAnim.getPath(i));
		mainEmitter.spriteSystem.spriteAnim.push_back(spriteAnimImage);
	}

	mainEmitter.setAsMainEmitter();
	mainEmitter.setEmitterImage("images/hero/up/up1.png");
	mainEmitter.setEmitterSize(mainEmitter.width * 0.5, mainEmitter.height * 0.5);
	mainEmitter.setInitialEmitterPosition(ofVec2f((ofGetWidth() / 2) - (mainEmitter.width / 2), (ofGetHeight() / 2) - (mainEmitter.height / 2)));
	mainEmitter.setMaxLife(3);
	mainEmitter.setSpriteImage(allSpriteAnim.getPath(0));
	mainEmitter.setSpriteSize(mainEmitter.spriteWidth * 2.5, mainEmitter.spriteHeight * 2.5);
	mainEmitter.setFireSound("sounds/lazer.wav");
	mainEmitter.fireSound.setVolume(0.2f);
	mainEmitter.setSpriteName("MainEmitter");
	mainEmitter.setSpriteVelocity(ofVec2f(0, -1));
	mainEmitter.setEmitterSpeed(10);
	mainEmitter.setRateofFire(200);
	mainEmitter.setSpriteLifespan(2000);
	mainEmitter.setSpriteSpeed(14);

	background.setBackgroundImage("images/background/background.png");
	background.setBackgroundHurtImage("images/background/backgroundHurt.png");
	background.setLifeImage("images/heart/heart.png");
	background.setFont("fonts/Exo2-SemiBold.otf");
	levelSystem.setFont("fonts/Exo2-SemiBold.otf");
	background.getMainEmitterMaxLife(mainEmitter.maxLife);
	background.setMusic("sounds/backgroundMusic.mp3");
	background.music.setVolume(0.2f);
	background.music.play();

	particleEmitter.setEmitterType(RadialEmitter);
	particleEmitter.setVelocity(ofVec3f(1000, 100, 0));
	particleEmitter.setRandomLife(true);
	particleEmitter.setLifespanRange(ofVec3f(0.5, 1.5));
	particleEmitter.setOneShot(true);
	particleEmitter.setParticleRadius(25);
	particleEmitter.setGroupSize(80);
}

// If the game is idle or the game is over, do not update
// Updates the background, level system, and emitters
//
void ofApp::update() {
	particleEmitter.update();
	if (background.isIdle || background.isGameOver) {
		return;
	}
	ofSeedRandom();

	// Tests for collision between main emitter sprites and enemy emitter sprites
	// Loops through the each emitter's sprite system to acquire all sprites current position
	// Play the hit sound, increase the score, and one shot particles if a collision occurs
	//
	for (int i = 0; i < mainEmitter.spriteSystem.sprites.size(); i++) {
		for (int j = 0; j < levelSystem.enemyEmitters.size(); j++) {
			for (int k = 0; k < levelSystem.enemyEmitters[j].spriteSystem.sprites.size(); k++) {
				ofVec2f p1 = ofVec2f((mainEmitter.spriteSystem.sprites[i].position.x + mainEmitter.spriteSystem.sprites[i].width / 2), (mainEmitter.spriteSystem.sprites[i].position.y + mainEmitter.spriteSystem.sprites[i].height / 2));
				ofVec2f p2 = ofVec2f((levelSystem.enemyEmitters[j].spriteSystem.sprites[k].position.x + levelSystem.enemyEmitters[j].spriteSystem.sprites[k].width / 2), (levelSystem.enemyEmitters[j].spriteSystem.sprites[k].position.y + levelSystem.enemyEmitters[j].spriteSystem.sprites[k].height / 2));
				float distance = ofDist(p1.x, p1.y, p2.x, p2.y);
				float contactDistance = mainEmitter.spriteSystem.sprites[i].width / 2 + levelSystem.enemyEmitters[j].spriteSystem.sprites[k].width / 2;

				if (distance < contactDistance) {
					hitSound.play();
					mainEmitter.spriteSystem.sprites[i].lifespan = 0;
					levelSystem.enemyEmitters[j].spriteSystem.sprites[k].lifespan = 0;
					background.score += 100;
					ofColor color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
					particleEmitter.setParticleColor(color);
					particleEmitter.setPostion(p2);
					particleEmitter.start();
				}
			}
		}
	}

	// Tests for collision between main emitter and enemy emitter sprites
	// Loops through the each emitter's sprite system to acquire main emitter and sprites current position
	// Subtract life total by one and one shot particles if a collision occurs
	//
	for (int i = 0; i < levelSystem.enemyEmitters.size(); i++) {
		for (int j = 0; j < levelSystem.enemyEmitters[i].spriteSystem.sprites.size(); j++) {
			ofVec2f p1 = ofVec2f((levelSystem.enemyEmitters[i].spriteSystem.sprites[j].position.x + levelSystem.enemyEmitters[i].spriteSystem.sprites[j].width / 2), (levelSystem.enemyEmitters[i].spriteSystem.sprites[j].position.y + levelSystem.enemyEmitters[i].spriteSystem.sprites[j].height / 2));
			ofVec2f p2 = ofVec2f((mainEmitter.position.x + mainEmitter.width / 2), (mainEmitter.position.y + mainEmitter.height / 2));
			float distance = ofDist(p1.x, p1.y, p2.x, p2.y);
			float contactDistance = mainEmitter.height / 2 + levelSystem.enemyEmitters[i].spriteSystem.sprites[j].width / 2;

			if (distance < contactDistance) {
				if (background.hasBackgroundHurtImage) {
					background.isHurt = true;
					background.hurtFrameTimer = 0;
				}
				levelSystem.enemyEmitters[i].spriteSystem.sprites[j].lifespan = 0;
				background.mainEmitterCurrentLife--;
				particleEmitter.setParticleColor(ofColor::red);
				particleEmitter.setPostion(p2);
				particleEmitter.start();
			}
		}
	}

	background.update();

	// Sets the rotation angle of the main emitter for emitting sprites
	//
	ofVec2f p1 = ofVec2f(mainEmitter.position.x + mainEmitter.width / 2, mainEmitter.position.y + mainEmitter.height / 2);
	ofVec2f p2 = ofVec2f(ofGetMouseX(), ofGetMouseY());
	float angle = atan2(p1.y - p2.y, p1.x - p2.x) * 180 / PI - 90;
	mainEmitter.rotationDegree = angle;

	if (background.mainEmitterCurrentLife == 0) {
		mainEmitter.isGameOver = true;
		levelSystem.isGameOver = true;
	}
	mainEmitter.update();
	levelSystem.update();
}

// Draws the background, level system, emitters, particle emitters, and cursor
//
void ofApp::draw() {
	background.draw();
	levelSystem.draw();
	mainEmitter.draw();
	loadVbo();
	glDepthMask(GL_FALSE);

	// this makes everything look glowy :)
	//
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnablePointSprites();

	shader.begin();

	// draw particle emitter here..
	//
	particleEmitter.draw();
	particleTex.bind();
	vbo.draw(GL_POINTS, 0, (int)particleEmitter.sys->particles.size());
	particleTex.unbind();

	shader.end();

	ofDisablePointSprites();
	ofDisableBlendMode();
	ofEnableAlphaBlending();

	// set back the depth mask
	//
	glDepthMask(GL_TRUE);

	ofSetColor(255, 255, 255);

	//draw cursor at mouse position
	//
	cursor.draw(ofGetMouseX() - cursor.getWidth() / 2, ofGetMouseY() - cursor.getHeight() / 2, cursor.getWidth() * 0.5, cursor.getHeight() * 0.5);
}

// Space key press to change game state from idle to not idle, and to fire sprites from the emitter
// Arrow/WASD keys press to animate the sprite movement in arrow direction
// Enter key to play the game again
//
void ofApp::keyPressed(int key) {
	switch (key) {
		case ' ':
			if (background.isIdle) {
				background.isIdle = false;
				mainEmitter.isIdle = false;
				levelSystem.isIdle = false;
			}
			else {
				mainEmitter.fire = true;
			};
			break;
		case OF_KEY_RETURN:
			if (background.isGameOver) {
				background.resetGame();
				mainEmitter.resetGame();
				levelSystem.resetGame();
				background.getMainEmitterMaxLife(mainEmitter.maxLife);
			}
			break;
		case OF_KEY_UP:
			mainEmitter.move(MoveUp);
			break;
		case OF_KEY_DOWN:
			mainEmitter.move(MoveDown);
			break;
		case OF_KEY_RIGHT:
			mainEmitter.move(MoveRight);
			break;
		case OF_KEY_LEFT:
			mainEmitter.move(MoveLeft);
			break;
		case 'w':
			mainEmitter.move(MoveUp);
			break;
		case 's':
			mainEmitter.move(MoveDown);
			break;
		case 'd':
			mainEmitter.move(MoveRight);
			break;
		case 'a':
			mainEmitter.move(MoveLeft);
			break;
	}
}

// Space key release to stop firing sprites from the emitter
// Arrow/WASD keys release to animate the stop of sprite movement
//
void ofApp::keyReleased(int key) {
	switch (key) {
		case ' ':
			mainEmitter.fire = false;
			break;
		case OF_KEY_RETURN:
			break;
		case OF_KEY_UP:
			mainEmitter.move(MoveStop);
			break;
		case OF_KEY_DOWN:
			mainEmitter.move(MoveStop);
			break;
		case OF_KEY_LEFT:
			mainEmitter.move(MoveStop);
			break;
		case OF_KEY_RIGHT:
			mainEmitter.move(MoveStop);
			break;
		case 'w':
			mainEmitter.move(MoveStop);
			break;
		case 's':
			mainEmitter.move(MoveStop);
			break;
		case 'd':
			mainEmitter.move(MoveStop);
			break;
		case 'a':
			mainEmitter.move(MoveStop);
			break;
	}
}

// Updates the position of the main emitter as it is being dragged by the mouse
// The main emitter can only be dragged within the bounds of the window
// The main emitter will stop if it touches the window boundaries when dragged by the mouse
//
void ofApp::mouseDragged(int x, int y, int button) {
	ofVec2f testPosition = ofVec2f(x - mainEmitter.xLengthToImageOrigin, y - mainEmitter.yLengthToImageOrigin);

	if (mainEmitter.isMainEmitter &&
		mainEmitter.isPressed &&
		testPosition.x >= 0 &&
		testPosition.y >= 0 &&
		testPosition.x + mainEmitter.width <= ofGetWidth() &&
		testPosition.y + mainEmitter.height <= ofGetHeight()) {
			mainEmitter.position = ofVec2f(x - mainEmitter.xLengthToImageOrigin, y - mainEmitter.yLengthToImageOrigin);
	}
}

// Lets the main emitter know if it has been pressed within itself by the mouse
// Fire sprites from the main emitter if mouse is clicked
//
void ofApp::mousePressed(int x, int y, int button) {
	if (mainEmitter.inside(x, y) && mainEmitter.isIdle == false) {
		mainEmitter.isPressed = true;
	}
	else {
		if (!background.isIdle) {
			mainEmitter.fire = true;
		}
	}
}

// Lets the main emitter know if it has been relased by the mouse
// Stop firing sprites when mouse is released
//
void ofApp::mouseReleased(int x, int y, int button) {
	mainEmitter.isPressed = false;
	mainEmitter.fire = false;
}

// load vertex buffer in preparation for rendering
//
void ofApp::loadVbo() {
	if (particleEmitter.sys->particles.size() < 1) return;

	vector<ofVec3f> sizes;
	vector<ofVec3f> points;
	for (int i = 0; i < particleEmitter.sys->particles.size(); i++) {
		points.push_back(particleEmitter.sys->particles[i].position);
		sizes.push_back(ofVec3f(particleEmitter.particleRadius));
	}
	// upload the data to the vbo
	//
	int total = (int)points.size();
	vbo.clear();
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
}