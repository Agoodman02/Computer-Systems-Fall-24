// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PROJECT PROJECT PROJECT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <cstdio> // for fileno
#include <cstring>  // for strlen
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

// simulates ls -l | wc         *the "|" command means pipe
int main(int argc, char *argv[])
{
      int pipeInfo[2];
      int myPipe = pipe(pipeInfo);
      
      if (myPipe !=  0)
        {
            cerr << "pip() call failed!" << endl;
            return 1;
        }
        
      int pid=fork();
      
      if (pid!=0)   //let's make parent be "wc" ...
      {
            close(pipeInfo[1]); // not using writer, so close it.
            dup2(pipeInfo[0], fileno(stdin));
            
            cout << "do wc  (parent)" << endl;
            char *args[2]; 
            
            int myLength; // = strlen("wc");
            String wc = "wc";
            myLength = wc.length();
            args[0] = new char [myLength +1];
            strcpy(args[0], wc.c_str() );
            args[1]=nullptr;
            execvp("wc", args);  // could substitute "wc" with args[0]
      }
      else // in child (ls -l)
      {
          char *args[3]; 
          
            close (pipeInfo[0]);
             dup2(pipeInfo[1], fileno(stdout));
             
            cout <<  "do ls -l (child)" << endl;
            
             int myLength; // = strlen("ls");
            String str= "ls";
            myLength = str.length();
            args[0] = new char [myLength +1];
            strcpy(args[0], str.c_str() );
            
            str = "-l";
            myLength = str.length();
            args[1] = new char [myLength+1];
            strcpy(args[1], str.c_str() );
            
            args[2] = nullptr;
            execvp(args[0], args);
            
            cout << "do ls  -l (child)" << endl;
      }

      return 0;
}
