//
// Created by gogagum on 07.07.22.
//

#ifndef DSU_SEG_BACKEND_DATA_VIEW_H
#define DSU_SEG_BACKEND_DATA_VIEW_H

#include <array>
#include <numeric>

#include "pixel_view.h"

namespace gdsu::impl {

    ////////////////////////////////////////////////////////////////////////////
    // class DataView
    class DataView {
    public:
        /**
         * Data view constructor.
         * @param data - pointer to data.
         * @param dimensions - three dimensions: with, height an channels.
         */
        DataView(double* data, std::array<std::size_t, 3>&& dimensions);

        /**
         * Get pixel view by a pair of indexes.
         * @param hor - horizontal index.
         * @param vert - vertical index.
         * @return pixel view.
         */
        [[nodiscard]] PixelView get(std::size_t hor, std::size_t vert) const;

    private:
        double* _data;
        std::array<std::size_t, 3> _dimensions;
    private:
        friend class PixelView;
    };

}

#endif //DSU_SEG_BACKEND_DATA_VIEW_H
