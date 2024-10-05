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

protected:
    virtual void Init() = 0;
    virtual void Delete() = 0;

    inline void SetId(size_t id) { m_SingletonId = id; }
    inline size_t GetId() const { return m_SingletonId; }

private:
    size_t m_SingletonId;
};

template <typename T>
class Singleton : public SingletonBase
{
private:
    Singleton(const T&) = delete;
    Singleton& operator=(const T&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

public:
    static T& GetInstance() { return *s_Instance; }

public:
    virtual void Init() override
    {
        s_Instance = new T();
        size_t id =
            SingletonManager::GetInstance().RegisterSingleton(s_Instance);
        s_Instance->SetId(id);
    }

    virtual void Delete() override { delete s_Instance; }

private:
    static T* s_Instance;
};

} // namespace BulletFarm
