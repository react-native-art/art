#include "pch.h"
#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#  include "ReactPackageProvider.g.cpp"
#endif

#include "ARTShapeViewManager.h"
#include "ARTGroupViewManager.h"
#include "ARTSurfaceViewManager.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::ART::implementation {
  void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept {
    packageBuilder.AddViewManager(L"ARTShapeViewManager", []() { return winrt::make<ARTShapeViewManager>(); });
    packageBuilder.AddViewManager(L"ARTGroupViewManager", []() { return winrt::make<ARTGroupViewManager>(); });
    packageBuilder.AddViewManager(L"ARTSurfaceViewManager", []() { return winrt::make<ARTSurfaceViewManager>(); });
  }
}
