
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

double frr(double A0, double At, double B0, double Bt)
{
  double temp = (At-A0);
  return temp * temp;
}

double fvr(double A0, double At, double B0, double Bt)
{
  return A0 * (B0 - Bt);
}

double fvv(double A0, double At, double B0, double Bt)
{
  return A0 * At;
}

int main()
{
  double dt = 5e-2;
  double t_sample = dt;
  double t_total = 1e6;

  unsigned int n_time_steps = 5;
  unsigned int n_decades = 6;

  long unsigned int seed = 213451789;


  System system(seed, dt);

  //TimeCorrelation<double> crr(n_time_steps, f); 
  LogTimeCorrelation<double> crr(n_time_steps, n_decades, frr); 
  LogTimeCorrelation<double> cvr(n_time_steps, n_decades, fvr); 
  LogTimeCorrelation<double> cvv(n_time_steps, n_decades, fvv); 


  system.Integrate(t_sample);
  while (system.GetTime() < t_total) {
    system.Integrate(t_sample);
    crr.Sample(system.GetPosition(), system.GetPosition()); 
    cvr.Sample(system.GetVelocity(), system.GetPosition()); 
    cvv.Sample(system.GetVelocity(), system.GetVelocity()); 
    cout << t_total << "\t" << system.GetTime() << endl;
  } 
  save_vector(crr.GetTimeCorrelationFunction(), "crr.dat");
  save_vector(crr.GetTimeList(), "t.dat");

  save_vector(cvr.GetTimeCorrelationFunction(), "cvr.dat");
  save_vector(cvv.GetTimeCorrelationFunction(), "cvv.dat");

  return 0;
}
