#pragma once

#include "pch.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "ARTShape.g.h"

namespace winrt::ART::implementation
{

    class ARTShape : public ARTShapeT<ARTShape>
    {
    public:
        ARTShape(Microsoft::ReactNative::IReactContext const& reactContext);
        void invalidate();

        void renderTo(Windows::Foundation::IInspectable const& session);

        static winrt::Windows::Foundation::Collections::
            IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
            NativeProps() noexcept;
        void UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept;

        Microsoft::ReactNative::IReactContext RNContext() { return m_reactContext; }
        void RNContext(Microsoft::ReactNative::IReactContext const& value) { m_reactContext = value; };

        ARTContainer ARTParent() { return m_parent; }
        void ARTParent(ARTContainer const& value) { m_parent = value; };


    private:
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
        ARTContainer m_parent{ nullptr };

        std::optional<Windows::Foundation::Numerics::float3x2> m_transform;
        float m_opacity = 1;

        std::optional<Microsoft::Graphics::Canvas::Geometry::CanvasGeometry> m_path;
        std::optional<std::string> m_strokeColor;
        std::optional<std::vector<float>> m_strokeDash;
        std::optional<std::vector<float>> m_brushData;
        float m_strokeWidth = 1;
        int m_strokeCap = CAP_ROUND;
        int m_strokeJoin = JOIN_ROUND;

        static const int CAP_BUTT = 0;
        static const int CAP_ROUND = 1;
        static const int CAP_SQUARE = 2;

        static const int JOIN_BEVEL = 2;
        static const int JOIN_MITER = 0;
        static const int JOIN_ROUND = 1;

        static const int PATH_TYPE_ARC = 4;
        static const int PATH_TYPE_CLOSE = 1;
        static const int PATH_TYPE_CURVETO = 3;
        static const int PATH_TYPE_LINETO = 2;
        static const int PATH_TYPE_MOVETO = 0;

        static const int COLOR_TYPE_SOLID_COLOR = 0;
        static const int COLOR_TYPE_LINEAR_GRADIENT = 1;
        static const int COLOR_TYPE_RADIAL_GRADIENT = 2;
        static const int COLOR_TYPE_PATTERN = 3;

        Microsoft::Graphics::Canvas::Geometry::CanvasGeometry createPath(std::vector<float> data);
        void renderLayerTo(Microsoft::Graphics::Canvas::ICanvasDrawingSession const& session);
        bool setupFillPaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush);
        bool setupStrokePaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush, Microsoft::Graphics::Canvas::Geometry::CanvasStrokeStyle& style);

    };

    
}



namespace winrt::ART::factory_implementation
{
    struct ARTShape : ARTShapeT<ARTShape, implementation::ARTShape> {};
}
