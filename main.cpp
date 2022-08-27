


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "system.h"
#include "time_correlation.h"

using namespace std;

template <class T>
void save_vector(const vector<T>& vec, string name)
{
  ofstream vec_out; 
  vec_out.open(name);

  for (unsigned int i = 0; i < vec.size(); ++i) {
    vec_out << vec[i] << "\n";
  }

  vec_out.close();
}

int main()
{
  double dt = 5e-1;
  double t_sample = 1.0;
  double t_total = 1e5;

  unsigned int n_time_steps = 40;

  long unsigned int seed = 123456789;


  System system(seed, dt);

  TimeCorrelation<double> crr(n_time_steps); 

  while (system.GetTime() < t_total) {
    system.Integrate(t_sample);
    crr.Sample(system.GetPosition(), system.GetPosition());
    cout << t_total << "\t" << system.GetTime() << endl;
  } 

  save_vector(crr.GetTimeCorrelationFunction(), "crr.dat");

  return 0;
}
