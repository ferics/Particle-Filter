
#ifndef COSC_ASS_ONE_PARTICLE
#define COSC_ASS_ONE_PARTICLE

#include "Types.h"

class Particle {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // x-co-ordinate of the particle
   int getX();

   // y-co-ordinate of the particle
   int getY();

   // Orientation of the particle
   Orientation getOrientation();

   Particle(int x,int y, Orientation z);
   ~Particle();


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

private:
   int x;
   int y;
   Orientation direction;

};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Particle
typedef Particle* ParticlePtr;

#endif // COSC_ASS_ONE_PARTICLE
