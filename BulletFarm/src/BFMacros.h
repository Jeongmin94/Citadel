#pragma once

/**
 * Singleton Macros
 */
#define MAKE_NO_COPY(CLASSNAME)                                                \
private:                                                                       \
    CLASSNAME(const CLASSNAME&) = delete;                                      \
    CLASSNAME& operator=(const CLASSNAME&) = delete;

/**
 * For Non-template Singleton 
 */
#define DECL_SINGLETON(CLASSNAME)                                              \
    MAKE_NO_COPY(CLASSNAME)                                                    \
private:                                                                       \
    CLASSNAME() = default;                                                     \
                                                                               \
public:                                                                        \
    static CLASSNAME& GetInstance();

#define IMPL_SINGLETON(CLASSNAME)                                              \
    CLASSNAME& CLASSNAME::GetInstance()                                        \
    {                                                                          \
        static CLASSNAME s_Instance;                                           \
        return s_Instance;                                                     \
    }