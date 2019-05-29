
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

   Particle(int x,int y, Orientation orientation);
   ~Particle();


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   void setX(int x);
   void setY(int y);
   void setOrientation(Orientation orientation);
private:
   int x;
   int y;
   Orientation orientation;

};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Particle
typedef Particle* ParticlePtr;

#endif // COSC_ASS_ONE_PARTICLE
