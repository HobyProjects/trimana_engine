#include "layer_stack.hpp"

namespace core::layers
{
    /**
     * @brief Adds a new layer to the stack.
     *
     * @param layer The layer to be added.
     */
    void layer_stack::push_layer(sptr<layer> layer)
    {
        m_layers.emplace(m_layers.begin() + m_layer_insert_index++, layer);
    }

    /**
     * @brief Adds a new overlay to the stack.
     *
     * @param layer The overlay to be added.
     */
    void layer_stack::push_overlay(sptr<layer> layer)
    {
        m_layers.emplace_back(layer);
    }

    /**
     * @brief Removes a layer from the stack.
     *
     * @param layer The layer to be removed.
     */
    void layer_stack::pop_layer(sptr<layer> layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_insert_index, layer);
        if (it != m_layers.begin() + m_layer_insert_index)
        {
            layer->on_detach(); // Call the on_detach() method of the layer
            layer->on_detach();
            m_layers.erase(it);
            m_layer_insert_index--;
        }
    }

    /**
     * @brief Removes an overlay from the stack.
     *
     * @param layer The overlay to be removed.
     */
    void layer_stack::pop_overlay(sptr<layer> layer)
    {
        auto it = std::find(m_layers.begin() + m_layer_insert_index, m_layers.end(), layer);
        if (it != m_layers.end())
        {
            layer->on_detach(); // Call the on_detach() method of the overlay
            layer->on_detach();
            m_layers.erase(it);
        }
    }
}