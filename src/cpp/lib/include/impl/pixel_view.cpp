//
// Created by gogagum on 07.07.22.
//

#include <stdexcept>

#include "pixel_view.h"
#include "data_view.h"


////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::PixelView::ChannelsRng::ChannelsRng(double *ptr,
                                                std::size_t numDim)
    : _begin(ptr), _end(ptr + numDim) {}

//----------------------------------------------------------------------------//
auto gseg::impl::PixelView::ChannelsRng::begin() -> Iterator {
    return _begin;
}

//----------------------------------------------------------------------------//
auto gseg::impl::PixelView::ChannelsRng::end() -> Iterator {
    return _end;
}

//----------------------------------------------------------------------------//
auto gseg::impl::PixelView::ChannelsRng::cbegin() const -> ConstIterator {
    return _begin;
}

//----------------------------------------------------------------------------//
auto gseg::impl::PixelView::ChannelsRng::cend() const -> ConstIterator {
    return _end;
}

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::PixelView::PixelView(const DataView *dataView,
                                 std::size_t i,
                                 std::size_t j)
    : _ptr(dataView->_data + dataView->_dimensions[0] * i + j),
      _num_dim(dataView->_dimensions[2]) {}

//----------------------------------------------------------------------------//
double gseg::impl::PixelView::getChannel(std::size_t i) const {
    if (i >= _num_dim) {
        throw std::invalid_argument(
                "Too great dimension index: "
                + std::to_string(i) + " >= " + std::to_string(_num_dim));
    }
    return _ptr[i];
}

//----------------------------------------------------------------------------//
std::size_t gseg::impl::PixelView::getSize() const {
    return _num_dim;
}

//----------------------------------------------------------------------------//
template<std::size_t maxSize>
gseg::impl::Pixel<maxSize> gseg::impl::PixelView::getPixel(
        std::integral_constant<std::size_t, maxSize>) const {
    return gseg::impl::Pixel<maxSize>(_ptr, _num_dim);
}

//----------------------------------------------------------------------------//
const double* gseg::impl::PixelView::getPtr() const {
    return _ptr;
}

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
bool
gseg::impl::PixelViewImplCmp::operator()(const gseg::impl::PixelView &pv1,
                                         const gseg::impl::PixelView &pv2) const {
    return pv1.getPtr() < pv2.getPtr();
}
