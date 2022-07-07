//
// Created by gogagum on 07.07.22.
//

#ifndef DSU_SEG_BACKEND_PIXEL_H
#define DSU_SEG_BACKEND_PIXEL_H

#include <numeric>

namespace gdsu::impl {

    class DataView;

    class Pixel {
    public:
        Pixel(const DataView* dataView, std::size_t i, std::size_t j);
    private:
        double *_ptr{};
        std::size_t _i{};
        std::size_t _j{};
        std::size_t _num_dim{};
    };
}


#endif //DSU_SEG_BACKEND_PIXEL_H
