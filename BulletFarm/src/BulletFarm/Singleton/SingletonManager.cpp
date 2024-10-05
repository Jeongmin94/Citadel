#include "bfpch.h"

#include "SingletonManager.h"

#include "Singleton.h"

namespace BulletFarm
{

size_t SingletonManager::s_SingletonId = 0;

SingletonManager& SingletonManager::GetInstance()
{
    static SingletonManager s_Manager;
    return s_Manager;
}

size_t SingletonManager::RegisterSingleton(SingletonBase* singletonBase)
{
    m_Singletons.emplace(s_SingletonId,
                         std::shared_ptr<SingletonBase>(singletonBase));

    return s_SingletonId++;
}

void SingletonManager::InitSingletons()
{
    for (auto& kv : m_Singletons)
    {
        kv.second->Init();
    }
}

void SingletonManager::DeleteSingletons()
{
    for (auto& kv : m_Singletons)
    {
        kv.second->Delete();
    }
}

SingletonBase* SingletonManager::GetSingleton(size_t id)
{
    if (m_Singletons.find(id) == m_Singletons.end())
    {
        return nullptr;
    }

    return m_Singletons[id].get();
}

} // namespace BulletFarm
