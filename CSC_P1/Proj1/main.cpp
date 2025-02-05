#include <iostream>
#include <csignal>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include "Command.hpp"
using namespace std;
 
// to compile type "make" not g++ (if you have Make File)
int main(int argc, char *argv[])
{

    Command com;
    int num=1; // keep track of number of commands. 
    
    // prompt for and read in first command. 
    cout << ">>>> ";
    com.read(); 
    
    while(com.name() != "exit")
    {
          char* args[100];   // Warning? fix later
          // make dynamic array
          for ( int i = 0; i <= com.numArgs(); i++)
         {
            int myLength = com.args() -> length();
            args [i] = new char[myLength +1];
            strcpy( args[0],  com.args() -> c_str() );
            args[i-1] = NULL;
         }
  
        // fork here
        int pid = fork();
        
        if (pid == 0) // parent
        {
              // cd
              if (com.backgrounded() == true) // is program being backgrounded?
              {
                    int cpid  = fork();
                    if (cpid !=0) // parent
                    {
                          // prompts for another command
                            cout << ">>>> ";
                            com.read(); 
                    }
                    else // child
                    {
                        execvp(args[0],args);
                        cout<< "pid: " << getpid() << " Command: " << com.name() << " completed!"<< endl;
                    }
              }
  
              else // run it and wait for results
              { 
                  int cpid = fork();
                  if (cpid !=0)
                  {
                      waitpid (cpid, NULL, 0); // here? 
                      cout<< "pid: " << getpid() << " Command: " << com.name() << " completed!"<< endl;
                  }
                  else
                  {
                      // do nothing
                  }
              }
        }
        
        else // child
        {
            if ( com.pipeOut() == true)
            {
                int pipefds[2];
                int status = pipe(pipefds);
                
                if (status !=0)
                {
                      cout << "pipe call failed!" << endl;
                      return 1;
                }
              
                close(pipefds [1]);
                dup2(pipefds[0],fileno(stdin));
            }
            
            else
            {
                // do nothing
            }
            
            if (com.redirIn() == true)
            {
                string fileInput = com.inputRedirectFile();
                FILE *fp = fopen(argv[1], fileInput.c_str() );
                dup2(fileno(fp), fileno(stdin));
            }
            
          else
          {
              // do nothing
          }
          
          if (com.redirOut() == true)
          {
                string fileOutput = com.outputRedirectFile();
                FILE *fp = fopen(argv[1], fileOutput.c_str() );
                dup2(fileno(fp), fileno(stdin));
          }
          
          else
          {
              // do nothing
          }
               
       } 
      
      execvp(args[0],args); 
                  
      // print out current command
      cout << num++ << ")" << com << endl;
        
      //prompt for and read next command
      cout << ">>>> ";
      com.read();
      }
  
    
    cout << "Thank you for using mini-shell. We now return you to your regularly scheduled shell!" << endl;
    return 0;
    }
