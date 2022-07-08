//
// Created by gogagum on 09.07.22.
//

#ifndef DSU_SEG_BACKEND_PIXEL_H
#define DSU_SEG_BACKEND_PIXEL_H

#include <numeric>
#include <boost/container/static_vector.hpp>

namespace gseg::impl {
    template <std::size_t maxSize>
    class Pixel {
        /**
         * Pixel class constructor.
         * @param ptr - pointer to pixel data.
         * @param numChannels - number of channels.
         */
        Pixel(double* ptr, std::size_t numChannels);

        /**
         * Get one channel.
         * @param i - channel index.
         * @return - one color channel.
         */
        double getChannel(std::size_t i) const;

        /**
         * Get number of channels.
         * @return number of channels.
         */
        std::size_t getSize() const;
    private:
        boost::container::static_vector<double, maxSize> _channels;
    };
} // gseg::impl

#endif //DSU_SEG_BACKEND_PIXEL_H

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
template<std::size_t maxSize>
gseg::impl::Pixel<maxSize>::Pixel(double *ptr, std::size_t numChannels)
        : _channels(ptr, ptr + numChannels) {}

//----------------------------------------------------------------------------//
template<std::size_t maxSize>
double gseg::impl::Pixel<maxSize>::getChannel(std::size_t i) const {
    return _channels[i];
}

//----------------------------------------------------------------------------//
template<std::size_t maxSize>
std::size_t gseg::impl::Pixel<maxSize>::getSize() const {
    return _channels.size();
}


