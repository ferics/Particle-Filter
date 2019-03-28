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
   delete list;
}

// A new observation of the robot, of size 3x3
void ParticleFilter::newObservation(Grid observation) {
   // Grid smallMaze[3][3];
   // for(int i = 0; i < rows-2; i++){
   //      for(int j = 0; j < cols-2; j++){
   //         smallMaze[i][j] = maze[i][j];
   //      }
   // }
}

// Return a DEEP COPY of the ParticleList of all particles representing
//    the current possible locations of the robot
ParticleList* ParticleFilter::getParticles() {
   return NULL;
}

// int ParticleFilter::countOpenSpace(){
//    int openSpace;
//     for(int i = 1; i < rows; i++){
//         for(int j = 1; j < cols; j++){
//             if(maze[i][j] == '.'){
//                openSpace++;
//             }
//         }
//     }
//    return openSpace;
// }
