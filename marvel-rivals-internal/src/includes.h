#pragma once

#include <ios>
#include <iostream>
#include <thread>
#include <vector>
#include <cstdint>
#include <chrono>

#define NOMINMAX
#include <Windows.h>

#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_impl_win32.h"
#include "dependencies/imgui/imgui_impl_dx12.h"
#include <psapi.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")

#include "SDK/Engine_parameters.hpp"
#include "SDK/Engine_classes.hpp"
#include "SDK/Marvel_classes.hpp"
#include "SDK/GameplayCameras_parameters.hpp"
#include "SDK/GameplayCameras_classes.hpp"

#include "SDK Functions/custom.h"
#include "globals.h"

#include "dependencies/msdetours.h"
#pragma comment(lib, "detours.lib")

#include "config.h"
#include "Render/render.h"
#include "dx12hook.h"

#include "hooks.h"