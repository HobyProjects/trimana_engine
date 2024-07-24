#ifndef __layer_stack_h__
#define __layer_stack_h__

#include <memory>
#include <vector>

#ifndef __layer_h__
#include "layer.hpp"
#endif

namespace trimana_core::layers
{
    /**
     * @brief A stack of layers to be rendered in the Trimana engine.
     *
     * This class is a stack of layers that can be rendered in the Trimana engine. The
     * layers are stored in a vector in the order they are added to the stack, and
     * the most recently added layer will be rendered first.
     *
     * The `push_layer()` and `push_overlay()` methods can be used to add new layers
     * to the stack. The `pop_layer()` and `pop_overlay()` methods can be used to
     * remove layers from the stack.
     *
     * The `begin()` and `end()` methods can be used to iterate over the layers in
     * the stack. The `rbegin()` and `rend()` methods can be used to iterate over the
     * layers in reverse order.
     */
    class TRIMANA_API layer_stack
    {
    public:
        layer_stack() = default;
        ~layer_stack() = default;

        /**
         * @brief Add a new layer to the stack.
         *
         * This method adds a new layer to the stack of layers to be rendered in the
         * Trimana engine. The new layer is added to the top of the stack, and will
         * be rendered first. If multiple layers are added to the stack, the most
         * recently added layer will be rendered first.
         *
         * @param layer The layer to add to the stack.
         */
        void push_layer(std::shared_ptr<layer> layer);

        /**
         * @brief Add a new overlay to the stack.
         *
         * This method adds a new overlay to the stack of layers to be rendered in the
         * Trimana engine. The new overlay is added to the top of the stack, and will
         * be rendered on top of all other layers in the stack. If multiple overlays
         * are added to the stack, the most recently added overlay will be rendered on
         * top of all other layers in the stack.
         *
         * @param layer The overlay to add to the stack.
         */
        void push_overlay(std::shared_ptr<layer> layer);

        /**
         * @brief Remove a layer from the stack.
         *
         * This method removes a layer from the stack of layers to be rendered in the
         * Trimana engine. The layer to be removed is specified by the `layer`
         * parameter. If the specified layer is not found in the stack, this method
         * has no effect.
         *
         * @param layer The layer to remove from the stack.
         */
        void pop_layer(std::shared_ptr<layer> layer);

        /**
         * @brief Remove an overlay from the stack.
         *
         * This method removes an overlay from the stack of layers to be rendered in
         * the Trimana engine. The overlay to be removed is specified by the `layer`
         * parameter. If the specified overlay is not found in the stack, this method
         * has no effect.
         *
         * @param layer The overlay to remove from the stack.
         */
        void pop_overlay(std::shared_ptr<layer> layer);

        /**
         * @brief Begin iterator for the layer stack.
         *
         * This method returns an iterator to the beginning of the layer stack.
         *
         * @return The begin iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::iterator begin() { return m_layers.begin(); }

        /**
         * @brief End iterator for the layer stack.
         *
         * This method returns an iterator to the end of the layer stack.
         *
         * @return The end iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::iterator end() { return m_layers.end(); }

        /**
         * @brief Reverse begin iterator for the layer stack.
         *
         * This method returns a reverse iterator to the beginning of the layer stack.
         *
         * @return The reverse begin iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::reverse_iterator rbegin() { return m_layers.rbegin(); }

        /**
         * @brief Reverse end iterator for the layer stack.
         *
         * This method returns a reverse iterator to the end of the layer stack.
         *
         * @return The reverse end iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::reverse_iterator rend() { return m_layers.rend(); }

        /**
         * @brief Const begin iterator for the layer stack.
         *
         * This method returns a const iterator to the beginning of the layer stack.
         *
         * @return The const begin iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::const_iterator begin() const { return m_layers.begin(); }

        /**
         * @brief Const end iterator for the layer stack.
         *
         * This method returns a const iterator to the end of the layer stack.
         *
         * @return The const end iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::const_iterator end() const { return m_layers.end(); }

        /**
         * @brief Const reverse begin iterator for the layer stack.
         *
         * This method returns a const reverse iterator to the beginning of the layer stack.
         *
         * @return The const reverse begin iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }

        /**
         * @brief Const reverse end iterator for the layer stack.
         *
         * This method returns a const reverse iterator to the end of the layer stack.
         *
         * @return The const reverse end iterator for the layer stack.
         */
        std::vector<std::shared_ptr<layer>>::const_reverse_iterator rend() const { return m_layers.rend(); }

    private:
        /*
         * @brief The list of layers in the layer stack.
         *
         * This vector contains all the layers in the layer stack. The order of the layers
         * in this vector is the order in which they will be rendered and updated.
         */
        std::vector<std::shared_ptr<layer>> m_layers;

        /*
         * @brief The index of the layer to insert the new layer into the layer stack.
         *
         * This variable is used to keep track of the index of the layer that the new layer
         * should be inserted into the layer stack. This is used to ensure that the layer
         * stack is sorted in the correct order.
         *
         * The default value of this variable is NULL, which means that the new layer
         * should be appended to the end of the layer stack.
         */
        uint32_t m_layer_insert_index{NULL};
    };
}

#endif // __layer_stack_h__