#include "utpch.h"

#include "BulletFarm/ReflectionTest.h"
#include "BulletFarm/SingletonTest.h"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    V8::Log::Init();

    return RUN_ALL_TESTS();
}