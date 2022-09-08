

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

double f2(double A0, double At, double B0, double Bt)
{
  double temp = (At-A0);
  return temp * temp;
}

double f4(double A0, double At, double B0, double Bt)
{
  double temp = (At-A0);
  return temp * temp * temp * temp;
}
int main()
{
  double dt = 1e-2;
  double t_sample = dt;
  double t_total = 1e6;

  unsigned int n_time_steps = 4;

  long unsigned int seed = 213451789;


  System system(seed, dt);

  //TimeCorrelation<double> crr(n_time_steps, f); 
  LogTimeCorrelation<double> crr2(n_time_steps, f2); 
  LogTimeCorrelation<double> crr4(n_time_steps, f4); 


  system.Integrate(t_sample);
  while (system.GetTime() < t_total) {
    system.Integrate(t_sample);
    crr2.Sample(system.GetPosition(), system.GetPosition()); 
    crr4.Sample(system.GetPosition(), system.GetPosition()); 
    cout << t_total << "\t" << system.GetTime() << endl;
  } 
  save_vector(crr2.GetTimeCorrelationFunction(), "crr2.dat");
  save_vector(crr2.GetTimeList(), "t2.dat");

  save_vector(crr4.GetTimeCorrelationFunction(), "crr4.dat");
  save_vector(crr4.GetTimeList(), "t4.dat");

  return 0;
}
