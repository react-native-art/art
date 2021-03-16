#pragma once
#pragma once

#include "pch.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "ARTText.g.h"

namespace winrt::ART::implementation
{

    // FIX: IDL classes have interface inheritance but no implementation inheritance.
    // Figure out how to abstract the dependency on ARTShape implementation, to fix the copy paste.
    class ARTText : public ARTTextT<ARTText>
    {
    public:
        ARTText(Microsoft::ReactNative::IReactContext const& reactContext);

        void renderTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session);

        static winrt::Windows::Foundation::Collections::
            IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
            NativeProps() noexcept;
        void UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept;

        Microsoft::ReactNative::IReactContext RNContext() { return m_reactContext; }
        void RNContext(Microsoft::ReactNative::IReactContext const& value) { m_reactContext = value; };

        ARTContainer ARTParent() { return m_parent; }
        void ARTParent(ARTContainer const& value) { m_parent = value; };


    private:
        struct ARTTextFrame
        {
            std::vector<std::string> lines;
            float fontSize = DEFAULT_FONT_SIZE;
            Windows::UI::Text::FontStyle fontStyle;
            Windows::UI::Text::FontWeight fontWeight;
            std::string fontFamily;
        };
        std::optional<ARTTextFrame> m_frame;
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

        int m_alignment = TEXT_ALIGNMENT_LEFT;

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

        static const int DEFAULT_FONT_SIZE = 12;

        static const int TEXT_ALIGNMENT_CENTER = 2;
        static const int TEXT_ALIGNMENT_LEFT = 0;
        static const int TEXT_ALIGNMENT_RIGHT = 1;

        void renderLayerTo(Microsoft::Graphics::Canvas::CanvasDrawingSession const& session);
        bool setupFillPaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush);
        bool setupStrokePaint(Microsoft::Graphics::Canvas::Brushes::ICanvasBrush& brush, Microsoft::Graphics::Canvas::Geometry::CanvasStrokeStyle& style);
        bool applyTextPropertiesToPaint(Microsoft::Graphics::Canvas::Text::ICanvasTextFormat& textFormat);

    };


}

namespace winrt::ART::factory_implementation
{
    struct ARTText : ARTTextT<ARTText, implementation::ARTText> {};
}
