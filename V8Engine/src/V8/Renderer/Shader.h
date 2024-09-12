#pragma once

#include <string>

#include "BulletFarm/PrimitiveTypes.h"

namespace V8
{

// Interface for Shader
class Shader
{
public:
    Shader(const std::string& vertexSrc, const std::string& pixelSrc);
    virtual ~Shader();

public:
    void Bind() const;
    void UnBind() const;

private:
    uint32 m_RendererId;
};

} // namespace V8