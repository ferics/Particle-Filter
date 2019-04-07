
#include "Particle.h"

// x-co-ordinate of the particle
int Particle::getX() {
   return this->x;
}

// y-co-ordinate of the particle
int Particle::getY() {
   return this->y;
}
// Orientation of the particle
Orientation Particle::getOrientation() {
   return this->orientation;
}

void Particle::setX(int x){
   this->x = x;
}

void Particle::setY(int y){
   this->y = y;
}

void Particle::setOrientation(Orientation orientation){
   this->orientation = orientation;
}

Particle::Particle(int x, int y, Orientation orientation){
   this->x = x;
   this->y = y;
   this->orientation = orientation;
}

Particle::~Particle(){
   // delete &x;
   // delete &y;
   // delete &direction;
}

