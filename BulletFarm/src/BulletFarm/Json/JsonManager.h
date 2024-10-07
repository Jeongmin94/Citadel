#pragma once

#include <fstream>
#include <string>

#include "BulletFarm/Singleton/Singleton.h"

#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;

namespace BulletFarm
{

class JsonManager : public Singleton<JsonManager>
{
    MAKE_NO_COPY(JsonManager);

public:
    JsonManager() = default;
};

} // namespace BulletFarm