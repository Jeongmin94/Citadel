#include "bfpch.h"

#include "ServiceLocator.h"

namespace BulletFarm
{

ServiceLocator::ServiceLocator() : m_InitializerMap(), m_InstanceMap() {}

ServiceLocator::~ServiceLocator() {}

void ServiceLocator::Clear()
{
    m_InstanceMap.clear();
    m_InitializerMap.clear();
}

} // namespace BulletFarm
