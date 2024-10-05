#include "utpch.h"

#include <iostream>

#include "SingletonTest.h"

/*
 * SingletonTest_01
 */
TEST(SingletonTest, SingletonTest_01)
{
    using namespace BulletFarm;

    EXPECT_EQ(SingletonManager::GetInstance().SingletonCounter(), 0);
}

/*
 * SingletonTest_02
 */
TEST(SingletonTest, SingletonTest_02)
{
    using namespace BulletFarm;
    using namespace std;

    TestSingleton1::GetInstance();
    TestSingleton2::GetInstance();

    EXPECT_EQ(SingletonManager::GetInstance().SingletonCounter(), 2);
}