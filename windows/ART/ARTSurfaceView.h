#pragma once

#include "pch.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "ARTSurfaceView.g.h"

namespace winrt::ART::implementation
{

    class ARTSurfaceView : public ARTSurfaceViewT<ARTSurfaceView>
    {
    public:
        ARTSurfaceView(Microsoft::ReactNative::IReactContext const& reactContext);
        void invalidate();

        Microsoft::ReactNative::IReactContext RNContext()
        {
            return m_reactContext;
        };
        void RNContext(Microsoft::ReactNative::IReactContext const& value)
        {
            m_reactContext = value;
        };

        void addChild(Windows::UI::Xaml::UIElement const& child, int64_t index);
        void removeAllChildren();
        void removeChildAt(int64_t index);
        void replaceChild(Windows::UI::Xaml::UIElement const& oldChild, Windows::UI::Xaml::UIElement const& newChild);

    private:
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
        IVector<Windows::UI::Xaml::UIElement> m_children{ winrt::single_threaded_vector<Windows::UI::Xaml::UIElement>() };

        Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl mCanvasControl;
        void OnCanvasDraw(Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const&, Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const&);
        void OnCanvasSizeChanged(const winrt::Windows::Foundation::IInspectable, Windows::UI::Xaml::SizeChangedEventArgs const&);
        Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl::Draw_revoker mCanvasDrawRevoker{};
        Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl::SizeChanged_revoker mCanvaSizeChangedRevoker{};
        int mOriginalWidth, mOriginalHeight;

    };
}

namespace winrt::ART::factory_implementation
{
    struct ARTSurfaceView : ARTSurfaceViewT<ARTSurfaceView, implementation::ARTSurfaceView> {};
}
