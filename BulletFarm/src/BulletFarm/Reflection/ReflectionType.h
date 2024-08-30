#pragma once

#include <string>

namespace BulletFarm
{

namespace Reflection
{
class Type
{
public:
    template <typename T>
    explicit Type(){};

private:
    size_t m_TypeHash;
    const char* m_Name;
    std::string m_FullName;
    const Type* m_Super;
};
} // namespace Reflection

} // namespace BulletFarm