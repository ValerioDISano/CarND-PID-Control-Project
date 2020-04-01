#ifndef TWIDDLE_HPP
#define TWIDDLE_HPP

#include <memory>
#include <vector>
#include <string>
#include <numeric> // accumulate

class Twiddle; // forward declaration

class TwiddleState
{
  protected:
      std::shared_ptr<Twiddle> context_;
      std::string state_;
      TwiddleState(std::string state) : state_ {state} {;}
  
  public:
      virtual ~TwiddleState() {;}
      
      virtual void run() = 0;
      void setContext(Twiddle* context);
};

class TwiddleStart : public TwiddleState
{
  public:
    TwiddleStart() : TwiddleState("start") {;}
    void run() override;
    
    ~TwiddleStart() {;} 
};

class TwiddleIncrease : public TwiddleState
{
  public:
    TwiddleIncrease() : TwiddleState("Increase") {;}
    void run() override;

    ~TwiddleIncrease() {;}
};

class TwiddleDecrease : public TwiddleState
{
  public:
    TwiddleDecrease() : TwiddleState("Decrease") {;}
    void run() override;
};


class Twiddle 
{
  public:
    Twiddle(const double& tolerance=0.2) : tolerance_ {tolerance} {;}
    ~Twiddle() {;};

    void changeState(TwiddleState* state);
    std::vector<double> gains_;
    std::vector<double> gains_delta_;
    std::vector<double> best_solution_;
    
    double tolerance_;
    std::size_t index_ {0};
  private:
    void Run();
    std::unique_ptr<TwiddleState> current_state_;
};

#endif // TWIDDLE_HPP
