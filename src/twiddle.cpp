#include "twiddle.hpp"

void TwiddleState::setContext(Twiddle* context)
{
    this->context_ = context;
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
    if (error < context_->best_error_)
    {
        context_->best_error_ = error;
        context_->gains_delta_[context_->index_] *= 1.1;
        context_->best_solution_ = context_->gains_;

        context_->index_ = (context_->index_ + 1) % context_->gains_.size();

        context_->changeState(new TwiddleStart());
        return;
    }

    context_->gains_[context_->index_] -= 2.0 * context_->gains_delta_[context_->index_];

    context_->changeState(new TwiddleDecrease());
}

void TwiddleDecrease::run(double error)
{
    if (error < context_->best_error_)
    {
        context_->best_error_ = error;
        context_->gains_delta_[context_->index_] *= 1.1;
        context_->best_solution_ = context_->gains_;
    } else
    {
        context_->gains_[context_->index_] += context_->gains_delta_[context_->index_];
        context_->gains_delta_[context_->index_] *= 0.9;
    }

    context_->changeState(new TwiddleStart());
    context_->index_ = (context_->index_ + 1) % context_->gains_.size();

bool Twiddle::Run(double error)
{
    double abs_error = std::abs(error);
    it_++;
    average_error_ = (average_error_ + abs_error) / double(it_);
    if ((it_ > max_it_ && abs_error > maximum_error_) || it_ > force_run_)
    {
        current_state_->run(average_error_);
        it_ = 0;
        average_error_ = 0.0;
        return true;
    }

    return false;
}
