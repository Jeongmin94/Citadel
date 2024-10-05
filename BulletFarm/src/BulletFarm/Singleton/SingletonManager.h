#pragma once

#include <unordered_map>

#include "BulletFarm/PrimitiveTypes.h"

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
    static int32 SingletonCounter() { return s_SingletonCounter; }

public:
    int32 RegisterSingleton(SingletonBase*);
    void DeleteSingletons();

    SingletonBase* GetSingleton(int32 id);

private:
    static int32 s_SingletonCounter;

    using SingletonMap = std::unordered_map<int32, SingletonBase*>;
    SingletonMap m_Singletons;
};

} // namespace BulletFarm