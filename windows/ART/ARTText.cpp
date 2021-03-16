#include "pch.h"
#include "ARTText.h"
#include "ARTText.g.cpp"
#include "PropHelper.h"

#define PI_VALUE (3.14159265358979323846f)

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Data::Json;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Numerics;
    using namespace Windows::UI;
    using namespace Windows::UI::Popups;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml::Media;
    using namespace Microsoft::Graphics::Canvas;
    using namespace Microsoft::Graphics::Canvas::Geometry;
    using namespace Microsoft::Graphics::Canvas::Brushes;
    using namespace Microsoft::Graphics::Canvas::Text;
} // namespace winrt

namespace winrt::ART::implementation
{
    ARTText::ARTText(Microsoft::ReactNative::IReactContext const& reactContext)
    {
        m_reactContext = reactContext;
    }
    void ARTText::invalidate()
    {
        if (m_parent != nullptr)
        {
            m_parent.invalidate();
        }
    }

    void ARTText::renderTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session)
    {

        if (m_opacity <= 0)
        {
            // Nothing to paint
            return;
        }
        if (m_opacity >= 1)
        {
            // Paint at full opacity
            renderLayerTo(session);
            return;
        }
        // Create a layer with specified opacity
        const auto& layer = session.CreateLayer(m_opacity);
        renderLayerTo(session);
    }

    void ARTText::renderLayerTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session)
    {
        auto current_transform = session.Transform();

        if (m_transform.has_value())
        {
            session.Transform(current_transform * m_transform.value());
        }

        if (m_frame.has_value() && m_frame.value().lines.size() > 0)
        {
            CanvasTextFormat text_format;
            applyTextPropertiesToPaint(text_format);

            std::string text = "";
            for (const auto& line : m_frame.value().lines)
            {
                if (text.size() > 0)
                {
                    text.append("\n");
                }
                text.append(line);
            }

            ICanvasBrush fill_brush;
            if (setupFillPaint(fill_brush))
            {
                session.DrawText(winrt::to_hstring(text), float2(0, 0), fill_brush, text_format);
            }

            ICanvasBrush stroke_brush;
            CanvasStrokeStyle stroke_style;
            if (setupStrokePaint(stroke_brush, stroke_style))
            {
                session.DrawText(winrt::to_hstring(text), float2(0, 0), stroke_brush, text_format);
            }
        }
        session.Transform(current_transform);
    }

    bool ARTText::setupFillPaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush)
    {
        if (m_brushData.has_value() && m_brushData.value().size() > 0)
        {
            auto const& brushData = m_brushData.value();
            int colorType = (int)brushData[0];
            switch (colorType)
            {
            case COLOR_TYPE_SOLID_COLOR:
            {
                Color color = Color();
                color.A = (uint8_t)(brushData.size() > 4 ? brushData[4] * 255 : 255.0f);
                color.R = (uint8_t)(brushData[1] * 255);
                color.G = (uint8_t)(brushData[2] * 255);
                color.B = (uint8_t)(brushData[3] * 255);
                brush = CanvasSolidColorBrush(CanvasDevice::GetSharedDevice(), color);
            }
            break;
            case COLOR_TYPE_LINEAR_GRADIENT:
            {
                if (brushData.size() < 5)
                {
                    // TODO: Log some warning.
                    return false;
                }
                float gradientStartX = brushData[1];
                float gradientStartY = brushData[2];
                float gradientEndX = brushData[3];
                float gradientEndY = brushData[4];
                int stops = (brushData.size() - 5) / 5;
                std::vector<CanvasGradientStop> positions(stops);
                if (stops > 0)
                {
                    for (int i = 0; i < stops; i++)
                    {
                        positions[i].Position = brushData[5 + 4 * stops + i];
                        positions[i].Color.R = (uint8_t)(brushData[5 + 4 * i + 0] * 255);
                        positions[i].Color.G = (uint8_t)(brushData[5 + 4 * i + 1] * 255);
                        positions[i].Color.B = (uint8_t)(brushData[5 + 4 * i + 2] * 255);
                        positions[i].Color.A = (uint8_t)(brushData[5 + 4 * i + 3] * 255);
                    }
                }
                auto gradientbrush = CanvasLinearGradientBrush(
                    CanvasDevice::GetSharedDevice(),
                    winrt::array_view<const CanvasGradientStop>(positions),
                    Microsoft::Graphics::Canvas::CanvasEdgeBehavior::Clamp,
                    CanvasAlphaMode::Straight
                );
                gradientbrush.StartPoint(float2(gradientStartX, gradientStartY));
                gradientbrush.EndPoint(float2(gradientEndX, gradientEndY));
                brush = gradientbrush;
            }
            break;
            case COLOR_TYPE_RADIAL_GRADIENT:
            {
                if (brushData.size() < 7)
                {
                    // TODO: Log some warning.
                    return false;
                }
                float radius = brushData[3];
                float radiusRatio = brushData[4] / radius;
                float focusPointX = brushData[1];
                float focusPointY = brushData[2] / radiusRatio;
                float centerPointX = brushData[5];
                float centerPointY = brushData[6] / radiusRatio;
                int stops = (brushData.size() - 7) / 5;
                std::vector<CanvasGradientStop> positions(stops);
                if (stops > 0)
                {
                    for (int i = 0; i < stops; i++)
                    {
                        positions[i].Position = brushData[7 + 4 * stops + i];
                        positions[i].Color.R = (uint8_t)(brushData[7 + 4 * i + 0] * 255);
                        positions[i].Color.G = (uint8_t)(brushData[7 + 4 * i + 1] * 255);
                        positions[i].Color.B = (uint8_t)(brushData[7 + 4 * i + 2] * 255);
                        positions[i].Color.A = (uint8_t)(brushData[7 + 4 * i + 3] * 255);
                    }
                }
                auto gradientbrush = CanvasRadialGradientBrush(
                    CanvasDevice::GetSharedDevice(),
                    winrt::array_view<const CanvasGradientStop>(positions),
                    Microsoft::Graphics::Canvas::CanvasEdgeBehavior::Clamp,
                    CanvasAlphaMode::Straight
                );
                gradientbrush.Center(float2(centerPointX, centerPointY));
                gradientbrush.OriginOffset(float2(focusPointX - centerPointX, focusPointY - centerPointY));
                gradientbrush.RadiusX(radius);
                gradientbrush.RadiusY(radius);
                brush = gradientbrush;
            }
            break;
            case COLOR_TYPE_PATTERN:
                // TODO: Support patterns etc.
                return false;
            default:
                break;
            }
            return true;
        } else
        {
            return false;
        }
    }

    bool ARTText::setupStrokePaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush, CanvasStrokeStyle& style)
    {
        if (m_strokeWidth == 0 || !m_strokeColor.has_value())
        {
            return false;
        }
        auto const& color = PropHelper::ParseColor(m_strokeColor.value());
        if (color.has_value())
        {
            brush = CanvasSolidColorBrush(CanvasDevice::GetSharedDevice(), color.value());
            style = CanvasStrokeStyle();

            CanvasCapStyle capStyle;
            switch (m_strokeCap)
            {
            case CAP_BUTT:
                capStyle = CanvasCapStyle::Flat;
                break;
            case CAP_SQUARE:
                capStyle = CanvasCapStyle::Square;
                break;
            case CAP_ROUND:
            default:
                // TODO: Throw some error here.
                capStyle = CanvasCapStyle::Round;
            }
            style.StartCap(capStyle);
            style.EndCap(capStyle);
            style.DashCap(capStyle);

            switch (m_strokeJoin)
            {
            case JOIN_MITER:
                style.LineJoin(CanvasLineJoin::Miter);
                break;
            case JOIN_BEVEL:
                style.LineJoin(CanvasLineJoin::Bevel);
                break;
            case JOIN_ROUND:
            default:
                // TODO: Throw some error here.
                style.LineJoin(CanvasLineJoin::Round);
            }

            if (m_strokeDash.has_value() && m_strokeDash.value().size() > 0)
            {
                style.CustomDashStyle(winrt::array_view<const float>(m_strokeDash.value()));
            }

            return true;
        } else
        {
            return false;
        }
    }

    bool ARTText::applyTextPropertiesToPaint(Microsoft::Graphics::Canvas::Text::ICanvasTextFormat& textFormat)
    {
        if (m_frame.has_value())
        {
            auto const& frame = m_frame.value();
            if (frame.fontFamily.size() > 0)
            {
                textFormat.FontFamily(winrt::to_hstring(frame.fontFamily));
            }
            textFormat.FontSize(frame.fontSize);
            textFormat.FontStyle(frame.fontStyle);
            textFormat.FontWeight(frame.fontWeight);
        } else
        {
            textFormat.FontSize(DEFAULT_FONT_SIZE);
        }
        
        switch (m_alignment)
        {
        case TEXT_ALIGNMENT_CENTER:
            textFormat.HorizontalAlignment(CanvasHorizontalAlignment::Center);
            break;
        case TEXT_ALIGNMENT_RIGHT:
            textFormat.HorizontalAlignment(CanvasHorizontalAlignment::Right);
            break;
        case TEXT_ALIGNMENT_LEFT:
        default:
            // TODO: Throw some error here.
            textFormat.HorizontalAlignment(CanvasHorizontalAlignment::Left);
        }

        return true;
    }

    winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType> ARTText::NativeProps() noexcept
    {
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
        //ARTNode
        nativeProps.Insert(L"opacity", ViewManagerPropertyType::Number);
        nativeProps.Insert(L"transform_windows", ViewManagerPropertyType::Array);
        nativeProps.Insert(L"shadow", ViewManagerPropertyType::Array);

        //ARTRenderable
        nativeProps.Insert(L"stroke", ViewManagerPropertyType::String);
        nativeProps.Insert(L"strokeDash", ViewManagerPropertyType::Array);
        nativeProps.Insert(L"fill", ViewManagerPropertyType::Array);
        nativeProps.Insert(L"strokeWidth", ViewManagerPropertyType::Number);
        nativeProps.Insert(L"strokeCap", ViewManagerPropertyType::Number);
        nativeProps.Insert(L"strokeJoin", ViewManagerPropertyType::Number);
                
        //ARTText
        nativeProps.Insert(L"frame", ViewManagerPropertyType::Map);
        nativeProps.Insert(L"alignment", ViewManagerPropertyType::Number);

        return nativeProps.GetView();
    }

    void ARTText::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept
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
                if (!propertyValue.IsNull())
                {
                    auto const& matrixArray = propertyValue.AsArray();
                    m_transform = PropHelper::to3x2Matrix(matrixArray);
                } else
                {
                    m_transform.reset();
                }
            }
            if (propertyName == "stroke")
            {
                if (!propertyValue.IsNull())
                {
                    m_strokeColor = propertyValue.AsString();
                } else
                {
                    m_strokeColor.reset();
                }
            }
            if (propertyName == "strokeDash")
            {
                if (!propertyValue.IsNull())
                {
                    auto const& strokeDash = propertyValue.AsArray();
                    m_strokeDash = PropHelper::toFloatArray(strokeDash);
                } else
                {
                    m_strokeDash.reset();
                }
            }
            if (propertyName == "fill")
            {
                if (!propertyValue.IsNull())
                {
                    auto const& fillColors = propertyValue.AsArray();
                    m_brushData = PropHelper::toFloatArray(fillColors);
                } else
                {
                    m_brushData.reset();
                }
            }
            if (propertyName == "strokeWidth")
            {
                if (!propertyValue.IsNull())
                {
                    m_strokeWidth = propertyValue.AsSingle();
                } else
                {
                    m_strokeWidth = 1;
                }
            }
            if (propertyName == "strokeCap")
            {
                if (!propertyValue.IsNull())
                {
                    m_strokeCap = propertyValue.AsInt32();
                } else
                {
                    m_strokeCap = CAP_ROUND;
                }
            }
            if (propertyName == "strokeJoin")
            {
                if (!propertyValue.IsNull())
                {
                    m_strokeJoin = propertyValue.AsInt32();
                } else
                {
                    m_strokeJoin = JOIN_ROUND;
                }
            }
            if (propertyName == "frame")
            {
                if (!propertyValue.IsNull())
                {
                    const auto& frameObj = propertyValue.AsObject();
                    ARTTextFrame textFrame;
                    
                    if (frameObj.find("lines") != frameObj.end())
                    {
                        const auto& lines = frameObj["lines"].AsArray();
                        textFrame.lines.reserve(lines.size());
                        for (const auto& line : lines)
                        {
                            textFrame.lines.push_back(line.AsString());
                        }
                    }
                    if (frameObj.find("font") != frameObj.end())
                    {
                        const auto& font = frameObj["font"].AsObject();
                        textFrame.fontSize = DEFAULT_FONT_SIZE;
                        if (font.find("fontSize") != font.end())
                        {
                            textFrame.fontSize = font["fontSize"].AsSingle();
                        }
                        textFrame.fontStyle =
                            font.find("fontStyle") != font.end() && font["fontStyle"].AsString() == "italic" ?
                            Windows::UI::Text::FontStyle::Italic :
                            Windows::UI::Text::FontStyle::Normal;
                        textFrame.fontWeight =
                            font.find("fontWeight") != font.end() && font["fontStyle"].AsString() == "bold" ?
                            Windows::UI::Text::FontWeights::Bold() :
                            Windows::UI::Text::FontWeights::Normal();
                        if (font.find("fontFamily") != font.end())
                        {
                            textFrame.fontFamily = font["fontFamily"].AsString();
                        }
                    }
                    m_frame = textFrame;
                    
                } else
                {
                    m_frame.reset();
                }
            }
            if (propertyName == "alignment")
            {
                if (!propertyValue.IsNull())
                {
                    m_alignment = propertyValue.AsInt32();
                } else
                {
                    m_alignment = TEXT_ALIGNMENT_LEFT;
                }
            }
        }
        invalidate();
    }

}
