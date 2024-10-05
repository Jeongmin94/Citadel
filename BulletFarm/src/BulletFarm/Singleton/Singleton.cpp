#include "bfpch.h"

#include "Singleton.h"

namespace BulletFarm
{

template <typename T>
T* Singleton<T>::s_Instance = nullptr;

}