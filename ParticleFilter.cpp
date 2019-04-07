/**
 * Particle Filter class that implements a list of particles
 * for all possible location (particles) of a robot within a
 * given maze and observations.
 * 
 * BEGIN
 *    CREATE an empty list
 *       POPULATE the empty list with all possible open spaces
 *       in the maze and all orientation
 *    KEEP TRACK of the orientation with the previous orientation
 *       IF it is the first observation
 *          SET the previous orientation to the current observation
 *          orientation
 *       ELSE continue with algorithm THEN set it after the algorithm
 *    CHECK IF it is the first observation
 *       IF(firstObservation)
 *          CONTINUE with algorithm
 *       ELSE
 *          CHANGE all particles orientation IF robot rotated
 *          CHANGE all particles x/y coordinate IF robot moved
 *    CREATE new empty list to filter
 *    SEARCH through the original list and find the particle that matches
 *    with the observation
 *       IF matches THEN add that particle to the new list
 *       REPEAT till last particle
 *    REPLACE original list with new list that filtered the particles
 * END
 * 
 * Issues encountered:
 * Program might run into segmentation fault if it cannot begin to populate
 * the original list. REFER to addParticlesToEmptyList() for implementation.
 * Program did not check if the list was to add the same/duplicate particles.
 * 
 * Rather than searching the whole maze, the design was decided and implemented
 * such that it searches the list of all particles THEN find the particle that
 * matches to the observation THEN add the particle to a new list. Also, rather
 * than duplicating two large particles list then deleting the ones that don't match
 * the observation, it was decided and implemented to add it instead.
 * This is done to ensure there are no NULL elements all over the list when the elements
 * are deleted (not matched).
 * NOTE: Unit tests include the provided sample as this test passes the sample01 test.
 * 
 * Quality of this software design.
 * Pros:
 *    -Code blocks were taken out of newObservatin() as much as possible to ensure readability
 *     such as rotating/shifting the particles in the particle list.
 *    -All simple functionalities such as comparing two grids and extracting the grid from a
 *     given particle are also broken down into smaller functions outside newObservation().
 * Cons:
 *    -Some variable names make less sense than the other, such as smallMaze (refer to the
 *     small 3x3 grid extract from a particle)
 *    -Some magic numbers were  used such as gri[1][1] as refered to the CENTER of the grid that
 *     could be defined elsewhere as a #define.
 * 
 *  @author Chanboth Som
 */

#include "ParticleFilter.h"
#include "ParticleList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

// Initialise a new particle filter with a given maze of size (x,y)
ParticleFilter::ParticleFilter(char** maze, int rows, int cols) {
   this->maze = maze;
   this->rows = rows;
   this->cols = cols;
   this->list = new ParticleList();
   addParticlesToEmptyList();
   firstObservation = true;
   previousOrientation = -1;
}

// Clean-up the Particle Filter
ParticleFilter::~ParticleFilter() {
}

// A new observation of the robot, of size 3x3
void ParticleFilter::newObservation(Grid observation) {

   int currentOrientation = -1;
   if (observation[1][1] == '<'){
      currentOrientation = ORIEN_LEFT;
   } else if (observation[1][1] == '^'){
      currentOrientation = ORIEN_UP;
   } else if (observation[1][1] == '>'){
      currentOrientation = ORIEN_RIGHT;
   } else if (observation[1][1] == 'v'){
      currentOrientation = ORIEN_DOWN;
   }

   if(!firstObservation){
      /* Compare current orientation to the previous orientation
       * If robot had been rotated
       *    THEN set all particles' orientation in the list to the current orientation
       */
      if (previousOrientation != currentOrientation){
         rotateParticle(currentOrientation);
      } else {
      /* If robot had been moved (+/-)1 in x direction
       *    THEN set all particles' x coordinate in the list to the current x coordinate
       * If robot had been moved (+/-)1 in y direction
       *    THEN set all particles' y coordinate in the list to the current y coordinate
       */
         shiftParticle(currentOrientation);
      }
   }

   ParticleList* listFilter = new ParticleList();
   for (int i = 0; i < list->getNumberParticles(); i++){
      bool match = false;
      for(int y = 0; y < OBSERVATION_DIMENSION && !match; y++){
         for(int x = 0; x < OBSERVATION_DIMENSION && !match; x++){
            int xCord = list->get(i)->getX();
            int yCord = list->get(i)->getY();
            Orientation orient = list->get(i)->getOrientation();
         
            if(compareGrids(observation, gridFromParticle(xCord,yCord,orient))){

               Particle* newPar = new Particle(xCord,yCord,currentOrientation);
                  listFilter->add_back(newPar);
               match = true;
            } else {
               match = false;
            }
         }
      }
   }
   list = listFilter;
   firstObservation = false;
   previousOrientation = currentOrientation;
}

// Return a DEEP COPY of the ParticleList of all particles representing
//    the current possible locations of the robot
ParticleList* ParticleFilter::getParticles() {
   ParticleList* deepCopy(list);
   return deepCopy;
}

//Populate the empty list with all possible particles on the open spaces
void ParticleFilter::addParticlesToEmptyList(){
   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
         if(maze[i][j] == '.'){
            list->add_back(new Particle(j,i,ORIEN_LEFT));
            list->add_back(new Particle(j,i,ORIEN_UP));
            list->add_back(new Particle(j,i,ORIEN_RIGHT));
            list->add_back(new Particle(j,i,ORIEN_DOWN)); 
         }
      }
   }
}

Grid ParticleFilter::gridFromParticle(int x, int y, Orientation orientation){
    Grid smallMaze = NULL;

   //making an empty 3x3 grid
   //REFER to the provided unit_test.cpp
   smallMaze = new char*[OBSERVATION_DIMENSION];
   for (int i = 0; i != OBSERVATION_DIMENSION; ++i) {
      smallMaze[i] = new char[OBSERVATION_DIMENSION];
   }

   //Point to the top left corner away from the particle
   //THEN start copying the maze's content to the 3x3 grid
   int xCorner = x - 1;
   int yCorner = y - 1;

   for (int gridRows = 0; gridRows < OBSERVATION_DIMENSION; gridRows++){
      for (int gridCols = 0; gridCols < OBSERVATION_DIMENSION; gridCols++){
         smallMaze[gridRows][gridCols] = this->maze[yCorner+gridRows][xCorner+gridCols];
      }
   }

   //Change the copied grid (smallMaze) centre to where the robot is facing.
   if(orientation == 0){
      smallMaze[1][1] = '<';
   } else if (orientation == 1){
      smallMaze[1][1] = '^';
   } else if (orientation == 2){
      smallMaze[1][1] = '>';
   } else if (orientation == 3){
      smallMaze[1][1] = 'v';
   }

   return smallMaze;
}

//Compare two given 3x3 grids
//Purpose: compare the observation and the grid from the particle
bool ParticleFilter::compareGrids(Grid observation, Grid particleGrid) {  
   bool same = true;
   for (int y = 0; y < OBSERVATION_DIMENSION; y++) {
      for (int x = 0; x < OBSERVATION_DIMENSION; x++) {
         if (observation[y][x] != particleGrid[y][x]) {
            same = false;
         }
      }
   }
   return same;
}

//Rotate all particles' orientation in the list as it had rotated
void ParticleFilter::rotateParticle(Orientation orientation){
   for(int i = 0; i < list->getNumberParticles(); i++){
      list->get(i)->setOrientation(orientation);
   }
}

//Shift particles' x/y coordinate in the list as it had moved 1 unit
void ParticleFilter::shiftParticle(Orientation orientation){
   if(orientation == 0){
      for(int i = 0; i < list->getNumberParticles(); i++){
         list->get(i)->setX(list->get(i)->getX() - 1);
      }
   } else if (orientation == 2){
      for(int i = 0; i < list->getNumberParticles(); i++){
         list->get(i)->setX(list->get(i)->getX() + 1);
      }
   } else if (orientation == 1){
      for(int i = 0; i < list->getNumberParticles(); i++){
         list->get(i)->setY(list->get(i)->getY() - 1);
      }
   } else if (orientation == 3){
      for(int i = 0; i < list->getNumberParticles(); i++){
         list->get(i)->setY(list->get(i)->getY() + 1);
      }
   }
}