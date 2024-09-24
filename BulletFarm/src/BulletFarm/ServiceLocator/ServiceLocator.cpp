#include "ServiceLocator.h"

BulletFarm::ServiceLocator::ServiceLocator()
    : m_InitializerMap(), m_InstanceMap()
{
}

BulletFarm::ServiceLocator::~ServiceLocator() {}

void BulletFarm::ServiceLocator::Clear()
{
    m_InstanceMap.clear();
    m_InitializerMap.clear();
}