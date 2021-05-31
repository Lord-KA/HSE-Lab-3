#include <iostream>
#include <vector>
#include <random>
#include "gtest/gtest.h"

#include "vector.hpp"
#include "../deque/deque.hpp"

std::mt19937 rnd(179);

TEST(MemberFunctions, Constructor)
{
    deque<long long> D;
    for (int i = 0; i < rnd() % 100 + 15; ++i){
        D.push_back(rnd());
        if (rnd() % 12)
            D.push_front(rnd());
    }

    vector<long long> V1, V2(112, 12), V3(1, 12345), V4(D.begin(), D.end());
    std::vector<long long> SDTV1, STDV2(112, 12), STDV3(1, 12345), STDV4(D.begin(), D.end());
    for (size_t i = 0; i < V4.size(); ++i)
        EXPECT_EQ(V4[i], STDV4[i]);
}
