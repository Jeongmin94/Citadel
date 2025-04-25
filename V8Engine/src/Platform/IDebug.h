#pragma once

namespace V8
{

class IDebug
{
public:
    virtual ~IDebug() = default;

public:
    virtual void IncludeDebugHeader() = 0;
    virtual void InitDebug() = 0;
    virtual void CatchDebug() = 0;
};

} // namespace V8