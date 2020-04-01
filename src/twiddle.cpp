#include "twiddle.hpp"

void TwiddleState::setContext(Twiddle* context)
{
    this->context_ = std::make_shared(context);
}

void Twiddle::changeState(TwiddleState* state)
{
    this->current_state = std::make_unique<Twiddle>(state);
    this->current_state.setContext(this);
}

void TwiddleStart::run()
{
    if std::accumulate(context_->gains_delta_.begin(),
            context_->gains_delta_.end(), 0.0) < context_->tolerance_
    {
        context_->best_solution_ = context_->gains_;
        return;
    }

    context_->gains_[context_->index] += context_->gains_delta_[context_->index];

    context_->changeState(new TwiddleIncrease())
}
