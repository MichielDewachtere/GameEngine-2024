#ifndef STDAFX_H
#define STDAFX_H

#pragma region Windows
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#define NOMINMAX
#pragma endregion

//#define USE_VLD

#pragma region VLD
#if _DEBUG
#ifdef USE_VLD
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#endif
#pragma endregion

#pragma region std

// STREAMS
#include <iostream>
#include <fstream>

#include <stdexcept>

#include <string>

#include <functional>
#include <algorithm>
#include <memory>
#include <chrono>

// CONTAINERS
#include <vector>
#include <array>
#include <map>

#pragma endregion

#pragma region SDL

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#pragma endregion

#pragma region GML

#include <glm/glm.hpp>

#pragma endregion

#pragma region ImGui

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "implot.h"

#pragma endregion

#include "Logger.h"
#include "Utils.h"

#endif // STDAFX_H