//
// Created by gogagum on 08.07.22.
//

#ifndef DSU_SEG_BACKEND_COMPONENT_DATA_H
#define DSU_SEG_BACKEND_COMPONENT_DATA_H

#include <DefaultDSUData.hpp>
#include "pixel_view.h"

namespace gseg::impl {

    ////////////////////////////////////////////////////////////////////////////
    // class ComponentData
    class ComponentData : gdsu::BaseRootDSUData<PixelView> {
    public:
        explicit ComponentData(PixelView&& pixelView);
    private:
        double _additionalThreshold;
    };

} // gseg::impl

#endif //DSU_SEG_BACKEND_COMPONENT_DATA_H
