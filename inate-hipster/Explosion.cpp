/*
Parts adapted from Chris Campbell -- http://www.iforce2d.net/b2dtut/explosions
*/

#include "Explosion.h"

Explosion::Explosion(int numRays, int blastPower) : numRays(numRays), blastPower(blastPower)
{
	if (numRays > MAX_BLAST_RAYS)
		numRays = MAX_BLAST_RAYS;
}

Explosion::~Explosion()
{
	clearParticles();
}


void Explosion::explodeParticle(b2Vec2* loc)
{
	clearParticles();

	if (loc) 
	{
		for (int i = 0; i < numRays; i++) 
		{
			float angle = (i / (float)numRays) * 360 * 0.0174532925199432957f;
			b2Vec2 rayDir(sinf(angle), cosf(angle));

			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.fixedRotation = true;
			bd.bullet = true;
			bd.linearDamping = 10;
			bd.gravityScale = 0;
			bd.position = *loc;
			bd.linearVelocity = 0.125f * blastPower * rayDir;
			b2Body* body = worldptr->CreateBody(&bd);

			b2CircleShape circleShape;
			circleShape.m_radius = 0.05;

			b2FixtureDef fd;
			fd.shape = &circleShape;
			fd.density = 60 / (float)numRays;
			fd.friction = 0;
			fd.restitution = 0.99f;
			fd.filter.groupIndex = -1;
			body->CreateFixture(&fd);

			blastParticleBodies[i] = body;
		}
	}
}

void Explosion::clearParticles()
{
	//clear old particles
	for (int i = 0; i < MAX_BLAST_RAYS; i++) {
		if (blastParticleBodies[i]) {
			worldptr->DestroyBody(blastParticleBodies[i]);
			blastParticleBodies[i] = NULL;
		}
	}
}

