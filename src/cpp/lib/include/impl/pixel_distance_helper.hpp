//
// Created by gogagum on 09.07.22.
//

#pragma once

#ifndef DSU_SEG_BACKEND_PIXEL_HELPER_H
#define DSU_SEG_BACKEND_PIXEL_HELPER_H

#include <numeric>
#include <boost/math/tools/norms.hpp>
#include <boost/range/iterator_range.hpp>

#include "pixel.hpp"
#include "pixel_view.h"

namespace gseg::impl {

    namespace norm {

        ////////////////////////////////////////////////////////////////////////
        /**
         * class L2Tag
         */
        class L2Tag {};

        ////////////////////////////////////////////////////////////////////////
        /**
         * class L1Tag
         */
        class L1Tag {};
    }

    ////////////////////////////////////////////////////////////////////////////
    /**
     * class PixelDistanceHelper
     * @tparam NormTag - type of norm.
     */
    template<class NormTag>
    class PixelDistanceHelper {
    public:

        /**
         * Compute distance between two pixels.
         * @tparam maxSize - maximum pixel channels count.
         * @param pixel1 - one pixel.
         * @param pixel2 - other pixel.
         * @return - distance between two pixels.
         */
        template<std::size_t maxSize>
        static double distance(const Pixel<maxSize>& pixel1,
                               const Pixel<maxSize>& pixel2);

        /**
         * Compute distance between two pixels.
         * @param pixelView1 - one pixel.
         * @param pixelView2 - other pixel.
         * @return - distance between two pixels.
         */
        static double distance(const PixelView& pixelView1,
                               const PixelView& pixelView2);
    private:

        /**
         * Cont distance by data pointers.
         * @param ptr1 - first pointer.
         * @param dimNum1 - number of dimensions.
         * @param ptr2 - second pointer.
         * @return - distance between to pixels.
         */
        static double _distanceImpl(const double* ptr1,
                                    std::size_t dimNum1,
                                    const double* ptr2);

        /**
         * Check equality of dimensions numbers.
         * @param dim1 - first number of dimensions.
         * @param dim2 - second number of dimensions.
         */
        static void _checkDimensions(std::size_t dim1, std::size_t dim2);
    };
} // gdsu::impl

#endif //DSU_SEG_BACKEND_PIXEL_HELPER_H

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
template<class NormTag>
template<std::size_t maxSize>
double
gseg::impl::PixelDistanceHelper<NormTag>::distance(
        const Pixel<maxSize> &pixel1, const Pixel<maxSize> &pixel2) {
    checkDimensions(pixel1.getSize(), pixel2.getSize());
    return distanceImpl(pixel1.getPtr(), pixel1.getSize(), pixel2.getPtr());
}

//----------------------------------------------------------------------------//
template<class NormTag>
double gseg::impl::PixelDistanceHelper<NormTag>::distance(const PixelView &pixelView1,
                                                  const PixelView &pixelView2) {
    _checkDimensions(pixelView1.getSize(), pixelView2.getSize());
    return _distanceImpl(pixelView1.getPtr(), pixelView1.getSize(), pixelView2.getPtr());
}

//----------------------------------------------------------------------------//
template<class NormTag>
double gseg::impl::PixelDistanceHelper<NormTag>::_distanceImpl(const double *ptr1,
                                                      std::size_t dimNum1,
                                                      const double *ptr2) {
    if constexpr(std::is_same_v<NormTag, norm::L2Tag>) {
        return boost::math::tools::l2_distance(ptr1, ptr1 + dimNum1, ptr2);
    } else if constexpr(std::is_same_v<NormTag, norm::L1Tag>) {
        return boost::math::tools::l1_distance(ptr1, ptr1 + dimNum1, ptr2);
    }
}

//----------------------------------------------------------------------------//
template<class NormTag>
void gseg::impl::PixelDistanceHelper<NormTag>::_checkDimensions(std::size_t dim1,
                                                       std::size_t dim2) {
    if (dim1 != dim2) {
        throw std::invalid_argument("Pixels have different dimensions numbers: "
                  + std::to_string(dim1) + " != " + std::to_string(dim2) + ".");
    }
}

