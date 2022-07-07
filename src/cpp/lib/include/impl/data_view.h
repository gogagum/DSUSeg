//
// Created by gogagum on 07.07.22.
//

#ifndef DSU_SEG_BACKEND_DATA_VIEW_H
#define DSU_SEG_BACKEND_DATA_VIEW_H

#include <array>
#include <numeric>

#include "pixel.h"

namespace gdsu::impl {

    class DataView {
    public:
        DataView(double* data, std::array<std::size_t, 3>&& dimensions);

        Pixel get(std::size_t vert, std::size_t hot) const;

    private:
        double* _data;
        std::array<std::size_t, 3> _dimensions;
    };

}

#endif //DSU_SEG_BACKEND_DATA_VIEW_H
