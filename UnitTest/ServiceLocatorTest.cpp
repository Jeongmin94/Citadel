#include "utpch.h"

#include "ServiceLocatorTest.h"

using namespace BulletFarm;

ServiceLocator g_TestLocator;

void InitLocator()
{
    IMathService* func = new MathServiceImpl();

    g_TestLocator.RegisterInstance<IMathService>(func);
    g_TestLocator.RegisterInitializer<MathServiceImpl>(
        []() { return std::make_shared<MathServiceImpl>(); });
}

void ClearLocator() { g_TestLocator.Clear(); }

TEST(ServiceLocator, ServiceLocatorInstanceTest_01)
{
    InitLocator();

    auto mathService = g_TestLocator.Get<IMathService>();

    EXPECT_EQ(mathService->add(1, 2), 3);

    auto newMathService = g_TestLocator.Get<MathServiceImpl>();

    EXPECT_EQ(newMathService->add(1, 2), 3);

    EXPECT_FALSE(mathService.get() == newMathService.get());

    ClearLocator();
}
