#include "pch.h"
#include "ARTGroup.h"
#include "ARTGroup.g.cpp"
#include "PropHelper.h"

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Data::Json;
    using namespace Windows::Foundation;
    using namespace Windows::UI;
    using namespace Windows::UI::Popups;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml::Media;
} // namespace winrt

namespace winrt::ART::implementation
{
    ARTGroup::ARTGroup(Microsoft::ReactNative::IReactContext const& reactContext)
    {
        m_reactContext = reactContext;
    }
    
    void ARTGroup::invalidate()
    {
        if(m_parent != nullptr)
        {
            m_parent.invalidate();
        }
    }

    void ARTGroup::renderTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session)
    {
        auto current_transform = session.Transform();

        if (m_transform.has_value())
        {
            session.Transform(current_transform * m_transform.value());
        }

        if (m_opacity <= 0)
        {
            // Nothing to paint
            return;
        } else if (m_opacity >= 1)
        {
            // Paint at full opacity
            if (m_clipping.has_value())
            {
                const auto& layer = session.CreateLayer(1.0f, m_clipping.value());
                renderLayerTo(session);
            } else
            {
                renderLayerTo(session);
            }
            
            return;
        } else
        {
            if (m_clipping.has_value())
            {
                const auto& layer = session.CreateLayer(m_opacity, m_clipping.value());
                renderLayerTo(session);
            } else
            {
                const auto& layer = session.CreateLayer(m_opacity);
                renderLayerTo(session);
            }
        }

        session.Transform(current_transform);

    }

    void ARTGroup::renderLayerTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session)
    {
        for (const auto &node : m_children)
        {
            if (auto const& art_node = node.try_as<ARTNode>())
            {
                art_node.renderTo(session);
            }
        }

    }

    winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType> ARTGroup::NativeProps() noexcept
    {
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
        //ARTNode
        nativeProps.Insert(L"opacity", ViewManagerPropertyType::Number);
        nativeProps.Insert(L"transform_windows", ViewManagerPropertyType::Array);
        nativeProps.Insert(L"shadow", ViewManagerPropertyType::Array);

        //ARTGroup
        nativeProps.Insert(L"clipping", ViewManagerPropertyType::Array);

        return nativeProps.GetView();
    }

    void ARTGroup::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept
    {
        const JSValueObject& propertyMap = JSValue::ReadObjectFrom(propertyMapReader);
        for (auto const& pair : propertyMap)
        {
            auto const& propertyName = pair.first;
            auto const& propertyValue = pair.second;
            if (propertyName == "opacity")
            {
                if (!propertyValue.IsNull())
                {
                    m_opacity = propertyValue.AsSingle();
                } else
                {
                    m_opacity = 1;
                }
            }
            if (propertyName == "transform_windows")
            {
                if (propertyValue != nullptr)
                {
                    auto const& matrixArray = propertyValue.AsArray();
                    m_transform = PropHelper::to3x2Matrix(matrixArray);
                } else
                {
                    m_transform.reset();
                }
            }
            if (propertyName == "clipping")
            {
                if (!propertyValue.IsNull())
                {
                    auto const& clippingDims = propertyValue.AsArray();
                    auto clippingData = PropHelper::toFloatArray(clippingDims);
                    m_clipping = createClipping(clippingData);
                } else
                {
                    m_clipping.reset();
                }
            }
        }
        invalidate();
    }

    std::optional<Rect> ARTGroup::createClipping(std::vector<float> data)
    {
        if (data.size() != 4)
        {
            //TODO: Throw something similar to JSApplicationIllegalArgumentException
            return std::nullopt;
        }
        return Rect(data[0], data[1], data[2], data[3]);
    }

    void ARTGroup::addChild(UIElement const& child, int64_t index)
    {
        m_children.InsertAt((uint32_t)index, child);
        if (auto const& ARTchild = child.try_as<ARTNode>())
        {
            ARTchild.ARTParent(*this);
        }
    }

    void ARTGroup::removeAllChildren()
    {
        for (auto const& child : m_children)
        {
            if (auto const& ARTchild = child.try_as<ARTNode>())
            {
                ARTchild.ARTParent(nullptr);
            }
        }
        m_children.Clear();
    }

    void ARTGroup::removeChildAt(int64_t index)
    {
        if (auto const& ARTchild = m_children.GetAt((uint32_t)index).try_as<ARTNode>())
        {
            ARTchild.ARTParent(nullptr);
        }
        m_children.RemoveAt((uint32_t)index);
    }

    void ARTGroup::replaceChild(UIElement const& oldChild, UIElement const& newChild)
    {
        uint32_t index;
        if (m_children.IndexOf(oldChild, index))
        {
            m_children.SetAt(index, newChild);
            if (auto const& ARTchild = newChild.try_as<ARTNode>())
            {
                ARTchild.ARTParent(*this);
            }
            if (auto const& ARTchild = oldChild.try_as<ARTNode>())
            {
                ARTchild.ARTParent(nullptr);
            }
        }
    }

}
