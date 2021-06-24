#include <iostream>
#include <vector>
#include <random>
#include <deque>
#include "gtest/gtest.h"

#include "vector.hpp"
#include "../deque/deque.hpp"

std::mt19937 rnd(179);

TEST(Manual, Constructors)
{
    deque<int> D;
    for (int i = 0; i < 40; ++i){

        D.push_back(rnd());
        if (rnd() % 12)
            D.push_front(rnd());
    }

    vector<long long> V1, V2(112), V3(1, 12345), V4(D.begin(), D.end());

    std::vector<long long> STDV1, STDV2(112), STDV3(1, 12345), STDV4(D.begin(), D.end());

    for (size_t i = 0; i < V1.size(); ++i)
        EXPECT_EQ(V1[i], STDV1[i]);
    for (size_t i = 0; i < V2.size(); ++i)
        EXPECT_EQ(V2[i], STDV2[i]);
    for (size_t i = 0; i < V3.size(); ++i)
        EXPECT_EQ(V3[i], STDV3[i]);
    for (size_t i = 0; i < V4.size(); ++i)
        EXPECT_EQ(V4[i], STDV4[i]);

    EXPECT_EQ(V4, STDV4);
    EXPECT_NE(V1, V4);
    vector<long long> V6(V4);
    V6[2] = rnd();
    EXPECT_NE(V6, V4);
    vector<long long> V5(std::move(V4));
    std::vector<long long> STDV5(std::move(STDV4));

    for (size_t i = 0; i < V5.size(); ++i)
        EXPECT_EQ(V5[i], STDV5[i]);
}

TEST(Manual, Assign) 
{
    deque<int> D;
    for (int i = 0; i < 40; ++i){
        D.push_back(rnd());
        if (rnd() % 12)
            D.push_front(rnd());
    }

    vector<long> V1, V2, V3;
    std::vector<long> STDV1, STDV2, STDV3;
    V1.assign(D.begin(), D.end());
    STDV1.assign(D.begin(), D.end());
    EXPECT_EQ(V1, STDV1);

    int a = rnd() % 500;
    int b = rnd();
    V2.assign(a, b);
    STDV2.assign(a, b);
    EXPECT_EQ(V2, STDV2);

    V3 = V1;
    STDV3 = STDV1;
    EXPECT_EQ(V1, STDV1);
    EXPECT_EQ(V1, V3);
    EXPECT_EQ(V3, STDV3);
    
    V2.assign(V1.begin(), V1.end() - 1);
    STDV2.assign(V1.begin(), V1.end() - 1);
    EXPECT_NE(V2, V1);
    EXPECT_EQ(V2, STDV2);
    return; //TODO fix memory leak in move assign
    V3 = std::move(V2);
    STDV3 = std::move(STDV2);
    EXPECT_EQ(V3, STDV3);
}

TEST(Manual, ElementAccess)
{
    deque<int> D;
    for (int i = 0; i < 40; ++i){
        D.push_back(rnd());
        if (rnd() % 12)
            D.push_front(rnd());
    }

    vector<long> V1, V2, V3;
    std::vector<long> STDV1, STDV2, STDV3;
    V1.assign(D.begin(), D.end());
    STDV1.assign(D.begin(), D.end());
    EXPECT_EQ(V1, STDV1);

    for (size_t i = 0; i < V1.size(); ++i){
        EXPECT_EQ(V1[i], STDV1[i]);
        EXPECT_EQ(V1.at(i), STDV1.at(i));
    }
    EXPECT_EQ(V1.front(), STDV1.front());
    EXPECT_EQ(V1.back(), STDV1.back());

    for (size_t i = 0; i < V1.size(); ++i){
        ++++V1[i];
        ++++STDV1[i];
    }
    for (size_t i = 0; i < V1.size(); ++i){
        EXPECT_EQ(V1[i], STDV1[i]);
        EXPECT_EQ(V1.at(i), STDV1.at(i));
    }
 
}

TEST(Iterators, Forward)
{
    deque<int> D;
    for (int i = 0; i < 40; ++i){
        D.push_back(rnd());
        if (rnd() % 12)
            D.push_front(rnd());
    }

    vector<long> V1, V2, V3;
    std::vector<long> STDV1, STDV2, STDV3;
    V1.assign(D.begin(), D.end());
    STDV1.assign(D.begin(), D.end());
    EXPECT_EQ(V1, STDV1);
    
    auto iter_1 = V1.begin();
    auto iter_2 = STDV1.begin();

    while (iter_1 != V1.end()){
        EXPECT_EQ(*(iter_1++), *(iter_2++));
    }
    
}

TEST(Iterators, Backward)
{
    deque<int> D;
    for (int i = 0; i < 40; ++i){
        D.push_back(rnd());
        if (rnd() % 12)
            D.push_front(rnd());
    }

    vector<long> V1, V2, V3;
    std::vector<long> STDV1, STDV2, STDV3;
    V1.assign(D.begin(), D.end());
    STDV1.assign(D.begin(), D.end());
    EXPECT_EQ(V1, STDV1);
    
    auto iter_1 = V1.end();
    auto iter_2 = STDV1.end();

    while (iter_1 != V1.begin()){
        EXPECT_EQ(*(--iter_1), *(--iter_2));
    }
}


TEST(Iterators, RandomAccess)
{
    deque<long> D;
    for (int i = 0; i < 1000 + rnd() % 3000; ++i){
        D.push_back(rnd()); 
        if (rnd() % 2)
            D.push_front(rnd());
    }
    vector<long> V1, V2, V3;
    std::vector<long> STDV1, STDV2, STDV3;
    V1.assign(D.begin(), D.end());
    STDV1.assign(D.begin(), D.end());
    EXPECT_EQ(V1, STDV1);
    

    for (int i = 0; i < 100; ++i){
        int a = rnd() % (V1.size() / 2 - 1) + 1;
        int b = -(rnd() % (V1.size() / 2 - 1) + 1);
        auto iter = V1.begin();
        iter += a;
        EXPECT_EQ(*(iter), V1[a]);
        auto iter2 = V1.end();
        EXPECT_EQ(*(iter2 - a), V1[V1.size() - a]);
        iter2 -= b;
    }
}


TEST(Manual, Capacity)
{
    deque<long> D;
    for (int i = 0; i < 1000 + rnd() % 3000; ++i){
        D.push_back(rnd()); 
        if (rnd() % 2)
            D.push_front(rnd());
    }
    vector<long> V1, V2, V3;
    std::vector<long> STDV1, STDV2, STDV3;
    V1.assign(D.begin(), D.end());
    STDV1.assign(D.begin(), D.end());
    EXPECT_EQ(V1, STDV1);
    
    EXPECT_EQ(V1.size(), STDV1.size());
    //EXPECT_EQ(V1.max_size(), STDV1.max_size());
    int a = rnd() % 50000;
    V1.reserve(a);
    EXPECT_EQ(V1.capacity(), a);
    V1.shrink_to_fit();
    STDV1.shrink_to_fit();

    EXPECT_EQ(V1, STDV1);
}

TEST(Manual, Modifiers)
{
    deque<long> D;
    for (int i = 0; i < 1000 + rnd() % 3000; ++i){
        D.push_back(rnd()); 
        if (rnd() % 2)
            D.push_front(rnd());
    }
    vector<long> V1, V2, V3;
    std::vector<long> STDV1, STDV2, STDV3;
    V1.assign(D.begin(), D.end());
    STDV1.assign(D.begin(), D.end());
    EXPECT_EQ(V1, STDV1);
    
    V2 = V1;
    STDV2 = STDV1;
    V2.clear();
    STDV2.clear();
    EXPECT_EQ(V2, STDV2);

    int a = rnd() % 200;
    int b = rnd();
    V2 = V1;
    STDV2 = STDV1;

    /*          //TODO write insert and tests for insert() (and emplace() and erase())
    V2.insert(V2.begin() + a, b);
    STDV2.insert(STDV2.begin() + a, b);
    EXPECT_EQ(V2, STDV2);
    EXPECT_NE(V2, V1);
    */
    
    V2.push_back(b);
    STDV2.push_back(b);
    
    EXPECT_EQ(V2, STDV2);
    EXPECT_NE(V2, V1);
    V2.pop_back();
    STDV2.pop_back();
    EXPECT_EQ(V2, V1);
    
    //V2.resize(V2.size() + a);     //TODO fix resize
    //STDV2.resize(STDV2.size() + a);
    EXPECT_EQ(V2, STDV2);

    V2.resize(V2.size() + a, b);
    STDV2.resize(STDV2.size() + a, b);
    //EXPECT_EQ(V2, STDV2);

    V2 = V1;
    STDV2 = STDV1;

    a = rnd() % 600;
    V2.resize(V2.size() - a);
    STDV2.resize(STDV2.size() - a);
    // EXPECT_EQ(V2, STDV2);

    V2 = V1;
    STDV2 = STDV1;

    V2[a] = b;
    STDV2[a] = b;

    swap(V1, V2);
    std::swap(STDV1, STDV2);
    EXPECT_EQ(V1, STDV1);
    EXPECT_EQ(V2, STDV2);
    EXPECT_NE(V1, V2);
} 


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
