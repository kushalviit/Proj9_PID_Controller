#include "PID.h"
#include <limits>
#include <stdlib.h>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double _Kp, double _Ki, double _Kd) {
 Kp=_Kp;
 Ki=_Ki;
 Kd=_Kd;
 p_error=0.0;
 i_error=0.0;
 d_error=0.0;
 step_count=0;
 twiddle=true;
 twiddle_step_limit=500;
 tol=0.2;
 error=0.0;
 best_error=0.0;
 dp[0]=1;//0.09161819 last twiddle run
 dp[1]=1;//0.005168 last twiddle run
 dp[2]=1;//0.090286 last twiddle run
 first_entry=true;
 new_index=false;
 before_second_if=true;
 index=0;
 //p_previous[0]=p_previous[1]=p_previous[2]=0.0;
}

void PID::UpdateError(double cte) {

//Twiddle algorithm

if(twiddle && TotalError()>tol)
  { 
    step_count++;
    double *p[]={&Kp,&Ki,&Kd};
    if(new_index)
    {
     *p[index]+=dp[index];
      new_index=false;
       std::cout<<"Index :"<<index<<std::endl;
    }
    if(step_count==2*twiddle_step_limit && first_entry)
    {
      step_count=0;
      first_entry=false;
      new_index=true;
      best_error=error/twiddle_step_limit;
      p_error=0.0;
      i_error=0.0;
      d_error=0.0;
      error=0.0;
    }
    else if(step_count==2*twiddle_step_limit && !first_entry)
    {
      step_count=0;
      if(error/twiddle_step_limit<best_error )
      {
        best_error=error/twiddle_step_limit;
        
        dp[index]*=1.1;
        index++;
        index%=3;
        new_index=true;
        p_error=0.0;
        i_error=0.0;
        d_error=0.0;
        error=0.0;
        if(before_second_if==false)
         {
          before_second_if=true;
         }
       }
      else
       {
          if(before_second_if)
           {
             *p[index]-=2*dp[index];
             before_second_if=false;
             p_error=0.0;
             i_error=0.0;
             d_error=0.0;
             error=0.0;
            }
           else
            {
             *p[index]+=dp[index];
             before_second_if=true;
             dp[index]*=0.9;
             index++;
             index%=3;
             new_index=true;
             p_error=0.0;
             i_error=0.0;
             d_error=0.0;
             error=0.0;
            }
         
        }
     }
    else error_calc(cte);
  } 
if(TotalError()<tol)
 {
  twiddle=false;
 }

//Computing the errors for PID run    
double cte_p=p_error;
 p_error=cte;
 i_error+=cte;
 d_error=cte-cte_p;
}


//Used to compare with the tolerance to decide when to end the twiddle
double PID::TotalError() {
  return dp[0]+dp[1]+dp[2];
}


//Common steps for error calculation during twiddle
void PID::error_calc(double cte)
{
    
    if(step_count<twiddle_step_limit)
    {
     return;
    }
    if(step_count>=twiddle_step_limit && step_count<2*twiddle_step_limit )
    {
     error+=cte*cte;
      return;
    }
  
}
