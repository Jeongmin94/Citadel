#pragma once

#include <BulletFarm.h>

class TestSingleton1 : public BulletFarm::Singleton<TestSingleton1>
{
public:
    TestSingleton1() = default;
};

class TestSingleton2 : public BulletFarm::Singleton<TestSingleton2>
{
public:
    TestSingleton2() = default;
};
