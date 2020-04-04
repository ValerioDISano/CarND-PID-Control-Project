#ifndef TWIDDLE_HPP
#define TWIDDLE_HPP

#include <memory>
#include <vector>
#include <string>
#include <numeric> // accumulate
#include <limits> // double max value

class Twiddle; // forward declaration

class TwiddleState
{
  protected:
      Twiddle* context_;
      TwiddleState(std::string state) : state_ {state} {;}
  
  public:
      std::string state_;
      virtual ~TwiddleState() {;}
      
      virtual void run(double error) = 0;
      void setContext(Twiddle* context);
};

class TwiddleStart : public TwiddleState
{
  public:
    TwiddleStart() : TwiddleState("start") {;}
    void run(double error) override;
    
    ~TwiddleStart() {;} 
};

class TwiddleIncrease : public TwiddleState
{
  public:
    TwiddleIncrease() : TwiddleState("Increase") {;}
    void run(double error) override;

    ~TwiddleIncrease() {;}
};

class TwiddleDecrease : public TwiddleState
{
  public:
    TwiddleDecrease() : TwiddleState("Decrease") {;}
    void run(double error) override;
};


class Twiddle 
{
  public:
    Twiddle(std::vector<double> gains,
            const double& tolerance=0.2) : tolerance_ {tolerance}
    {
        gains_ = gains;
        best_solution_ = gains;
        gains_delta_ = std::vector<double>(gains.size(), 1.0);
    }
    ~Twiddle() {;};

    double best_error_ {std::numeric_limits<double>::max()};
    double average_error_ {0.0};
    std::size_t index_ {0};
    std::vector<double> gains_;
    std::vector<double> gains_delta_;
    std::vector<double> best_solution_;
    
    double tolerance_;
    double best_error_;
    std::size_t index_ {0};
    void changeState(TwiddleState* state);
    bool Run(double error);
  private:
    std::unique_ptr<TwiddleState> current_state_;
    std::unique_ptr<TwiddleState> old_state_;

    std::size_t it_ {0};
    std::size_t force_run_ {1200};
    std::size_t max_it_;
    double maximum_error_;
};

#endif // TWIDDLE_HPP
