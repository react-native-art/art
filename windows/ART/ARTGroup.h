#pragma once

#include "pch.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "ARTGroup.g.h"

namespace winrt::ART::implementation
{

    class ARTGroup : public ARTGroupT<ARTGroup>
    {
    public:
        ARTGroup(Microsoft::ReactNative::IReactContext const& reactContext);
        void invalidate();

        void renderTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session);

        Microsoft::ReactNative::IReactContext RNContext() { return m_reactContext; }
        void RNContext(Microsoft::ReactNative::IReactContext const& value) { m_reactContext = value; };

        static winrt::Windows::Foundation::Collections::
            IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
            NativeProps() noexcept;
        void UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept;

        ARTContainer ARTParent() { return m_parent; }
        void ARTParent(ARTContainer const& value) { m_parent = value; };
        
        void addChild(Windows::UI::Xaml::UIElement const& child, int64_t index);
        void removeAllChildren();
        void removeChildAt(int64_t index);
        void replaceChild(Windows::UI::Xaml::UIElement const& oldChild, Windows::UI::Xaml::UIElement const& newChild);

    private:
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };

        ARTContainer m_parent{ nullptr };
        IVector<Windows::UI::Xaml::UIElement> m_children{ winrt::single_threaded_vector<Windows::UI::Xaml::UIElement>() };

        float m_opacity = 1;
        std::optional<Windows::Foundation::Numerics::float3x2> m_transform;
        
        std::optional<Windows::Foundation::Rect> m_clipping;
        std::optional<Windows::Foundation::Rect> createClipping(std::vector<float> data);

        void renderLayerTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session);

    };
}



namespace winrt::ART::factory_implementation
{
    struct ARTGroup : ARTGroupT<ARTGroup, implementation::ARTGroup> {};
}
