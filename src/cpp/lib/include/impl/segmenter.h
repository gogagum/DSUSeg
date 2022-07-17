//
// Created by gogagum on 08.07.22.
//

#ifndef DSU_SEG_BACKEND_SEGMENTER_H
#define DSU_SEG_BACKEND_SEGMENTER_H

#include <DSUWithData.hpp>
#include "component_data.h"
#include "data_view.h"
#include "edge.h"

namespace gseg::impl {

    class Segmenter {
    public:
        explicit Segmenter(DataView&& dataView);
    private:
        void _initDSU();
        void _generateEdges();
        void _sortEdges();
    private:
        std::vector<Edge> _edges;
        DataView _dataView;
        gdsu::DSUWithData<PixelView, ComponentData, PixelViewImplCmp> _dsu;
    };

} // gseg::impl

#endif //DSU_SEG_BACKEND_SEGMENTER_H
