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
   // delete list;
}

// A new observation of the robot, of size 3x3
void ParticleFilter::newObservation(Grid observation) {

   // for(int j = 0; j < 3; j++){
   //    for(int i = 0; i < 3; i++){
   //       std::cout << observation[j][i];
   //    }
   //    std::cout << std::endl;
   // }


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
   // std::cout << intDirection << std::endl;

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
   std::cout << "I got here" << std::endl;

   ParticleList* listFilter = new ParticleList();
   for (int i = 0; i < list->getNumberParticles(); i++){
      bool match = false;
      for(int y = 0; y < OBSERVATION_DIMENSION && !match; y++){
         for(int x = 0; x < OBSERVATION_DIMENSION && !match; x++){
            int xCord = list->get(i)->getX();
            int yCord = list->get(i)->getY();
            Orientation orient = list->get(i)->getOrientation();   
            // Orientation lastOrient = list->get(i-1)->getOrientation();    
            // if(compareGrids(observation, compareMaze(tempX,tempY))){
         
            if(compareGrids(observation, compareMaze(xCord,yCord,orient))){
               // int xCord = list->get(i)->getX();
               // int yCord = list->get(i)->getY();

               Particle* newPar = new Particle(xCord,yCord,currentOrientation);
               
               // std::cout << "breakpoint" << std::endl;   
               // if (compareParticles(list->get(i-1), list->get(i))) {
                  listFilter->add_back(newPar);
               // }
               // std::cout << "(" << newPar->getX() <<","<< newPar->getY() << ","<<newPar->getOrientation() <<")"<< std::endl;
               match = true;
            } else {
               match = false;
            }
         }
      }
   }
   list = listFilter;
   firstObservation = false;
   // listFilter->clear();
}

// Return a DEEP COPY of the ParticleList of all particles representing
//    the current possible locations of the robot
ParticleList* ParticleFilter::getParticles() {
   return list;
}

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

// Grid ParticleFilter::compareMaze(int x, int y){
Grid ParticleFilter::compareMaze(int x, int y, Orientation orientation){
    Grid smallMaze = NULL;

   //making an empty 3x3 grid
   //REFER to the provided unit_test.cpp
   smallMaze = new char*[OBSERVATION_DIMENSION];
   for (int i = 0; i != OBSERVATION_DIMENSION; ++i) {
      smallMaze[i] = new char[OBSERVATION_DIMENSION];
   }

   int xCorner = x - 1;
   int yCorner = y - 1;

   for (int gridRows = 0; gridRows < OBSERVATION_DIMENSION; gridRows++){
      for (int gridCols = 0; gridCols < OBSERVATION_DIMENSION; gridCols++){
         smallMaze[gridRows][gridCols] = this->maze[yCorner+gridRows][xCorner+gridCols];
      }
   }

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

bool ParticleFilter::compareGrids(Grid observation, Grid particleGrid) {
   
   bool same = true;
   for (int y = 0; y < OBSERVATION_DIMENSION; y++) {
      for (int x = 0; x < OBSERVATION_DIMENSION; x++) {
         // if (x != 1 || y != 1) {
            if (observation[y][x] != particleGrid[y][x]) {
               same = false; 
               // std::cout<<"failed to check"<<std::endl;
               
            }
            // std::cout<<"pass to check"<<std::endl;
         // }
      }
   }
   return same;
}

// bool ParticleFilter::compareParticles(Particle* p1, Particle* p2) {
//     bool match = false;
//     bool xCompare = false;
//     bool yCompare = false;
//     bool oCompare = false;
//     if (p1->getX() == p2->getX()) {
//         xCompare = true;
//     }
//     if (p1->getY() == p2->getY()) {
//         yCompare = true;
//     }
//     if (p1->getOrientation() == p2->getOrientation()) {
//         oCompare = true;
//     }
//     if (xCompare && yCompare && oCompare) {
//         match = true;
//     }
//     return match;
// }


void ParticleFilter::rotateParticle(Orientation orientation){
   for(int i = 0; i < list->getNumberParticles(); i++){
         list->get(i)->setOrientation(orientation);
   }
}

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