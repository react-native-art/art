#pragma once
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"


namespace winrt::ART::implementation
{

    class ARTGroupViewManager : public winrt::implements<
        ARTGroupViewManager,
        winrt::Microsoft::ReactNative::IViewManager,
        winrt::Microsoft::ReactNative::IViewManagerWithReactContext,
        winrt::Microsoft::ReactNative::IViewManagerWithNativeProperties,
        winrt::Microsoft::ReactNative::IViewManagerWithChildren>
    {
    public:
        ARTGroupViewManager() = default;

        // IViewManager
        winrt::hstring Name() noexcept;
        winrt::Windows::UI::Xaml::FrameworkElement CreateView() noexcept;

        // IViewManagerWithReactContext
        winrt::Microsoft::ReactNative::IReactContext ReactContext() noexcept;
        void ReactContext(winrt::Microsoft::ReactNative::IReactContext reactContext) noexcept;

        // IViewManagerWithNativeProperties
        winrt::Windows::Foundation::Collections::
            IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
            NativeProps() noexcept;

        void UpdateProperties(
            winrt::Windows::UI::Xaml::FrameworkElement const& view,
            winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept;

        // IViewManagerWithChildren
        void AddView(
            winrt::Windows::UI::Xaml::FrameworkElement const& parent,
            winrt::Windows::UI::Xaml::UIElement const& child,
            int64_t index) noexcept;

        void RemoveAllChildren(winrt::Windows::UI::Xaml::FrameworkElement const& parent) noexcept;

        void RemoveChildAt(winrt::Windows::UI::Xaml::FrameworkElement const& parent, int64_t index) noexcept;

        void ReplaceChild(
            winrt::Windows::UI::Xaml::FrameworkElement const& parent,
            winrt::Windows::UI::Xaml::UIElement const& oldChild,
            winrt::Windows::UI::Xaml::UIElement const& newChild) noexcept;


    private:
        winrt::Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
    };
}
