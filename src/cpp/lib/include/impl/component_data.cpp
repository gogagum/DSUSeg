//
// Created by gogagum on 08.07.22.
//

#include "component_data.h"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::ComponentData::ComponentData(PixelView &&pixelView)
    : gdsu::BaseRootDSUData<PixelView>(std::move(pixelView)),
      _additionalThreshold(0) {}