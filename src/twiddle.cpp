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
