#include "twiddle.hpp"

void TwiddleState::setContext(Twiddle* context)
{
    this->context_ = std::shared_ptr<Twiddle>(context);
}

void Twiddle::changeState(TwiddleState* state)
{
    current_state_ = std::unique_ptr<TwiddleState>(state);
    current_state_->setContext(this);
}

void TwiddleStart::run(double error)
{
    if (std::accumulate(context_->gains_delta_.begin(),
            context_->gains_delta_.end(), 0.0) < context_->tolerance_)
    {
        context_->best_solution_ = context_->gains_;
        return;
    }

    context_->gains_[context_->index_] += context_->gains_delta_[context_->index_];

    context_->changeState(new TwiddleIncrease());
}

void TwiddleIncrease::run(double error)
{
    ;
}

void TwiddleDecrease::run(double error)
{
    ;
}
