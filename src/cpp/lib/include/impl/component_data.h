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
    class ComponentData : public gdsu::BaseRootDSUData<PixelView> {
    public:
        explicit ComponentData(const PixelView& pixelView);

        void joinWith(const ComponentData& other);

        ComponentData(const ComponentData& other);
    private:
        double _additionalThreshold;
        Pixel<5> _avgPixel;
    };

} // gseg::impl

#endif //DSU_SEG_BACKEND_COMPONENT_DATA_H
