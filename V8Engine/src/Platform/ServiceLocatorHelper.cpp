#include "v8pch.h"

#include "ServiceLocatorHelper.h"

#include "PlatformInclude.h"

namespace V8
{

BulletFarm::ServiceLocator& ServiceLocatorHelper::Get()
{
    static BulletFarm::ServiceLocator locator;

    return locator;
}

void ServiceLocatorHelper::InitLocator(BulletFarm::ServiceLocator& locator)
{
#ifdef V8_PLATFORM_WINDOWS
    locator.RegisterInstance<IDebug>(new WindowsDebug);
#elif V8_PLATFORM_MAC
    locator.RegisterInstance<IDebug>(new MacDebug);
#else
    #error Not Supported OS!
#endif
}

} // namespace V8