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
}

// Clean-up the Particle Filter
ParticleFilter::~ParticleFilter() {
   // delete list;
}

// A new observation of the robot, of size 3x3
void ParticleFilter::newObservation(Grid observation) {
   Grid smallMaze = NULL;

   smallMaze = new char*[OBSERVATION_DIMENSION];
   for (int i = 0; i != OBSERVATION_DIMENSION; ++i) {
      smallMaze[i] = new char[OBSERVATION_DIMENSION];
   }

   for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
         if(maze[i][j] == '.'){
            this->list->add_back(new Particle(i,j,ORIEN_LEFT));
            // std::cout << "debug1" << std::endl;
            this->list->add_back(new Particle(i,j,ORIEN_UP));
            // std::cout << "debug2" << std::endl;
            this->list->add_back(new Particle(i,j,ORIEN_RIGHT));
            // std::cout << "debug3" << std::endl;
            this->list->add_back(new Particle(i,j,ORIEN_DOWN)); 
            // std::cout << "debug4" << std::endl;
         }
         // std::cout << "debug5" << std::endl;
      }
      // std::cout << "debug6" << std::endl;
   }

   // for(int i = 0; i < OBSERVATION_DIMENSION; i++){
   //    for(int j = 0; j < OBSERVATION_DIMENSION; j++){
         
   //    }
   // }


   std::cout << "debug6" << std::endl;
   // this->list->clear();
   
}

// Return a DEEP COPY of the ParticleList of all particles representing
//    the current possible locations of the robot
ParticleList* ParticleFilter::getParticles() {
   return list;
}