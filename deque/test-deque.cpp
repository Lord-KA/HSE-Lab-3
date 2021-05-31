#include "deque.hpp"

#include <random>
#include <deque>
#include "gtest/gtest.h"


std::mt19937 rnd(179);

template<typename T>
void PushAndPopTest()
{
    std::deque<T> STD1;
    deque<T> D1;
    for (int i = 0; i < rnd() % 30000 + 150; ++i){
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


template<typename T>
void CopyAndMoveTest()
{
    std::deque<T> STD1, STD2;
    deque<T> D1, D2;
    for (int i = 0; i < rnd() % 30000 + 150; ++i){
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

    deque<T> D3(D2);
    std::deque<T> STD3(STD2);
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

    deque<T> D4(std::move(D2)), D5, D6;
    std::deque<T> STD4(std::move(STD2)), STD5, STD6;

    D5 = std::move(D3);
    STD5 = std::move(STD3);
    
    a = rnd();
    D5[17] = a;
    STD5[17] = a;
    D6 = D5;
    STD6 = STD5;

    EXPECT_EQ(D4, STD4);
    EXPECT_EQ(D5, STD5);   
    EXPECT_EQ(D6, STD6);   
}


template<typename T>
void ForwardIteratorTest()
{
    deque<long> D1;
    for (int i = 0; i < 1000 + rnd() % 3000; ++i){
        D1.push_back(rnd());
        if (rnd() % 2)
            D1.push_front(rnd());
    }
    
    size_t i = 0;
    for (auto elem : D1){
        EXPECT_EQ(elem, D1[i]);
        ++i;
    }
}


template<typename T>
void BackwardIteratorTest()
{
    deque<T> D1;
    for (int i = 0; i < 1000 + rnd() % 3000; ++i){
        D1.push_back(rnd()); 
        if (rnd() % 2)
            D1.push_front(rnd());
    }
 
    auto iter = D1.end();
    size_t i = D1.size();
    while (i){
        --iter;
        --i;
        EXPECT_EQ(*iter, D1[i]);
    }
}


template<typename T>
void RandomAccessIteratorTest()
{
    deque<long> D1;
    for (int i = 0; i < 1000 + rnd() % 3000; ++i){
        D1.push_back(rnd()); 
        if (rnd() % 2)
            D1.push_front(rnd());
    }
    for (int i = 0; i < 100; ++i){
        int a = rnd() % (D1.size() / 2 - 1) + 1;
        int b = rnd() % (D1.size() / 2 - 1) + 1;
        auto iter = D1.begin();
        iter += a;
        EXPECT_EQ(*(iter + b), D1[a + b]);
        auto iter2 = D1.end();
        iter2 -= b;
        EXPECT_EQ(*(iter2 - a), D1[D1.size() - a - b]);
    }
}




TEST(Basics, PushAndPop)
{
    for (int p = 0; p < 50; ++p){
        PushAndPopTest<int>();
        PushAndPopTest<long>();
        PushAndPopTest<unsigned long long>();
        PushAndPopTest<double>();
        PushAndPopTest<float>();

        #ifdef NDEBUG
        PushAndPopTest<short>();
        PushAndPopTest<char>();
        PushAndPopTest<bool>();
        #endif
    }
}

TEST(Basics, CopyAndMove){
    for (int p = 0; p < 50; ++p){
        CopyAndMoveTest<int>();
        CopyAndMoveTest<long>();
        CopyAndMoveTest<unsigned long long>();
        CopyAndMoveTest<double>();
        CopyAndMoveTest<float>();

        #ifdef NDEBUG
        CopyAndMoveTest<short>();
        CopyAndMoveTest<char>();
        CopyAndMoveTest<bool>();
        #endif
 
    }
}

TEST(Iterators, ForwardIterator){
    for (int p = 0; p < 20; ++p){
        ForwardIteratorTest<int>();
        ForwardIteratorTest<long>();
        ForwardIteratorTest<unsigned long long>();
        ForwardIteratorTest<double>();
        ForwardIteratorTest<float>();

        #ifdef NDEBUG
        ForwardIteratorTest<short>();
        ForwardIteratorTest<char>();
        ForwardIteratorTest<bool>();
        #endif
    }
}

TEST(Iterators, BackwardIterator){
    for (int p = 0; p < 20; ++p){
        BackwardIteratorTest<int>();
        BackwardIteratorTest<long>();
        BackwardIteratorTest<unsigned long long>();
        BackwardIteratorTest<double>();
        BackwardIteratorTest<float>();

        #ifdef NDEBUG
        BackwardIteratorTest<short>();
        BackwardIteratorTest<char>();
        BackwardIteratorTest<bool>();
        #endif
    }
}

TEST(Iterators, RandomAccessIterator){
    for (int p = 0; p < 20; ++p){
        RandomAccessIteratorTest<int>();
        RandomAccessIteratorTest<long>();
        RandomAccessIteratorTest<unsigned long long>();
        RandomAccessIteratorTest<double>();
        RandomAccessIteratorTest<float>();

        #ifdef NDEBUG
        RandomAccessIteratorTest<short>();
        RandomAccessIteratorTest<char>();
        RandomAccessIteratorTest<bool>();
        #endif
    }
}
