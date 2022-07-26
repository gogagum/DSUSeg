//
// Created by gogagum on 08.07.22.
//

#include <cassert>

#include "component_data.h"
#include "pixel_distance_helper.hpp"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::ComponentData::ComponentData(const PixelView& pixelView,
                                         std::size_t componentColour)
    : gdsu::BaseRootDSUData<PixelView>(pixelView),
      _additionalThreshold(0),
      _avgPixel(pixelView.getPixel({})),
      _flagColour(componentColour) {}

//----------------------------------------------------------------------------//
gseg::impl::ComponentData::ComponentData(
        const gseg::impl::ComponentData &other)
    : _additionalThreshold(other._additionalThreshold),
      _avgPixel(other._avgPixel),
      gdsu::BaseRootDSUData<PixelView>(other.getKey()),
      _flagColour(other._flagColour) {}

//----------------------------------------------------------------------------//
void gseg::impl::ComponentData::joinWith(const ComponentData &other) {
    _avgPixel = weighted_avg(_size, _avgPixel, other._size, other._avgPixel);
    _additionalThreshold +=
            PixelDistanceHelper<norm::L2Tag>::distance(getKey(), other.getKey());
}

//----------------------------------------------------------------------------//
double gseg::impl::ComponentData::getAdditionalThreshold() const {
    return _additionalThreshold;
}

//----------------------------------------------------------------------------//
std::size_t gseg::impl::ComponentData::getFlagColour() const {
    return _flagColour;
}
