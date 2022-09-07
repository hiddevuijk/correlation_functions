

#include "time_correlation.h"
#include "log_time_correlation.h"
#include "system.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


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
  double dt = 1e-3;
  double t_sample = dt;
  double t_total = 5e4;

  //unsigned int n_time_steps = 1000;

  long unsigned int seed = 213456789;


  System system(seed, dt);

  //TimeCorrelation1<double> cvv(n_time_steps); 
  //TimeCorrelation2<double> cvr(n_time_steps); 
  //TimeCorrelation3<double> crr(n_time_steps); 

  LogTimeCorrelation<double> crr(5);

  system.Integrate(1.0);
  while (system.GetTime() < t_total) {
    system.Integrate(t_sample);
    crr.Sample(system.GetPosition(), system.GetPosition()); 
    //cvv.Sample(system.GetVelocity(), system.GetVelocity());
    //cvr.Sample(system.GetVelocity(), system.GetPosition());
    //crr.Sample(system.GetPosition(), system.GetPosition());
    cout << t_total << "\t" << system.GetTime() << endl;
  } 
  save_vector(crr.GetCorrelationFunction(), "crr.dat");
  save_vector(crr.GetTimeList(), "t.dat");
  //save_vector(cvv.GetTimeCorrelationFunction(), "cvv.dat");
  //save_vector(cvr.GetTimeCorrelationFunction(), "cvr.dat");
  //save_vector(crr.GetTimeCorrelationFunction(), "crr.dat");

  return 0;
}
