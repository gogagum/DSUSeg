//
// Created by gogagum on 07.07.22.
//

#pragma once
#ifndef DSU_SEG_BACKEND_PIXEL_VIEW_H
#define DSU_SEG_BACKEND_PIXEL_VIEW_H

#include <numeric>
#include <functional>
#include <string>
#include <stdexcept>
#include <boost/math/tools/norms.hpp>


namespace gdsu::impl {

    namespace bmt = boost::math::tools;

    class DataView;

    ////////////////////////////////////////////////////////////////////////////
    // class PixelView
    class PixelView {
    public:
        template<class IteratorT>
        using NormT = std::function<double(IteratorT, IteratorT, IteratorT)>;

        ////////////////////////////////////////////////////////////////////////
        //--------------------------------------------------------------------//
        template<class IteratorT>
        static double distance(const PixelView& pv1,
                               const PixelView& pv2,
                               NormT<IteratorT> norm = bmt::l2_norm);
    public:

        /**
         * Pixel view constructor.
         * @param dataView - parent data view.
         * @param i - first dimension index.
         * @param j - second dimension index.
         */
        PixelView(const DataView* dataView, std::size_t i, std::size_t j);

        /**
         * Get pixel channel by index.
         * @param i - channel index.
         * @return channel.
         */
        [[nodiscard]] double getChannel(std::size_t i) const;
    private:
        const double *_ptr;
        std::size_t _num_dim;
    };
}

#endif //DSU_SEG_BACKEND_PIXEL_VIEW_H

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
template<class IteratorT>
double gdsu::impl::PixelView::distance(const PixelView& pv1,
                                       const PixelView& pv2,
                                       PixelView::NormT<IteratorT> norm) {
    if (pv1._num_dim != pv2._num_dim) {
        throw std::invalid_argument(
                "Got to pixels of different dimensions numbers: "
                + std::to_string(pv1._num_dim) + " and "
                + std::to_string(pv2._num_dim));
    }
    return norm(pv1._ptr, pv1._ptr + pv1._num_dim, pv2._ptr);
}
