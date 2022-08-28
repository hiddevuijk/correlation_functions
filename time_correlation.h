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

 protected:  

  virtual void SampleCABFromList() {};

  unsigned int number_of_time_steps_;
  int number_of_samples_;

  std::vector<T> A_list_;
  std::vector<T> B_list_;

  unsigned int list_last_index_;

  std::vector<T> c_AB_;
  
};

template <class T>
class TimeCorrelation3 : public TimeCorrelation<T>
{
 public:
  TimeCorrelation3(unsigned int number_of_time_steps)
    : TimeCorrelation<T>(number_of_time_steps) {};

 private:
    void SampleCABFromList() override;
};


template <class T>
TimeCorrelation<T>::TimeCorrelation(unsigned int number_of_time_steps)
  : number_of_time_steps_(number_of_time_steps),
    number_of_samples_(-1 * number_of_time_steps),
    A_list_(number_of_time_steps),
    B_list_(number_of_time_steps),
    list_last_index_(-1),
    c_AB_(number_of_time_steps_)
{} 

template <class T>
void TimeCorrelation<T>::Sample(T A, T B)
{
  // if A_list_ and B_list_ not filled yet
  if (number_of_samples_ < 0) {
    ++list_last_index_;
    A_list_[list_last_index_] = A;
    B_list_[list_last_index_] = B;
    ++number_of_samples_;
  } else {
    list_last_index_ = (list_last_index_ + 1) % number_of_time_steps_;
    A_list_[list_last_index_] = A; 
    B_list_[list_last_index_] = B; 
    SampleCABFromList();
  } 
}

template <class T>
std::vector<T> TimeCorrelation<T>::GetTimeCorrelationFunction() const
{

  std::vector<T> c_AB_temp = c_AB_;
  for (unsigned int i = 0; i < number_of_time_steps_; ++i) {
    c_AB_temp[i] /= number_of_samples_;
  }
  return c_AB_temp;
}

template <class T>
void TimeCorrelation3<T>::SampleCABFromList()
{
  ++TimeCorrelation<T>::number_of_samples_;
  int delta_ti;
  unsigned int list_last_index = TimeCorrelation<T>::list_last_index_; 
  for (unsigned int i = 0;
       i < TimeCorrelation<T>::number_of_time_steps_;
       ++i)
  {
    delta_ti = TimeCorrelation<T>::list_last_index_ - i;

    if ( delta_ti < 0) {
      delta_ti += TimeCorrelation<T>::number_of_time_steps_;
    }

    TimeCorrelation<T>::c_AB_[i] +=
       (TimeCorrelation<T>::A_list_[list_last_index] -
          TimeCorrelation<T>::A_list_[delta_ti]) *
       (TimeCorrelation<T>::B_list_[list_last_index] -
          TimeCorrelation<T>::B_list_[delta_ti]);

  }
  
}


#endif
