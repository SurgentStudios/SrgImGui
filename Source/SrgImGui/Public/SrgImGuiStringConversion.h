// © Surgent Studios

#pragma once

#include "CoreMinimal.h"

#define TO_IMGUI(Str) reinterpret_cast<const ANSICHAR*>(StringCast<UTF8CHAR>(Str).Get())
#define FROM_IMGUI(Str) StringCast<TCHAR>(Str).Get()