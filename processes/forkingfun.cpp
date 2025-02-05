#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
  cout << "my pid = " << getpid() << endl;

  //while(true)   // REALLY bad idea ... why? computer crash :/ ... doesn't stop :/
 for (int index =0; index<4; index++)
    fork();

  cout << "good on fork!" << endl;

  return 0;
}
