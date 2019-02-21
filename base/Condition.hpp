#pragma once

#include "noncopyable.hpp"

#include <pthread.h>


class Condition : noncopyable
{
private:
    /* data */
public:
    Condition(/* args */);
    ~Condition();
};

Condition::Condition(/* args */)
{
}

Condition::~Condition()
{
}
