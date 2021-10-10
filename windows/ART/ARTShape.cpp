#include "pch.h"
#include "ARTShape.h"
#include "ARTShape.g.cpp"
#include "PropHelper.h"

constexpr float XM_PI = 3.141592654f;
constexpr float XM_2PI = 6.283185307f;

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
} // namespace winrt

namespace winrt::ART::implementation
{
    ARTShape::ARTShape(Microsoft::ReactNative::IReactContext const& reactContext)
    {
        m_reactContext = reactContext;
    }

    void ARTShape::invalidate()
    {
        if (m_parent != nullptr)
        {
            m_parent.invalidate();
        }
    }

    void ARTShape::renderTo(Windows::Foundation::IInspectable const& session)
    {
        if (auto const& drawingSession = session.try_as< Microsoft::Graphics::Canvas::ICanvasDrawingSession>())
        {
            if (m_opacity <= 0)
            {
                // Nothing to paint
                return;
            }
            if (m_opacity >= 1)
            {
                // Paint at full opacity
                renderLayerTo(drawingSession);
                return;
            }
            // Create a layer with specified opacity
            const auto& layer = drawingSession.CreateLayer(m_opacity);
            renderLayerTo(drawingSession);
        }
    }

    void ARTShape::renderLayerTo(Microsoft::Graphics::Canvas::ICanvasDrawingSession const& session)
    {
        auto current_transform = session.Transform();

        if (m_transform.has_value())
        {
            session.Transform(current_transform * m_transform.value());
        }

        if (!m_path.has_value())
        {
            session.Transform(current_transform);
            return;
            //TODO: see how to throw something similar to JSApplicationIllegalArgumentException
        }
        
        ICanvasBrush fill_brush;
        if (setupFillPaint(fill_brush))
        {
            session.FillGeometry(m_path.value(), fill_brush);
        }

        ICanvasBrush stroke_brush;
        CanvasStrokeStyle stroke_style;
        if (setupStrokePaint(stroke_brush, stroke_style))
        {
            session.DrawGeometry(m_path.value(), stroke_brush, m_strokeWidth, stroke_style);
        }

        session.Transform(current_transform);
    }

    bool ARTShape::setupFillPaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush)
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

    bool ARTShape::setupStrokePaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush, CanvasStrokeStyle& style)
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

    winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType> ARTShape::NativeProps() noexcept
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

        //ARTShape
        nativeProps.Insert(L"d", ViewManagerPropertyType::Array);

        return nativeProps.GetView();
    }

    void ARTShape::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept
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
            if (propertyName == "d")
            {
                if (!propertyValue.IsNull())
                {
                    auto const& shapePath = propertyValue.AsArray();
                    auto pathData = PropHelper::toFloatArray(shapePath);
                    m_path = createPath(pathData);
                } else
                {
                    m_path.reset();
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
        }
        invalidate();
    }

    Microsoft::Graphics::Canvas::Geometry::CanvasGeometry ARTShape::createPath(std::vector<float> data)
    {
        CanvasPathBuilder pathBuilder(CanvasDevice::GetSharedDevice());
        pathBuilder.BeginFigure(0, 0);
        bool figurestarted=true;
        int i = 0;
        while (i < data.size())
        {
            int type = (int)data[i++];
            switch (type)
            {
            case PATH_TYPE_MOVETO:
            {
                if (figurestarted) pathBuilder.EndFigure(CanvasFigureLoop::Open);
                float a = data[i++];
                float b = data[i++];
                pathBuilder.BeginFigure(a, b);
                figurestarted = true;
            }
                break;
            case PATH_TYPE_CLOSE:
            {
                pathBuilder.EndFigure(CanvasFigureLoop::Closed);
                figurestarted=false;
            }
                break;
            case PATH_TYPE_LINETO:
            {
                float a = data[i++];
                float b = data[i++];
                pathBuilder.AddLine(a, b);
            }
                break;
            case PATH_TYPE_CURVETO:
            {
                float x1 = data[i++];
                float y1 = data[i++];
                float x2 = data[i++];
                float y2 = data[i++];
                float x3 = data[i++];
                float y3 = data[i++];
                pathBuilder.AddCubicBezier(float2(x1, y1), float2(x2, y2), float2(x3, y3));
            }
                break;
            case PATH_TYPE_ARC:
            {
                float centerx = data[i++];
                float centery = data[i++];
                float radius = data[i++];
                float startAngle = data[i++];
                float endAngle = data[i++];
                float clockwise = data[i++];
                float sweepAngle = endAngle - startAngle;
                bool counterClockwise = !(clockwise == 1.0f);

                // If the arc is a full circle, we divide it into two half circles.
                bool isFullCircle = fabs(sweepAngle) >= XM_2PI - FLT_EPSILON;

                float2 centerPoint = float2(centerx, centery);
                float2 startPoint = centerPoint + Windows::Foundation::Numerics::transform(float2::unit_x(), Windows::Foundation::Numerics::make_float3x2_rotation(startAngle)) * radius;
                float2 endPoint = centerPoint + Windows::Foundation::Numerics::transform(float2::unit_x(), Windows::Foundation::Numerics::make_float3x2_rotation(endAngle)) * radius;

                if (isFullCircle)
                {
                    endPoint = centerPoint + Windows::Foundation::Numerics::transform(float2::unit_x(), Windows::Foundation::Numerics::make_float3x2_rotation(endAngle + XM_PI)) * radius;
                }
                pathBuilder.AddLine(startPoint);
                /*if (figurestarted) pathBuilder.EndFigure(CanvasFigureLoop::Open);
                pathBuilder.BeginFigure(startPoint);*/

                pathBuilder.AddArc(
                    endPoint,
                    radius,
                    radius,
                    0,
                    counterClockwise ? CanvasSweepDirection::CounterClockwise : CanvasSweepDirection::Clockwise,
                    (fabs(sweepAngle) > XM_PI) ? CanvasArcSize::Large : CanvasArcSize::Small
                    );

                if (isFullCircle)
                {
                    pathBuilder.AddArc(
                        startPoint,
                        radius,
                        radius,
                        0,
                        counterClockwise ? CanvasSweepDirection::CounterClockwise : CanvasSweepDirection::Clockwise,
                        (fabs(sweepAngle) > XM_PI) ? CanvasArcSize::Large : CanvasArcSize::Small
                    );

                }

            }
                break;
            default:
                //TODO: Throw something equivalent to JSApplicatoinIllegalArgumentException
                break;
            }
        }
        if (figurestarted) pathBuilder.EndFigure(CanvasFigureLoop::Open);
        return CanvasGeometry::CreatePath(pathBuilder);        
    }

}
