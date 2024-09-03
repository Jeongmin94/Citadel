#pragma once

// clang-format off

#define GENERATE_TYPE_INFO(_type) \
public: \
    using Super = SuperClassDeduction<_type>::Type; \
    using This = _type; \
\
public: \
    static Type& StaticType() \
    { \
        static Type s_Type(TypeGenerator<This>(#_type)); \
        return s_Type; \
    } \


// clang-format on
