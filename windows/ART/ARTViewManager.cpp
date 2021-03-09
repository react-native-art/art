#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "ARTViewManager.h"
#include "ART.h"

namespace winrt {
    using namespace Microsoft::ReactNative;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
    using namespace Windows::UI;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
}

namespace winrt::ART::implementation {
    // IViewManager
    winrt::hstring ARTViewManager::Name() noexcept {
        return L"ART";
    }

    winrt::FrameworkElement ARTViewManager::CreateView() noexcept {
        return winrt::ART::ARTModule(m_reactContext);
    }

    // IViewManagerWithReactContext
    winrt::IReactContext ARTViewManager::ReactContext() noexcept {
        return m_reactContext;
    }

    void ARTViewManager::ReactContext(IReactContext reactContext) noexcept {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> ARTViewManager::NativeProps() noexcept {
        return winrt::ART::implementation::ARTModule::NativeProps();
    }

    void ARTViewManager::UpdateProperties(
        FrameworkElement const& view,
        IJSValueReader const& propertyMapReader) noexcept {
         if (auto module = view.try_as<winrt::ART::ARTModule>()) {
            module.UpdateProperties(propertyMapReader);
        }
    }
    // IViewManagerWithExportedEventTypeConstants
    ConstantProviderDelegate ARTViewManager::ExportedCustomBubblingEventTypeConstants() noexcept {
        return winrt::ART::implementation::ARTModule::ExportedCustomBubblingEventTypeConstants();
    }

    ConstantProviderDelegate ARTViewManager::ExportedCustomDirectEventTypeConstants() noexcept {
       return winrt::ART::implementation::ARTModule::ExportedCustomDirectEventTypeConstants();
    }

    // IViewManagerWithCommands
    IVectorView<hstring> ARTViewManager::Commands() noexcept {
        return winrt::ART::implementation::ARTModule::Commands();
    }

    void ARTViewManager::DispatchCommand(
        FrameworkElement const& view,
        winrt::hstring const& commandId,
        winrt::IJSValueReader const& commandArgsReader) noexcept {
        if (auto module = view.try_as<winrt::ART::ARTModule>()) {
            module.DispatchCommand(commandId, commandArgsReader);
        }
    }
}
