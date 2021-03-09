#include "pch.h"
#include "ARTSurfaceView.h"
#include "ARTSurfaceView.g.cpp"

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
    using namespace Microsoft::Graphics::Canvas;
    using namespace Microsoft::Graphics::Canvas::Text;
    using namespace Microsoft::Graphics::Canvas::UI::Xaml;
} // namespace winrt

namespace winrt::ART::implementation
{
    ARTSurfaceView::ARTSurfaceView(Microsoft::ReactNative::IReactContext const& reactContext)
    {
        m_reactContext = reactContext;

        mCanvasControl = Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl();
        this->Children().Append(mCanvasControl);
        mCanvasControl.Background(SolidColorBrush(Colors::Transparent()));

        mCanvasDrawRevoker = mCanvasControl.Draw(winrt::auto_revoke, { get_weak(), &ARTSurfaceView::OnCanvasDraw });
        mCanvaSizeChangedRevoker = mCanvasControl.SizeChanged(winrt::auto_revoke, { get_weak(), &ARTSurfaceView::OnCanvasSizeChanged });
    }

    void ARTSurfaceView::invalidate()
    {
        mCanvasControl.Invalidate();
    }

    void ARTSurfaceView::addChild(Windows::UI::Xaml::UIElement const& child, int64_t index)
    {
        m_children.InsertAt(index, child);
    }

    void ARTSurfaceView::removeAllChildren()
    {
        m_children.Clear();
    }

    void ARTSurfaceView::removeChildAt(int64_t index)
    {
        m_children.RemoveAt(index);
    }

    void ARTSurfaceView::replaceChild(Windows::UI::Xaml::UIElement const& oldChild, Windows::UI::Xaml::UIElement const& newChild)
    {
        uint32_t index;
        if (m_children.IndexOf(oldChild, index))
        {
            m_children.SetAt(index, newChild);
        }
    }

    void ARTSurfaceView::OnCanvasDraw(CanvasControl const& canvas, CanvasDrawEventArgs const& args)
    {
        auto session = args.DrawingSession();
        for (const auto& node : m_children)
        {
            if (auto const& art_node = node.try_as<ARTNode>())
            {
                art_node.renderTo(session);
            }
        }
    }

    void ARTSurfaceView::OnCanvasSizeChanged(const IInspectable canvas, Windows::UI::Xaml::SizeChangedEventArgs const& args)
    {
        Size newSize = args.NewSize();
        if (newSize.Width >= 0 && newSize.Height >= 0)
        {
            mCanvasControl.Invalidate();
        }
    }
}
