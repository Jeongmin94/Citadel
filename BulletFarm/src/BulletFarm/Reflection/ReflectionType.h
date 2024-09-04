#pragma once

#include <sstream>
#include <string>

#include "ReflectionConcepts.h"

template <typename T>
class SuperClassDeduction
{
public:
    // primitive template
    template <typename U, typename V = void>
    struct Deductor
    {
        using Type = void;
    };

    template <typename U>
    struct Deductor<U, std::void_t<typename U::This>>
    {
        using Type = U::This;
    };

    using Type = Deductor<T>::Type;
};

class Type;

// Type Generator
template <typename T>
struct TypeGenerator
{
    TypeGenerator(const char* _name) : m_Name(_name)
    {
        if constexpr (Reflection::HasSuper<T>)
        {
            m_SuperType = &(typename T::Super::StaticType());
        }
        else
        {
            m_SuperType = nullptr;
        }
    }

    const char* m_Name;
    const Type* m_SuperType;
};

// Metadata
class Type
{
private:
    Type(const Type& ref) = delete;
    Type& operator=(const Type& ref) = delete;

public:
    template<typename T>
    explicit Type(const TypeGenerator<T>& _generator)
    {
        m_Name = _generator.m_Name;
        m_FullName = typeid(T).name();
        m_TypeHash = typeid(T).hash_code();
        m_Super = _generator.m_SuperType;
    }

public:
    std::string ToString() const
    {
        std::stringstream ss;
        ss << m_FullName << "( " << m_TypeHash << " )";
        return ss.str();
    }

    const size_t GetTypeHash() const { return m_TypeHash; }
    const Type& GetSuper() const { return *m_Super; }

private:
    const char* m_Name;
    const char* m_FullName;
    size_t m_TypeHash;
    const Type* m_Super;
};
