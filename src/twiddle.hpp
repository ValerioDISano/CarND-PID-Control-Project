#ifndef TWIDDLE_HPP
#define TWIDDLE_HPP

#include <memory>
#include <vector>

class TwiddleState
{
  protected:
      std::shared_ptr<Twiddle> context_;
  public:
      std::string state;
      virtual void run() = 0;

      void setContext(Twiddle* context);
};

class TwiddleStart : public TwiddleState
{
  public:
    void run() override;
  
};

class TwiddleIncrease : public TwiddleState
{
  public:
    void run() override;
};

class TwiddleDecrease : public TwiddleState
{
  public:
    void run() override;
};


class Twiddle
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
};

#endif // TWIDDLE_HPP
