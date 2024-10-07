#include "bfpch.h"

#include "ServiceLocator.h"

namespace BulletFarm
{

void ServiceLocator::Clear()
{
    m_InstanceMap.clear();
    m_InitializerMap.clear();
}

} // namespace BulletFarm
