# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## PID controller

PID is a three term (Proportional, Integral, Derivative) closed-loop feedback controller.
The PID algorithm is used to control the sterring angle of the car, trying to minimize the CTE (Cross Track Error).

### Proportional component

The proportional component sets the sterring angle proportional to current error value by a factor Kp. The bigger the Kp value the larger will be the steer applied. So a larger Kp will make the car more rapid in steering back to the center of the track but at the same time the car will oscillate. Proportional correction alone makes convergence impossible.

### Integral component

The integral component produces a control input proportional to the sum of all the past errors. This component is useful to deal with systematic biases, like a sterring drift, allowing to correct the steady state error.

### Derivative component

The derivate component takes into account the error change rate between the current and the last one iteration. This component helps to mitigate the overshooting trend caused by the P component. Introducing a derivating component makes the car behavior less abrupt.


## Twiddle

In oder to have an effective PID controller it is necessary that the algorithm gains are correctly tuned. I used the Twiddle algorithm to search the optimal hyper-paramters.
Initially, I set PID gains to zero, so no control was applied to the car steering angle. 
I left the algorithm run until it reached convergence, obtaining the following optimal parameters: 
- Kp 0.1484559
- Ki 0.0001
- Kd 0.696846

The algorithm found this parameters trying to minimize the Mean Absolute Error, computed as follow:

<a href="https://www.codecogs.com/eqnedit.php?latex=MAE&space;=&space;\frac{1}{iterations}&space;\sum_{i=1}^{&space;iterations}&space;\left&space;|&space;CTE_i&space;\right&space;|" target="_blank"><img src="https://latex.codecogs.com/gif.latex?MAE&space;=&space;\frac{1}{iterations}&space;\sum_{i=1}^{&space;iterations}&space;\left&space;|&space;CTE_i&space;\right&space;|" title="MAE = \frac{1}{iterations} \sum_{i=1}^{ iterations} \left | CTE_i \right |" /></a>
