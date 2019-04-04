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
   for (int i = 0; i< 3; i++){
      for (int j = 0; j < 3; j++){
         if (observation[i][j] == '<'){
            intDirection = ORIEN_LEFT;
         } else if (observation[i][j] == '^'){
            intDirection = ORIEN_UP;
         } else if (observation[i][j] == '>'){
            intDirection = ORIEN_RIGHT;
         } else if (observation[i][j] == 'v'){
            intDirection = ORIEN_DOWN;
         }
      }
   }

   Grid smallMaze = NULL;

   //making an empty 3x3 grid
   //REFER to the provided unit_test.cpp
   smallMaze = new char*[OBSERVATION_DIMENSION];
   for (int i = 0; i != OBSERVATION_DIMENSION; ++i) {
      smallMaze[i] = new char[OBSERVATION_DIMENSION];
   }

   // smallMaze = observation;


   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
         if(maze[j][i] == '.'){
            smallMaze = {[j-1][i-1],[j][i-1],[j+1][i-1],[j-1][i],[j][i],[j+1][i],[j-1][i+1],[j][i+1],[j+1][i+1]}
         }
      }
   }


   // ParticleList* list2 = new ParticleList();
   // for (int i = 0; i < 3; i++){
   //    for (int j = 0; j < 3; j++){
   //       list2->add_back(new Particle(i,j,intDirection));
   //    }
   // }

   // // for (int i = 0; i < getNumberParticles(); i++){
   // //    if
   // // }


   std::cout << intDirection << std::endl;
   // std::cout << "debug6" << std::endl;
   // this->list->clear();
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