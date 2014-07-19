/*
	Parts adapted from Chris Campbell -- http://www.iforce2d.net/b2dtut/explosions
*/

#pragma once

#include <Box2D\Box2D.h>

#include "worldConst.h"

const int MAX_BLAST_RAYS = 120;

class Explosion
{
public:
	Explosion(int numRays, int blastPower);
	~Explosion();
	void blast();
	void explodeParticle(b2Vec2* loc);
	void clearParticles();
	void clearStoppedParticles();
	
private:
	
	b2Body*	blastParticleBodies[MAX_BLAST_RAYS];
	int numRays;
	int blastPower;

};

