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
    if std::accumulate(context_->gains_delta.begin(),
            context_->gains_delta.end(), 0.0) < context_->tolerance
    {
        context_->best_solution = gains;
        return;
    }

    gains[index] += gains_delta[index];

    context_->changeState(new TwiddleIncrease())
}
