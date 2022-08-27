#ifndef GUARD_Time_CORRELATION_H
#define GUARD_Time_CORRELATION_H

/*
  Sample the time correlation function 
    C(t) = < A(t) B(t) >

  A and B must be of the same class, of which * must be defined,
  and A * B is of the same type as A and B
*/


template <class T>
class TimeCorrelation {
 public:
  TimeCorrelation(unsigned int number_of_time_steps);

  void Sample(T A, T B);


  std::vector<T> GetTimeCorrelationFunction() const;

 private:  

  unsigned int number_of_time_steps_;
  unsigned int number_of_samples_;

  std::vector<T> C_AB_;
  
};


template <class T>
TimeCorrelation<T>::TimeCorrelation(unsigned int number_of_time_steps)
  : number_of_time_steps_(number_of_time_steps),
    number_of_samples_(0),
    C_AB_(number_of_time_steps_)
{} 



#endif
