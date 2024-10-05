#pragma once

#include <BulletFarm.h>

class TestSingleton1 : public BulletFarm::Singleton<TestSingleton1>
{
};

class TestSingleton2 : public BulletFarm::Singleton<TestSingleton2>
{
};
