//
// Created by gogagum on 08.07.22.
//

#ifndef DSU_SEG_BACKEND_SEGMENTER_H
#define DSU_SEG_BACKEND_SEGMENTER_H

#include "data_view.h"

namespace gseg::impl {

    class Segmenter {
    public:
        explicit Segmenter(DataView&& dataView);
    private:
        DataView _dataView;
    };

} // gseg::impl

#endif //DSU_SEG_BACKEND_SEGMENTER_H
