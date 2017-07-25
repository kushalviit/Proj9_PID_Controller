# CarND-Controls-PID
Reflections on Project 4 Term2.



## The Effect of P,I,D components

1. The effect of P component, i.e. proportional component,is the component which tells how the controlling value(steering value in this project)as the name
   suggests the steering value is proportaional to the error . It indicates the fact that as the 
   CTE increases the vehicle should increase the steer value .
2. The effect of I component i.e. integral component, is used to account for the faults in the vehicle which makes it move in unintended direction because
   of the design of the car. The factor by which the CTE error is proportional is very less in the simulator model of the car.
3. The effect of D component i.e. Difference/Differntial component,is the component whihc decides how the diffence between the current and the previous CTE 
   error is accounted for. The factor for this element was very high as the track is curved in many places and diffence of CTE is very high in many curves

## The Decision on hyperparameters

    Both Twiddle and Manual tuning was used. The twiddle algorithm has been implemented but the factors used to decided the amount of variation the hyperparameters
    are subjected to is very low hence the simulator got struck. The algorithm had to be restarted with new parameters obtained from the last step of the previous
    run. So combination of Twiddle and Manual tuning was used to decide on the hyperparameters.
     


