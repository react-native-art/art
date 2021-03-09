#pragma once
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"


namespace winrt::ART::implementation {
    
    class ARTViewManager : public winrt::implements<
        ARTViewManager,
        winrt::Microsoft::ReactNative::IViewManager,
        winrt::Microsoft::ReactNative::IViewManagerWithReactContext,
        winrt::Microsoft::ReactNative::IViewManagerWithNativeProperties,
        winrt::Microsoft::ReactNative::IViewManagerWithExportedEventTypeConstants,
        winrt::Microsoft::ReactNative::IViewManagerWithCommands /*,
        winrt::Microsoft::ReactNative::IViewManagerWithChildren */> {
    public:
        ARTViewManager() = default;
        /*
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
        };
        */
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

        // IViewManagerWithExportedEventTypeConstants
        winrt::Microsoft::ReactNative::ConstantProviderDelegate ExportedCustomBubblingEventTypeConstants() noexcept;
        winrt::Microsoft::ReactNative::ConstantProviderDelegate ExportedCustomDirectEventTypeConstants() noexcept;


        // IViewManagerWithCommands
        winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> Commands() noexcept;

        void DispatchCommand(
            winrt::Windows::UI::Xaml::FrameworkElement const &view,
            winrt::hstring const &commandId,
            winrt::Microsoft::ReactNative::IJSValueReader const &commandArgsReader) noexcept;

    private:
        winrt::Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
    };
}
