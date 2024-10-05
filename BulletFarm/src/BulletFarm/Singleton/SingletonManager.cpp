#include "bfpch.h"

#include "SingletonManager.h"

#include "Singleton.h"

namespace BulletFarm
{

int32 SingletonManager::s_SingletonCounter = 0;

SingletonManager& SingletonManager::GetInstance()
{
    static SingletonManager s_Manager;
    return s_Manager;
}

int32 SingletonManager::RegisterSingleton(SingletonBase* singletonBase)
{
    singletonBase->Init();
    m_Singletons.emplace(++s_SingletonCounter, singletonBase);

    return s_SingletonCounter;
}

void SingletonManager::DeleteSingletons()
{
    for (auto& kv : m_Singletons)
    {
        kv.second->Delete();
    }
}

SingletonBase* SingletonManager::GetSingleton(int32 id)
{
    if (m_Singletons.find(id) == m_Singletons.end())
    {
        return nullptr;
    }

    return m_Singletons[id];
}

} // namespace BulletFarm
