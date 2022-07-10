//
// Created by gogagum on 08.07.22.
//

#include "component_data.h"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::ComponentData::ComponentData(const PixelView& pixelView)
    : gdsu::BaseRootDSUData<PixelView>(pixelView),
      _additionalThreshold(0), _avgPixel(pixelView.getPixel({})) {}

//----------------------------------------------------------------------------//
void gseg::impl::ComponentData::joinWith(const ComponentData &other) {
    _avgPixel = weighted_avg(_size, _avgPixel, other._size, other._avgPixel);
}
