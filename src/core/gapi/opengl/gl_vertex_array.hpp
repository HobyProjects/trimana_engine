#ifndef __gl_vertex_array_h__
#define __gl_vertex_array_h__

#include "gvertex_array.hpp"

namespace trimana_core::renderer::opengl
{
    /**
     * @brief The gl_vertex_array class represents a vertex array object in OpenGL.
     *
     * This class inherits from the vertex_array base class and provides an implementation
     * for OpenGL-specific functionality.
     */
    class gl_vertex_array : public vertex_array
    {
    public:
        /**
         * @brief Constructs a new gl_vertex_array object.
         */
        gl_vertex_array();

        /**
         * @brief Destroys the gl_vertex_array object.
         */
        virtual ~gl_vertex_array();

        /**
         * @brief Binds the vertex array object.
         */
        virtual void bind() const override;

        /**
         * @brief Unbinds the vertex array object.
         */
        virtual void unbind() const override;

        /**
         * @brief Adds a vertex buffer to the vertex array.
         *
         * @param vertex_buffer The vertex buffer to add.
         */
        virtual void emplace_vertex_buffer(const std::shared_ptr<vertex_buffers> &vertex_buffer) override;

        /**
         * @brief Sets the index buffer for the vertex array.
         *
         * @param index_buffer The index buffer to set.
         */
        virtual void set_index_buffer(const std::shared_ptr<index_buffers> &index_buffer) override;

        /**
         * @brief Returns the vector of vertex buffers associated with the vertex array.
         *
         * @return The vector of vertex buffers.
         */
        const std::vector<std::shared_ptr<vertex_buffers>> &get_vertex_buffers() const override { return m_vertex_buffers; }

        /**
         * @brief Returns the index buffer associated with the vertex array.
         *
         * @return The index buffer.
         */
        const std::shared_ptr<index_buffers> &get_index_buffer() const override { return m_index_buffer; }

    private:
        uint32_t m_renderer_id;                                        // The ID of the renderer
        std::vector<std::shared_ptr<vertex_buffers>> m_vertex_buffers; // Vector of vertex buffers
        std::shared_ptr<index_buffers> m_index_buffer;                 // Index buffer
    };
}

#endif // __gl_vertex_array_h__