
#include "ParticleList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define PARTICLE_SIZE      10000

#ifndef DEBUG
#define DEBUG        0
#endif

// Initialise a new particle filter with a given maze of size (x,y)
ParticleList::ParticleList() {
   for(int i = 0; i < 300; i++){
      particles[i] = 0;
   }
   numParticles = 0;
}

// Clean-up the particle list
ParticleList::~ParticleList() {
   clear();
   delete *particles;
}

// Number of particles in the ParticleList
int ParticleList::getNumberParticles() {
   for(int i = 0; i < 300; i++){
      numParticles++;
   }
   return numParticles;
}

// Get a pointer to the i-th particle in the list
ParticlePtr ParticleList::get(int i) {
   ParticlePtr getPtr = NULL;
   if (i < numParticle){
      getPtr = particle[i];
   }
   return getPtr;
}

// Add a particle (as a pointer) to the list
//    This class now has control over the pointer
//    And should delete the pointer if the particle is removed from the list
void ParticleList::add_back(ParticlePtr particle) {
   particle[numParticles] = particle;
   numParticles++;
}

// Remove all particles from the list
void ParticleList::clear() {
   for(int i = 0; i < 300; i++){
      delete particle[i];
   }
}
