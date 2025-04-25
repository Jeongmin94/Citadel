#pragma once

#include "Platform/IDebug.h"

namespace V8
{

class MacDebug: public IDebug
{
public:
    virtual ~MacDebug() override = default;

public:
    virtual void IncludeDebugHeader() override;
    virtual void InitDebug() override;
    virtual void CatchDebug() override;
};


}
