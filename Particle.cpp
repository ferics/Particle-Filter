
#include "Particle.h"

// x-co-ordinate of the particle
int Particle::getX() {
   return x;
}

// y-co-ordinate of the particle
int Particle::getY() {
   return y;
}

Particle::Particle(int x, int y, Orientation direction){
   this->x = x;
   this->y = y;
   this->direction = direction;
}

Particle::~Particle(){
   delete this->x;
   delete this->y;
   delete this->direction;
}

// Orientation of the particle
Orientation Particle::getOrientation() {
   return direction;
}
