//
// Created by gogagum on 08.07.22.
//

#include "segmenter.h"

////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------//
gseg::impl::Segmenter::Segmenter(DataView &&dataView)
    : _dataView(std::move(dataView)),
      _dsu(dataView.getPixelsBegin(), dataView.getPixelsEnd()) {
    _initDSU();
    _generateEdges();
    _sortEdges();
    _process();
}

//----------------------------------------------------------------------------//
void gseg::impl::Segmenter::_generateEdges() {
    _edges.clear();
    const std::size_t rows_num = _dataView.getRowsNum();
    const std::size_t cols_num = _dataView.getColumnsNum();
    for (std::size_t row_i = 0; row_i < rows_num - 1; ++row_i) {
        for (std::size_t col_i = 0; col_i < cols_num; ++col_i) {
            _edges.emplace_back(_dataView.get(row_i, col_i),
                                _dataView.get(row_i + 1, col_i));
        }
    }
    for (std::size_t row_i = 0; row_i < rows_num; ++row_i) {
        for (std::size_t col_i = 0; col_i < cols_num - 1; ++col_i) {
            _edges.emplace_back(_dataView.get(row_i, col_i),
                                _dataView.get(row_i, col_i + 1));
        }
    }
    for (std::size_t row_i = 0; row_i < rows_num - 1; ++row_i) {
        for (std::size_t col_i = 0; col_i < cols_num - 1; ++col_i) {
            _edges.emplace_back(_dataView.get(row_i, col_i),
                                _dataView.get(row_i + 1, col_i + 1));
        }
    }
    for (std::size_t row_i = 0; row_i < rows_num - 1; ++row_i) {
        for (std::size_t col_i = 1; col_i < cols_num; ++col_i) {
            _edges.emplace_back(_dataView.get(row_i, col_i),
                                _dataView.get(row_i + 1, col_i - 1));
        }
    }
}

//----------------------------------------------------------------------------//
void gseg::impl::Segmenter::_sortEdges() {
    std::sort(_edges.rbegin(), _edges.rend(),
              [](const Edge& e1, const Edge& e2) {
                  return e1.getLength() < e2.getLength();
              });
}

//----------------------------------------------------------------------------//
void gseg::impl::Segmenter::_initDSU() {
    std::vector<ComponentData> components;
    for (std::size_t row_i = 0; row_i < _dataView.getRowsNum(); ++row_i) {
        for (std::size_t col_i = 1; col_i < _dataView.getColumnsNum(); ++col_i) {
            components.emplace_back(PixelView(&_dataView, row_i, col_i), _dataView.getColumnsNum() * row_i + col_i);
        }
    }
}

//----------------------------------------------------------------------------//
void gseg::impl::Segmenter::_process() {
    for (const auto& edge : _edges) {
        const auto& [pv1, pv2] = edge.getPixelViews();
        const auto& comp1 = _dsu.getRootData(pv1);
        const auto& comp2 = _dsu.getRootData(pv2);
        if (!_dsu.inSameComponent(pv1, pv2)
            && edge.getLength() < comp1.getAdditionalThreshold()
            && edge.getLength() < comp2.getAdditionalThreshold()) {
            _dsu.join(pv1, pv2);
        }
    }
}

//----------------------------------------------------------------------------//
auto gseg::impl::Segmenter::_getSegmentsMapImpl() -> np::ndarray {
    const p::tuple shape = p::make_tuple(_dataView.getColumnsNum(),
                                         _dataView.getRowsNum());
    const np::dtype indexType = np::dtype::get_builtin<long long>();
    auto ret = np::zeros(shape, indexType);
    std::map<std::size_t, std::size_t> coloursMap;
    std::size_t currNewColour = 1;
    for (std::size_t colI = 0; colI < _dataView.getColumnsNum(); ++colI) {
        for (std::size_t rowI = 0; rowI < _dataView.getRowsNum(); ++rowI) {
            const PixelView pv = _dataView.get(colI, rowI);
            const std::size_t colour = _dsu.getRootData(pv).getFlagColour();
            if (auto colourIt = coloursMap.find(colour);
            colourIt != coloursMap.end()) {
                ret[rowI][colI] = colourIt->second;
            } else {
                coloursMap[currNewColour] = colour;
                ret[rowI][colI] = currNewColour;
                ++currNewColour;
            }
        }
    }
    return ret;
}
