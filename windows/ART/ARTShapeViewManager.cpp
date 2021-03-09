#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "ARTShapeViewManager.h"
#include "ARTShape.h"

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
    winrt::hstring ARTShapeViewManager::Name() noexcept
    {
        return L"ARTShape";
    }

    winrt::FrameworkElement ARTShapeViewManager::CreateView() noexcept
    {
        return winrt::ART::ARTShape(m_reactContext);
    }

    // IViewManagerWithReactContext
    winrt::IReactContext ARTShapeViewManager::ReactContext() noexcept
    {
        return m_reactContext;
    }

    void ARTShapeViewManager::ReactContext(IReactContext reactContext) noexcept
    {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> ARTShapeViewManager::NativeProps() noexcept
    {
        return winrt::ART::implementation::ARTShape::NativeProps();
    }

    void ARTShapeViewManager::UpdateProperties(
        FrameworkElement const& view,
        IJSValueReader const& propertyMapReader) noexcept
    {
        if (auto const &module = view.try_as<winrt::ART::ARTShape>())
        {
            module.UpdateProperties(propertyMapReader);
        }
    }

}
