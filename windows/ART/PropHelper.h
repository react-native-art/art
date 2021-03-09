#pragma once
#include "pch.h"
#include "NativeModules.h"

namespace winrt::ART::implementation
{
    class PropHelper
    {
    public:
        static std::vector<float> toFloatArray(winrt::Microsoft::ReactNative::JSValueArray const& value);
        static int toFloatArray(winrt::Microsoft::ReactNative::JSValueArray const& value, std::vector<float> & into);
        static std::optional<Windows::Foundation::Numerics::float3x2> to3x2Matrix(winrt::Microsoft::ReactNative::JSValueArray const& value);
        static std::optional<Windows::UI::Color> ParseColor(std::string color);
    };
}
