#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  

  
  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  bool twiddle;
  double error;
  double best_error;
  int step_count;
  int twiddle_step_limit;
  double dp[3];
  double p_previous[3];
  double tol;
  bool first_entry;
 bool new_index;
 bool before_second_if;
 int index;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  void error_calc(double cte);
};

#endif /* PID_H */
