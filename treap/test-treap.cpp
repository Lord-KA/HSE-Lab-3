#include "treap.hpp"
#include <cassert>
#include "gtest/gtest.h"



TEST(Basics, )
{
    Treap<int, int> T1;
    for (int i = 0; i < rnd() % 100 + 10; ++i)
        T1.insert(rnd(), rnd());
    
}
