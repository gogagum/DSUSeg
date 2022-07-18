//
// Created by gogagum on 09.07.22.
//

#include <stdexcept>

#include "edge.h"
#include "pixel_distance_helper.hpp"
#include "pixel_view.h"


////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::Edge::Edge(const PixelView &pixelView1, const PixelView &pixelView2)
    : _pixelsDistance(PixelDistanceHelper<norm::L2Tag>::distance(pixelView1, pixelView2)),
      _pv1(pixelView1),
      _pv2(pixelView2) {
    if (pixelView1.getSize() != pixelView2.getSize()) {
        throw std::invalid_argument(
                "Pixels are not of the same dimension sizes.");
    }
}

//----------------------------------------------------------------------------//
double gseg::impl::Edge::getLength() const {
    return _pixelsDistance;
}

//----------------------------------------------------------------------------//
auto
gseg::impl::Edge::getPixelViews(
        ) const -> std::pair<PixelViewConstRef, PixelViewConstRef> {
    return {_pv1, _pv2};
}
