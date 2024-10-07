#include "bfpch.h"

#include "SingletonInitializer.h"

/*
 * Include Singleton class
 */
#include "BulletFarm/Json/JsonManager.h"

namespace BulletFarm
{

void BulletFarm::InitBulletFarmSingletons()
{
    // Call GetInstance() for Initializing
    JsonManager::GetInstance();
}

} // namespace BulletFarm
