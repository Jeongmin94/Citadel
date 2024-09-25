#pragma once

#include "V8/Application.h"
#include "V8/Core/Input.h"
#include "V8/Core/Layer.h"
#include "V8/GUI/ImGuiLayer.h"
#include "V8/Utils/Log.h"

#include "Platform/ServiceLocatorHelper.h"

// Entry Point for Client
#ifndef UNIT_TEST
#include "V8/Core/EntryPoint.h"
#endif