#pragma once

// clang-format off

#define GENERATE_TYPE_INFO(_type) \
public: \
    using Super = SuperClassDeduction<_type>::Type; \
    using This = _type; \
\
public: \
    static const Type& StaticType() \
    { \
        static Type s_Type(TypeGenerator<This>(#_type)); \
        return s_Type; \
    } \
\
    virtual const Type& GetType() const \
    { \
        return m_Type; \
    } \
\
private: \
    inline static const Type& m_Type = StaticType(); \

// clang-format on
