#include "pch.h"
#include "NativeModules.h"
#include "JSValueXaml.h"
#include "ARTGroupViewManager.h"
#include "ARTGroup.h"

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
    winrt::hstring ARTGroupViewManager::Name() noexcept
    {
        return L"ARTGroup";
    }

    winrt::FrameworkElement ARTGroupViewManager::CreateView() noexcept
    {
        return winrt::ART::ARTGroup(m_reactContext);
    }

    // IViewManagerWithReactContext
    winrt::IReactContext ARTGroupViewManager::ReactContext() noexcept
    {
        return m_reactContext;
    }

    void ARTGroupViewManager::ReactContext(IReactContext reactContext) noexcept
    {
        m_reactContext = reactContext;
    }

    // IViewManagerWithNativeProperties
    IMapView<hstring, ViewManagerPropertyType> ARTGroupViewManager::NativeProps() noexcept
    {
        return winrt::ART::implementation::ARTGroup::NativeProps();
    }

    void ARTGroupViewManager::UpdateProperties(
        FrameworkElement const& view,
        IJSValueReader const& propertyMapReader) noexcept
    {
        if (auto const& module = view.try_as<winrt::ART::ARTGroup>())
        {
            module.UpdateProperties(propertyMapReader);
        }
    }

    // IViewManagerWithChildren
    void ARTGroupViewManager::AddView(winrt::Windows::UI::Xaml::FrameworkElement const& parent, winrt::Windows::UI::Xaml::UIElement const& child, int64_t index) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.addChild(child, index);
        }
    }

    void ARTGroupViewManager::RemoveAllChildren(winrt::Windows::UI::Xaml::FrameworkElement const& parent) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.removeAllChildren();
        }
    }

    void ARTGroupViewManager::RemoveChildAt(winrt::Windows::UI::Xaml::FrameworkElement const& parent, int64_t index) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.removeChildAt(index);
        }
    }

    void ARTGroupViewManager::ReplaceChild(winrt::Windows::UI::Xaml::FrameworkElement const& parent, winrt::Windows::UI::Xaml::UIElement const& oldChild, winrt::Windows::UI::Xaml::UIElement const& newChild) noexcept
    {
        if (auto const& container = parent.try_as<ARTContainer>())
        {
            container.replaceChild(oldChild, newChild);
        }
    }
}
