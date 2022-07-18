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
#include <boost/range/iterator_range.hpp>

#include "pixel.hpp"

namespace gseg::impl {

    namespace bmt = boost::math::tools;

    class DataView;

    ////////////////////////////////////////////////////////////////////////////
    // class PixelView
    class PixelView {
    public:

        /**
         * Pixel view constructor.
         * @param dataView - parent data view.
         * @param i - first dimension index.
         * @param j - second dimension index.
         */
        PixelView(const DataView* dataView, std::size_t i, std::size_t j);

        /**
         * Copy constructor.
         * @param other - pixel view to copy from.
         */
        PixelView(const PixelView& other) = default;

        /**
         * Move constructor.
         * @param other - pixel view to move from
         */
        PixelView(PixelView&& other) = default;

        /**
         * Get pixel channel by index.
         * @param i - channel index.
         * @return channel.
         */
        [[nodiscard]] double getChannel(std::size_t i) const;

        /**
         * Get number of channels.
         * @return number of channels.
         */
        [[nodiscard]] std::size_t getSize() const;

        /**
         * Get pixel from view.
         * @tparam maxSize - maximal pixel size.
         * @return pixel.
         */
        template<std::size_t maxSize = 5>
        Pixel<maxSize>
        getPixel(std::integral_constant<std::size_t, maxSize>) const;

        /**
         * Get pixel bytes pointer.
         * @return pixel pointer.
         */
        [[nodiscard]] const double* getPtr() const;

        PixelView& operator=(PixelView&& other) = default;

    private:
        const double *_ptr;
        std::size_t _num_dim;

    private:
        template<class NormTag>
        friend class PixelDistanceHelper;
    };

    using PixelViewRef = std::reference_wrapper<PixelView>;
    using PixelViewConstRef = std::reference_wrapper<const PixelView>;

    struct PixelViewImplCmp {
        bool operator ()(const PixelView& pv1, const PixelView& pv2) const;
    };


}

#endif //DSU_SEG_BACKEND_PIXEL_VIEW_H

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
template <class PixelT, std::size_t maxSize>
gseg::impl::Pixel<maxSize> avg(const PixelT& p1,
                               const gseg::impl::Pixel<maxSize>& p2) {
    if (p1.getSize() != p2.getSize()) {
        throw std::invalid_argument("Pixels are of different channel numbers.");
    }
    auto retDataArr = boost::container::static_vector<double, maxSize>();
    for (std::size_t i = 0; i < p1.getSize(); ++i) {
        retDataArr.push_back((p1.getChannel(i) + p2.getChannel(i)) / 2);
    }
    return gseg::impl::Pixel(retDataArr.data(), retDataArr.size());
}

//----------------------------------------------------------------------------//
template <class PixelT, std::size_t maxSize>
gseg::impl::Pixel<maxSize> avg(const gseg::impl::Pixel<maxSize>& p1,
                               const PixelT& p2) {
    return avg(p2, p1);
}

//----------------------------------------------------------------------------//
template<std::size_t maxSize>
gseg::impl::Pixel<maxSize> avg(const gseg::impl::Pixel<maxSize>& p1,
                               const gseg::impl::Pixel<maxSize>& p2) {
    if (p1.getSize() != p2.getSize()) {
        throw std::invalid_argument("Pixels are of different channel numbers.");
    }
    auto retDataArr = boost::container::static_vector<double, maxSize>();
    for (std::size_t i = 0; i < p1.getSize(); ++i) {
        retDataArr.push_back((p1.getChannel(i) + p2.getChannel(i)) / 2);
    }
    return gseg::impl::Pixel(retDataArr.data(), retDataArr.size());
}

//----------------------------------------------------------------------------//
template <class PixelT, std::size_t maxSize>
gseg::impl::Pixel<maxSize> weighted_avg(std::size_t s1,
                                        const PixelT& p1,
                                        std::size_t s2,
                                        const gseg::impl::Pixel<maxSize>& p2) {
    if (p1.getSize() != p2.getSize()) {
        throw std::invalid_argument("Pixels are of different channel numbers.");
    }
    auto retDataArr = boost::container::static_vector<double, maxSize>();
    for (std::size_t i = 0; i < p1.getSize(); ++i) {
        retDataArr.push_back(
                (p1.getChannel(i) * s1 + p2.getChannel(i) * s2) / (s1 + s2));
    }
    return gseg::impl::Pixel(retDataArr.data(), retDataArr.size());
}

//----------------------------------------------------------------------------//
template <class PixelT, std::size_t maxSize>
gseg::impl::Pixel<maxSize> weighted_avg(std::size_t s1,
                                        const gseg::impl::Pixel<maxSize>& p1,
                                        std::size_t s2,
                                        const PixelT& p2) {
    return avg(s2, p2, s1, p1);
}

//----------------------------------------------------------------------------//
template<std::size_t maxSize>
gseg::impl::Pixel<maxSize> weighted_avg(std::size_t s1,
                                        const gseg::impl::Pixel<maxSize>& p1,
                                        std::size_t s2,
                                        const gseg::impl::Pixel<maxSize>& p2) {
    if (p1.getSize() != p2.getSize()) {
        throw std::invalid_argument("Pixels are of different channel numbers.");
    }
    auto retDataArr = boost::container::static_vector<double, maxSize>();
    for (std::size_t i = 0; i < p1.getSize(); ++i) {
        retDataArr.push_back(
                (p1.getChannel(i) * s1 + p2.getChannel(i) * s2) / (s1 + s2));
    }
    return gseg::impl::Pixel<maxSize>(retDataArr.data(), retDataArr.size());
}
