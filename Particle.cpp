
#include "Particle.h"

// x-co-ordinate of the particle
int Particle::getX() {
   return x;
}

// y-co-ordinate of the particle
int Particle::getY() {
   return y;
}

Particle::Particle(int xPos, int yPos, Orientation z){
   x = xPos;
   y = yPos;
   direction = z;
}

Particle::~Particle(){
   delete x;
   delete y;
   delete direction;
}

// Orientation of the particle
Orientation Particle::getOrientation() {
   return direction;
}
