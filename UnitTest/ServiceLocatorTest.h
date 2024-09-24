#pragma once

#include <BulletFarm.h>

#include <iostream>

class IMathService
{
public:
    IMathService() = default;
    virtual ~IMathService() = default;

public:
    virtual int add(int a, int b) = 0;
    virtual int sub(int a, int b) = 0;
};

class MathServiceImpl : public IMathService
{
public:
    virtual ~MathServiceImpl() override
    {
        CLI_DEBUG("MathServiceImpl Destoryer Called");
    }

public:
    virtual int add(int a, int b) override { return a + b; }
    virtual int sub(int a, int b) override { return a - b; }
};
