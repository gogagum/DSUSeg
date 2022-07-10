//
// Created by gogagum on 09.07.22.
//

#include <stdexcept>

#include "edge.h"
#include "pixel_distance_helper.hpp"
#include "pixel_view.h"


////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::Edge::Edge(const PixelView &pixelView1,
                       const PixelView &pixelView2) {
    if (pixelView1.getSize() != pixelView2.getSize()) {
        throw std::invalid_argument(
                "Pixels are not of the same dimension sizes.");
    }
    _length = PixelHelper<norm::L2Tag>::distance(pixelView1, pixelView2);
}

//----------------------------------------------------------------------------//
double gseg::impl::Edge::getLength() const {
    return _length;
}
