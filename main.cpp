


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "system.h"
#include "correlation_function.h"

using namespace std;

int main()
{
  double dt = 1e-3;
  double t_sample = 1e-2;
  double t_total = 1e2;

  long unsigned int seed = 123456789;


  System system(seed, dt);
 
  while (system.GetTime() < t_total) {
    system.Integrate(t_sample);
  } 



  return 0;
}
