#include <iostream>
#include <math.h>
#include <tuple>
using namespace std;

double new_mean, new_var;

tuple<double, double> measurement_update(double mean1, double var1, double mean2, double var2)
{
    new_mean = (var2 * mean1 + var1 * mean2) / (var1 + var2);
    new_var = 1 / (1 / var1 + 1 / var2);
    return make_tuple(new_mean, new_var);
}

tuple<double, double> state_prediction(double mean1, double var1, double mean2, double var2)
{
    new_mean = mean1 + mean2;
    new_var = var1 + var2;
    return make_tuple(new_mean, new_var);
}

int main()
{
    // measurements and measurement variance
    double measurements[5] = { 5, 6, 7, 9, 10 };
    double measurement_sig = 4;
    
    // motions and motion variance
    double motion[5] = { 1, 1, 2, 1, 1 };
    double motion_sig = 2;
    
    // initial state
    double mu = 0;
    double sig = 1000;
    
    // look variables to iteratively measure and update state estimation
    tuple<double, double> priors;
    tuple<double, double> posteriors;
    
    // Loop through all the measurments
    for (int i = 0; i < sizeof(measurements) / sizeof(measurements[0]); i++)
    {
      // apply measurment update
      posteriors = measurement_update(mu, sig, measurements[i], measurement_sig);
      mu  = get<0>(posteriors);
      sig = get<1>(posteriors);
      printf("update:  [%f, %f]\n", mu, sig);
      
      // apply state prediction
      priors = state_prediction(mu, sig, motion[i], motion_sig);
      mu  = get<0>(priors);
      sig = get<1>(priors);
      printf("predict: [%f, %f]\n", mu, sig);
    }
    
    // while that ^^^ code works - and illuminates some of the tuple access methods - this is much cleaner
    /*  
    for (int i = 0; i < sizeof(measurements) / sizeof(measurements[0]); i++)
    {
      // Apply a measurment update
      tie(mu, sig) = measurement_update(mu, sig, measurements[i], measurement_sig);
      printf("update:  [%f, %f]\n", mu, sig);
      
      // Apply a state prediction
      tie(mu, sig) = state_prediction(mu, sig, motion[i], motion_sig);
      printf("predict: [%f, %f]\n", mu, sig);
    }
    */
    
    // another great tuple example: look how useful std::ignore is here (like _ in python)
    /*
    int main () 
    {
      int myint;
      char mychar;

      std::tuple<int,float,char> mytuple;

      mytuple = std::make_tuple(10, 2.6, 'a');

      std::tie(myint, std::ignore, mychar) = mytuple;

      std::cout << "myint contains: " << myint << '\n';
      std::cout << "mychar contains: " << mychar << '\n';

      return 0;
    }
    */
    
    return 0;
}
