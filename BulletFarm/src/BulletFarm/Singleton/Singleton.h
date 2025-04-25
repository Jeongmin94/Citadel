#pragma once

#include <cassert>

#include "BFMacros.h"
#include "SingletonManager.h"

namespace BulletFarm
{

class SingletonBase
{
    MAKE_NO_COPY(SingletonBase);

protected:
    SingletonBase() = default;
    virtual ~SingletonBase() = default;

public:
    virtual void Init() = 0;
    virtual void Delete() = 0;
};

template <typename T>
class Singleton : public SingletonBase
{
    MAKE_NO_COPY(Singleton<T>)

protected:
    Singleton()
    {
        assert(s_SingletonId == -1);

        s_SingletonId = SingletonManager::GetInstance().RegisterSingleton(this);
    }
    virtual ~Singleton() = default;

public:
    static T& GetInstance()
    {
        static T s_Instance;

        return s_Instance;
    }

public:
    static int32 Id() { return s_SingletonId; }

    virtual void Init() override {}
    virtual void Delete() override {}

private:
    static int32 s_SingletonId;
};

template <typename T>
int32 Singleton<T>::s_SingletonId = -1;

} // namespace BulletFarm
