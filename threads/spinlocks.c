#include <stdbool.h>

//atomic
bool test_and_set(bool *thelock)
{
    bool initial = *thelock;
    *thelock = true;
    return initial;
}

void lock(bool *thelock)
{
    while (test_and_set(&thelock) == 1);
}

void unlock(bool *thelock)
{
    *thelock = false;
}
