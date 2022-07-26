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
        //explicit ComponentData(const PixelView& pixelView);

        ComponentData(const PixelView& pixelView, std::size_t componentColour);

        void joinWith(const ComponentData& other);

        ComponentData(const ComponentData& other);

        [[nodiscard]] double getAdditionalThreshold() const;

        [[nodiscard]] std::size_t getFlagColour() const;

    private:
        double _additionalThreshold;
        const std::size_t _flagColour;
        Pixel<5> _avgPixel;
    };

} // gseg::impl

#endif //DSU_SEG_BACKEND_COMPONENT_DATA_H
