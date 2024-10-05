#pragma once

#include "SingletonManager.h"

namespace BulletFarm
{

class SingletonBase
{
private:
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

public:
    SingletonBase() = default;
    virtual ~SingletonBase() = default;

public:
    virtual void Init() = 0;
    virtual void Delete() = 0;
    virtual int32 GetId() const = 0;
};

template <typename T>
class Singleton : public SingletonBase
{
private:
    Singleton(const T&) = delete;
    Singleton& operator=(const T&) = delete;

protected:
    Singleton()
    {
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
    virtual void Init() override {}
    virtual void Delete() override {}
    virtual int32 GetId() const override { return s_SingletonId; }

private:
    static int32 s_SingletonId;
};

template <typename T>
int32 Singleton<T>::s_SingletonId = -1;

} // namespace BulletFarm
