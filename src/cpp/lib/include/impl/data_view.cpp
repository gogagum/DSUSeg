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

//----------------------------------------------------------------------------//
std::size_t gseg::impl::DataView::getRowsNum() const {
    return _dimensions[0];
}

//----------------------------------------------------------------------------//
std::size_t gseg::impl::DataView::getColumnsNum() const {
    return _dimensions[1];
}

//----------------------------------------------------------------------------//
auto gseg::impl::DataView::getPixelsBegin() const -> DataView::ComponentDataIterator {
    return {this, 0, 0};
}

//----------------------------------------------------------------------------//
auto gseg::impl::DataView::getPixelsEnd() const -> DataView::ComponentDataIterator {
    return {this, getRowsNum() + 1, getColumnsNum()};
}

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::DataView::ComponentDataIterator::ComponentDataIterator(
        const gseg::impl::DataView *owner, std::size_t i, std::size_t j)
    : _owner(owner), _i(i), _j(j) {}

//----------------------------------------------------------------------------//
auto
gseg::impl::DataView::ComponentDataIterator::operator++() -> DataView::ComponentDataIterator {
    if (_j == _owner->getColumnsNum()) {
        return {_owner, _i + 1, 0};
    } else {
        return {_owner, _i, _j + 1};
    }
}

//----------------------------------------------------------------------------//
bool
gseg::impl::DataView::ComponentDataIterator::operator==(
        const ComponentDataIterator& other) const {
    return _owner == other._owner && _i == other._i && _j == other._j;
}

//----------------------------------------------------------------------------//
bool
gseg::impl::DataView::ComponentDataIterator::operator!=(
        const ComponentDataIterator& other) const {
    return !operator==(other);
}

//----------------------------------------------------------------------------//
gseg::impl::ComponentData
gseg::impl::DataView::ComponentDataIterator::operator*() const {
    return {{_owner, _i, _j}, _i * _owner->getColumnsNum() + _j};
}
