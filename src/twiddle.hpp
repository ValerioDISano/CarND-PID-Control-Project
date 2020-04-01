#ifndef TWIDDLE_HPP
#define TWIDDLE_HPP

#include <memory>
#include <vector>

class TwiddleState
{
  protected:
      std::shared_ptr<Twiddle> context_;
      std::string state;
  public:
      virtual void run() = 0;

      void setContext(Twiddle* context);
};

class TwiddleStart : public TwiddleState
{
  public:
    TwiddleStart() : state{"Start"} {;}
    void run() override;
  
};

class TwiddleIncrease : public TwiddleState
{
  public:
    TwiddleIncrease() : state{"Increase"} {;}
    void run() override;
};

class TwiddleDecrease : public TwiddleState
{
  public:
    TwiddleDecrease() : state{"Decrease"} {;}
    void run() override;
};


class 
{
  public:
    Twiddle()
    ~Twiddle()

    void changeState(TwiddleState* state);
  private:
    void Run();
    std::vector<double> gains;
    std::vector<double> gains_delta;
    std::vector<double> best_solution;
    std::unique_ptr<TwiddleState> current_state;

    std::size_t index {0};
};

#endif // TWIDDLE_HPP
