//
// Created by gogagum on 08.07.22.
//

#include "segmenter.h"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::Segmenter::Segmenter(DataView &&dataView)
    : _dataView(std::move(dataView)) {}