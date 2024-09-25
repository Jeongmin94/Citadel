#pragma once

#include "IDebug.h"

namespace V8
{

class ServiceLocatorHelper
{
public:
    static BulletFarm::ServiceLocator* Get();
    static void InitLocator(BulletFarm::ServiceLocator* locator);
};

} // namespace V8