#pragma once
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"
#include "Particle.h"

class ParticleSystem {
public:
	void add(const Particle &);
	void remove(int);
	void update();
	void setLifespan(float);
	void draw();
	vector<Particle> particles;
};
