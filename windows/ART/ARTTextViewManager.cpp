#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "ARTTextViewManager.h"
#include "ARTText.h"

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
    using namespace Windows::UI;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
}

namespace winrt::ART::implementation
{
    // IViewManager
    winrt::hstring ARTTextViewManager::Name() noexcept
    {
        return L"ARTText";
    }

    winrt::FrameworkElement ARTTextViewManager::CreateView() noexcept
    {
        return winrt::ART::ARTText(m_reactContext);
    }

    // IViewManagerWithReactContext
    winrt::IReactContext ARTTextViewManager::ReactContext() noexcept
    {
        return m_reactContext;
    }

    void ARTTextViewManager::ReactContext(IReactContext reactContext) noexcept
    {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> ARTTextViewManager::NativeProps() noexcept
    {
        return winrt::ART::implementation::ARTText::NativeProps();
    }

    void ARTTextViewManager::UpdateProperties(
        FrameworkElement const& view,
        IJSValueReader const& propertyMapReader) noexcept
    {
        if (auto const& module = view.try_as<winrt::ART::ARTText>())
        {
            module.UpdateProperties(propertyMapReader);
        }
    }

}
