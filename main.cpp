


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
  double dt = 1e-1;
  double t_sample = 1e-2;
  double t_total = 2e6;

  unsigned int n_time_steps = 1000;

  long unsigned int seed = 213456789;


  System system(seed, dt);

  TimeCorrelation1<double> cvv(n_time_steps); 
  TimeCorrelation2<double> cvr(n_time_steps); 
  TimeCorrelation3<double> crr(n_time_steps); 

  system.Integrate(100);
  while (system.GetTime() < t_total) {
    system.Integrate(t_sample);
    cvv.Sample(system.GetVelocity(), system.GetVelocity());
    cvr.Sample(system.GetVelocity(), system.GetPosition());
    crr.Sample(system.GetPosition(), system.GetPosition());
    cout << t_total << "\t" << system.GetTime() << endl;
  } 

  save_vector(cvv.GetTimeCorrelationFunction(), "cvv.dat");
  save_vector(cvr.GetTimeCorrelationFunction(), "cvr.dat");
  save_vector(crr.GetTimeCorrelationFunction(), "crr.dat");

  return 0;
}
