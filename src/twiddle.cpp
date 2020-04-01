#include "twiddle.hpp"


void TwiddleState::setContext(Twiddle* context)
{
    this->context_ = std::make_shared(context);
}
