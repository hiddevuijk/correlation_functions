
#ifndef GUARD_SYSTEM_H
#define GUARD_SYSTEM_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <boost/random.hpp>


class System {
 public:
	System(unsigned long int seed, double dt);

  void MakeTimeStep(double dt);
  void Integrate(double delta_t);

  double GetPosition() const { return x_;}
  double GetVelocity() const { return v_;}


  void ResetTime() { time_ = 0; }
  double GetTime() const { return time_;}

 private:
  const boost::normal_distribution<double> normal_distribution_;

  boost::mt19937 random_number_generator_;
  boost::variate_generator<boost::mt19937&,
        boost::normal_distribution<double> > random_normal_distribution_;

  // time step size
  double dt_;


	// particle velocity and position
  double v_, x_;

  // current time	
  double time_;
};

System::System(unsigned long int seed, double dt)
  : normal_distribution_(0.0,1.0),
	  random_number_generator_(seed),
    random_normal_distribution_(random_number_generator_,
                                normal_distribution_),
	  dt_(dt), v_(0.0), x_(0.0), time_(0.0)
{}


void System::Integrate(double delta_time)
{
  while (delta_time > dt_) {
    MakeTimeStep(dt_);
    delta_time -= dt_;
  }
  MakeTimeStep(delta_time);
}

void System::MakeTimeStep(double dt)
{
  double sqrt_2_dt = sqrt(2 * dt);
  x_ += dt * v_;
  v_ +=  - dt * v_ + sqrt_2_dt * random_normal_distribution_();
  time_ += dt;
}

#endif
