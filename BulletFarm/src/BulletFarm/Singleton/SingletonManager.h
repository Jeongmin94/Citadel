#pragma once

#include <memory>
#include <unordered_map>

namespace BulletFarm
{
class SingletonBase;

class SingletonManager
{
private:
    SingletonManager(const SingletonManager&) = delete;
    SingletonManager& operator=(const SingletonManager&) = delete;

public:
    SingletonManager() = default;
    ~SingletonManager() = default;

public:
    static SingletonManager& GetInstance();

public:
    size_t RegisterSingleton(SingletonBase*);
    void InitSingletons();
    void DeleteSingletons();

    SingletonBase* GetSingleton(size_t id);

private:
    static size_t s_SingletonId;

    using SingletonMap =
        std::unordered_map<size_t, std::shared_ptr<SingletonBase>>;
    SingletonMap m_Singletons;
};

} // namespace BulletFarm