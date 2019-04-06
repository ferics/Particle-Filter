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
}

// Clean-up the Particle Filter
ParticleFilter::~ParticleFilter() {
   // delete list;
}

// A new observation of the robot, of size 3x3
void ParticleFilter::newObservation(Grid observation) {

   int intDirection = -1;
   if (observation[1][1] == '<'){
      intDirection = ORIEN_LEFT;
   } else if (observation[1][1] == '^'){
      intDirection = ORIEN_UP;
   } else if (observation[1][1] == '>'){
      intDirection = ORIEN_RIGHT;
   } else if (observation[1][1] == 'v'){
      intDirection = ORIEN_DOWN;
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
               Particle* newPar = new Particle(xCord,yCord,intDirection);
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
Grid ParticleFilter::gridFromParticle(int x, int y, Orientation orientation){
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
            }
         // }
      }
   }
   return same;
}
