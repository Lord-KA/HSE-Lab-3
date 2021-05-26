#include "deque.hpp"
#include <random>
#include "gtest/gtest.h"


std::mt19937 rnd(179);

TEST(Basics, PushAndPop)
{
    std::deque<int> STD1;
    deque<int> D1;
    for (int i = 0; i < rnd() % 3000 + 150; ++i){
        int a = rnd(), b = rnd();
        D1.push_back(a);
        STD1.push_back(a);
        D1.push_front(b);
        STD1.push_front(b);
    }
    EXPECT_EQ(D1, STD1);
    for (int i = 0; i < rnd() % 100 + 10; ++i){
        if (i % 2){
            D1.pop_front();
            STD1.pop_front();
        }
        else{
            D1.pop_back();
            STD1.pop_back();
        }
    }
    EXPECT_EQ(D1, STD1);
    for (int i = 0; i < D1.size(); ++i)
        EXPECT_EQ(D1[i], STD1[i]);
}

TEST(Basics, CopyAndMove){
    std::deque<int> STD1, STD2;
    deque<int> D1, D2;
    for (int i = 0; i < rnd() % 3000 + 150; ++i){
        int a = rnd(), b = rnd();
        D1.push_back(a);
        STD1.push_back(a);
        D1.push_front(b);
        STD1.push_front(b);
    }
    EXPECT_EQ(D1, STD1);
    D2 = D1;
    STD2 = STD1;    
    for (int i = 0; i < rnd() % 100 + 10; ++i){
        if (i % 2){
            D2.pop_front();
            STD2.pop_front();
        }
        else{
            D2.pop_back();
            STD2.pop_back();
        }
    }
 
    EXPECT_EQ(D2, STD2);
    EXPECT_EQ(D2, D2);
    EXPECT_EQ(D1, D1);
    int a = rnd();
    int b = rnd();
    D2.push_front(a);
    D2.push_back(b);
    STD2.push_front(a);
    STD2.push_back(b);

    deque<int> D3(D2);
    std::deque<int> STD3(STD2);
    EXPECT_EQ(D3, STD3);
    EXPECT_EQ(D3, D2);

    a = rnd();
    D3[12] = a;
    STD3[12] = a;
    EXPECT_EQ(D3, STD3);
    size_t i = 0;
    for (auto elem : D3){
        EXPECT_EQ(elem, STD3[i]);
        ++i;
    }

    deque<int> D4(std::move(D2)), D5;
    std::deque<int> STD4(std::move(STD2)), STD5;

    D5 = std::move(D3);
    STD5 = std::move(STD3);

    EXPECT_EQ(D4, STD4);
    EXPECT_EQ(D5, STD5);

    
}
