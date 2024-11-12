/*
* FILE: main.cpp
* CLASS: CSC35500 Project #2 
* AUTHOR: Amber Goodman
* DATE: 11/2024
*/

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include "AirportAnimator.hpp"
using namespace std;

pthread_t plane0, plane1, plane2, plane3, plane4, plane5, plane6, plane7;

void* planeAction(void *arg)
{

  int *planeID = (int *) arg;
  
    for(int passenger=1; passenger<=10; passenger++)
    {
        AirportAnimator::updatePassengers(*planeID, passenger);
         sleep(1);
    }
            
     AirportAnimator::updateStatus(*planeID, "TAXI");
     AirportAnimator::taxiOut(*planeID);

     AirportAnimator::updateStatus(*planeID, "TKOFF");
     AirportAnimator::takeoff(*planeID);

     AirportAnimator::updateStatus(*planeID,"TOUR");
      sleep(10);

      AirportAnimator::updateStatus(*planeID,"LNDRQ");
      sleep(2);

      AirportAnimator::updateStatus(*planeID,"LAND");
      AirportAnimator::land(*planeID);

      AirportAnimator::updateStatus(*planeID, "TAXI");
      AirportAnimator::taxiIn(*planeID);

      AirportAnimator::updateStatus(*planeID, "DEPLN");
      for(int passenger=9; passenger>=0; passenger--)
      {
          AirportAnimator::updatePassengers(*planeID, passenger);
          sleep(1);
      }
  
      AirportAnimator::updateStatus(*planeID, "DEPLN");
            
        AirportAnimator::updateTours( 1);
        sleep(2);
        return NULL;
}
      
int main (int argc, char * argv[]) 
{

      int id0=0;
      int errCode = pthread_create(&plane0, NULL, planeAction, (void * ) &id0);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
      
      int id1 =  1;
      errCode = pthread_create(&plane1, NULL, planeAction, (void * ) &id1);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
      
      int id2 =  2;
      errCode = pthread_create(&plane2, NULL, planeAction, (void * ) &id2);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
      
      int id3 =  3;
      errCode = pthread_create(&plane3, NULL, planeAction, (void * ) &id3);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
      
      int id4 =  4;
      errCode = pthread_create(&plane4, NULL, planeAction, (void * ) &id4);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
    
      int id5 =  5;
      errCode = pthread_create(&plane5, NULL, planeAction, (void * ) &id5);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
      
      int id6 =  6;
      errCode = pthread_create(&plane6, NULL, planeAction, (void * ) &id6);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
      
      int id7 =  7;
      errCode = pthread_create(&plane7, NULL, planeAction, (void * ) &id7);
      if (errCode== -1)
      {
          cerr << "pthread_create() failed" << endl;
      }
      
      AirportAnimator:: end();
}
