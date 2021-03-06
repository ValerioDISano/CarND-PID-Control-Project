#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
    
    this->Kp = Kp_;
    this->Ki = Ki_;
    this->Kd = Kd_;
}

void PID::UpdateError(double cte) {
    
    this->d_error = cte - this->p_error;
    this->p_error = cte;
    this->i_error += cte;

}

double PID::TotalError() {
  
    double error = (-this->Kp * this->p_error) +
      (-this->Ki * this->i_error) +
      (-this->Kd * this->d_error);  // TODO: Add your total error calc here!

  if (error < -1.0)
      error = -1.0;
  else if (error > 1.0)
      error = 1.0;

  return error;
}
