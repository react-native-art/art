#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "ARTSurfaceViewManager.h"
#include "ARTSurfaceView.h"

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
    winrt::hstring ARTSurfaceViewManager::Name() noexcept
    {
        return L"ARTSurfaceView";
    }

    winrt::FrameworkElement ARTSurfaceViewManager::CreateView() noexcept
    {
        return winrt::ART::ARTSurfaceView(m_reactContext);
    }

    // IViewManagerWithReactContext
    winrt::IReactContext ARTSurfaceViewManager::ReactContext() noexcept
    {
        return m_reactContext;
    }

    void ARTSurfaceViewManager::ReactContext(IReactContext reactContext) noexcept
    {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> ARTSurfaceViewManager::NativeProps() noexcept
    {
        // TODO: define props here
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
        return nativeProps.GetView();
    }

    void ARTSurfaceViewManager::UpdateProperties(
        FrameworkElement const& view,
        IJSValueReader const& propertyMapReader) noexcept
    {
        /*
        if (auto module = view.try_as<winrt::ART::ARTModule>())
        {
            module.UpdateProperties(propertyMapReader);
        }
        */
    }

    // IViewManagerWithChildren
    void ARTSurfaceViewManager::AddView(winrt::Windows::UI::Xaml::FrameworkElement const& parent, winrt::Windows::UI::Xaml::UIElement const& child, int64_t index) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.addChild(child, index);
        }
    }

    void ARTSurfaceViewManager::RemoveAllChildren(winrt::Windows::UI::Xaml::FrameworkElement const& parent) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.removeAllChildren();
        }
    }

    void ARTSurfaceViewManager::RemoveChildAt(winrt::Windows::UI::Xaml::FrameworkElement const& parent, int64_t index) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.removeChildAt(index);
        }
    }

    void ARTSurfaceViewManager::ReplaceChild(winrt::Windows::UI::Xaml::FrameworkElement const& parent, winrt::Windows::UI::Xaml::UIElement const& oldChild, winrt::Windows::UI::Xaml::UIElement const& newChild) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.replaceChild(oldChild, newChild);
        }
    }
}
