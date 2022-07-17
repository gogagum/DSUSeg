//
// Created by gogagum on 07.07.22.
//

#ifndef DSU_SEG_BACKEND_DATA_VIEW_H
#define DSU_SEG_BACKEND_DATA_VIEW_H

#include <array>
#include <numeric>

#include "pixel_view.h"

namespace gseg::impl {

    ////////////////////////////////////////////////////////////////////////////
    // class DataView
    class DataView {
    public:
        class PixelViewIterator {
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = PixelView;
            using difference_type = int;
            using pointer = PixelView*;
            using reference = PixelView&;

        public:
            PixelViewIterator(const DataView* owner, std::size_t i, std::size_t j);

            PixelViewIterator operator++();

            bool operator==(const PixelViewIterator& other) const;

            bool operator!=(const PixelViewIterator& other) const;

            PixelView operator*() const;



        private:
            std::size_t _i;
            std::size_t _j;
            const DataView* _owner;
        };

    public:
        /**
         * Data view constructor.
         * @param data - pointer to data.
         * @param dimensions - three dimensions: with, height an channels.
         */
        DataView(double* data, std::array<std::size_t, 3>&& dimensions);

        /**
         * Data view move constructor.
         * @param other - data view to construct from.
         */
        DataView(DataView&& other) noexcept;

        /**
         * Get pixel view by a pair of indexes.
         * @param hor - horizontal index.
         * @param vert - vertical index.
         * @return pixel view.
         */
        [[nodiscard]] PixelView get(std::size_t hor, std::size_t vert) const;

        [[nodiscard]] std::size_t getRowsNum() const;

        [[nodiscard]] std::size_t getColumnsNum() const;

        [[nodiscard]] PixelViewIterator getPixelsBegin() const;

        [[nodiscard]] PixelViewIterator getPixelsEnd() const;

    private:
        double* _data;
        std::array<std::size_t, 3> _dimensions;
    private:
        friend class PixelView;
    };

}

#endif //DSU_SEG_BACKEND_DATA_VIEW_H
