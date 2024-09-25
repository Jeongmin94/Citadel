#include "Platform/IDebug.h"

namespace V8
{

class WindowsDebug : public IDebug
{
public:
    ~WindowsDebug(){};

public:
    virtual void IncludeDebugHeader() override;
    virtual void InitDebug() override;
    virtual void CatchDebug() override;
};

} // namespace V8