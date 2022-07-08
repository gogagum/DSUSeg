//
// Created by gogagum on 07.07.22.
//

#include "data_view.h"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::DataView::DataView(double *data,
                               std::array<std::size_t, 3>&& dimensions)
    : _data(data), _dimensions(dimensions) {}

//----------------------------------------------------------------------------//
gseg::impl::DataView::DataView(DataView &&other) noexcept
    : _data(other._data), _dimensions(other._dimensions) {}

//----------------------------------------------------------------------------//
auto
gseg::impl::DataView::get(std::size_t hor, std::size_t vert) const -> PixelView {
    return {this, hor, vert};
}
