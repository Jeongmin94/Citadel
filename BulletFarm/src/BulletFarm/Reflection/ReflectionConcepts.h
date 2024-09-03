#pragma once

#include <concepts>

namespace Reflection
{
template <typename T>
concept HasSuper =
    requires { typename T::Super; } && !std::same_as<typename T::Super, void>;
}