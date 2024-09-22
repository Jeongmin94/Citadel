#pragma once

#include <string>

#include "BulletFarm/PrimitiveTypes.h"

namespace V8
{

// Interface for Shader
class IShader
{
public:
    IShader(const std::string& vertexSrc, const std::string& pixelSrc);
    virtual ~IShader();

public:
    void Bind() const;
    void UnBind() const;

private:
    uint32 m_RendererId;
};

} // namespace V8