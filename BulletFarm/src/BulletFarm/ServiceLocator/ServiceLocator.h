#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

namespace BulletFarm
{

class ServiceLocator
{
public:
    ServiceLocator();
    ~ServiceLocator();

public:
    void Clear();

public:
    template <typename T>
    void RegisterInstance(T* Instance)
    {
        auto hash = typeid(T).hash_code();
        if (m_InstanceMap.find(hash) == m_InstanceMap.end())
        {
            m_InstanceMap.emplace(hash, std::shared_ptr<void>(Instance));
        }
    }

    template <typename T>
    void RegisterInitializer(const std::function<std::shared_ptr<void>()>& func)
    {
        auto hash = typeid(T).hash_code();
        if (m_InitializerMap.find(hash) == m_InitializerMap.end())
        {
            m_InitializerMap.emplace(hash, func);
        }
    }

    template <typename T>
    std::shared_ptr<T> Get()
    {
        auto hash = typeid(T).hash_code();
        if (m_InstanceMap.find(hash) != m_InstanceMap.end())
        {
            return std::static_pointer_cast<T>(m_InstanceMap[hash]);
        }

        if (m_InitializerMap.find(hash) != m_InitializerMap.end())
        {
            return std::static_pointer_cast<T>(m_InitializerMap[hash]());
        }

        return nullptr;
    }

private:
    using InstanceMap = std::unordered_map<size_t, std::shared_ptr<void>>;
    using InitializerMap =
        std::unordered_map<size_t, std::function<std::shared_ptr<void>()>>;

    InstanceMap m_InstanceMap;
    InitializerMap m_InitializerMap;
};

} // namespace BulletFarm
