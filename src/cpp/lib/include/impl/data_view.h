//
// Created by gogagum on 07.07.22.
//

#ifndef DSU_SEG_BACKEND_DATA_VIEW_H
#define DSU_SEG_BACKEND_DATA_VIEW_H

#include <array>
#include <numeric>

#include "pixel_view.h"
#include "component_data.h"

namespace gseg::impl {

    ////////////////////////////////////////////////////////////////////////////
    // class DataView
    class DataView {
    public:
        class ComponentDataIterator {
        public:
            using iterator_category [[maybe_unused]] = std::input_iterator_tag;
            using value_type [[maybe_unused]] = ComponentData;
            using difference_type [[maybe_unused]] = ptrdiff_t;
            using pointer [[maybe_unused]] = ComponentData*;
            using reference [[maybe_unused]] = ComponentData&;

        private:

            class Proxy {
            public:
                // Constructor
                explicit Proxy(ComponentDataIterator* owner) : _owner(owner) {};
                // Operator ->
                ComponentDataIterator::value_type* operator->() {
                    return (value_type *) _owner->_owner;
                }
            private:
                ComponentDataIterator* _owner;
            };


        public:

            /**
             * Pixel view iterator constructor.
             * @param owner - data view to take data from.
             * @param i - vertical index (row index).
             * @param j - horizontal index (column index).
             */
            ComponentDataIterator(const DataView* owner, std::size_t i, std::size_t j);

            /**
             * Move to the next pixel.
             * @return
             */
            ComponentDataIterator operator++();

            /**
             * Comparison operator.
             * @param other - pixel to compare to.
             * @return `true if iterators are equal. `false if they are not
             * equal.
             */
            bool operator==(const ComponentDataIterator& other) const;

            /**
             * Not equal operator
             * @param other
             * @return `true if iterators are not equal. `false if they are
             * equal.
             */
            bool operator!=(const ComponentDataIterator& other) const;

            /**
             * Dereference operator.
             * @return view to an iterated pixel.
             */
            ComponentData operator*() const;

            Proxy operator->() {
                return Proxy(this);
            }

        private:
            // Row index.
            std::size_t _i;
            // Column index.
            std::size_t _j;
            // Pointer to the data view which iterator is owned by.
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

        /**
         * Get number of rows.
         * @return number of rows.
         */
        [[nodiscard]] std::size_t getRowsNum() const;

        /**
         * Get number of columns.
         * @return number of columns.
         */
        [[nodiscard]] std::size_t getColumnsNum() const;

        /**
         * Get iterator to a data view beginning.
         * @return iterator to beginning.
         */
        [[nodiscard]] ComponentDataIterator getPixelsBegin() const;

        /**
         * Get iterator to data view end.
         * @return iterator to end.
         */
        [[nodiscard]] ComponentDataIterator getPixelsEnd() const;

    private:
        // Pointer to image data.
        double* _data;
        // Dimensions array.
        std::array<std::size_t, 3> _dimensions;
    private:
        friend class PixelView;
    };

}

#endif //DSU_SEG_BACKEND_DATA_VIEW_H
