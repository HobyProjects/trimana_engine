#ifndef __gl_buffers_h__
#define __gl_buffers_h__

#include "gbuffers.hpp"
namespace trimana_core::renderer::opengl
{
    /**
     * @brief Enumeration representing the draw type of a vertex buffer object.
     */
    enum class gl_draw_type
    {
        draw_static = GL_STATIC_DRAW,  /**< Static draw type */
        draw_dynamic = GL_DYNAMIC_DRAW /**< Dynamic draw type */
    };

    /**
     * @brief Enumeration representing the data type of a vertex buffer object.
     */
    enum gl_data_type : unsigned int
    {
        none = 0,                    /**< No data type */
        gl_float = GL_FLOAT,         /**< Float data type */
        gl_uint = GL_UNSIGNED_INT,   /**< Unsigned integer data type */
        gl_byte = GL_BYTE,           /**< Byte data type */
        gl_ubyte = GL_UNSIGNED_BYTE, /**< Unsigned byte data type */
        gl_int = GL_INT              /**< Integer data type */
    };

    /**
     * @brief The OpenGL implementation of a vertex buffer.
     *
     * This class represents a vertex buffer in OpenGL.
     * It inherits from the base class vertex_buffers.
     */
    class TRIMANA_API gl_vertex_buffer : public vertex_buffers
    {
    public:
        /**
         * @brief Constructs a gl_vertex_buffer object.
         *
         * @param vertices A pointer to the vertex data.
         * @param size The size of the vertex data in bytes.
         * @param type The draw type of the vertex buffer.
         */
        gl_vertex_buffer(float *vertices, size_t size, gl_draw_type type);

        /**
         * @brief Destroys the gl_vertex_buffer object.
         */
        virtual ~gl_vertex_buffer();

        /**
         * @brief Binds the vertex buffer.
         *
         * This function binds the vertex buffer to the OpenGL context.
         */
        void bind() const override;

        /**
         * @brief Unbinds the vertex buffer.
         *
         * This function unbinds the vertex buffer from the OpenGL context.
         */
        void unbind() const override;

        /**
         * @brief Gets the layout of the vertex buffer.
         * @return The layout of the vertex buffer.
         */
        virtual const buffer_layout &get_layout() const override { return m_layout; }

        /**
         * @brief Sets the layout of the vertex buffer.
         * @param layout The layout of the vertex buffer object.
         */
        virtual void set_layout(const buffer_layout &layout) override { m_layout = layout; }

    private:
        unsigned int m_renderer_id; /**< The ID of the OpenGL renderer. */
        buffer_layout m_layout;     /**< The layout of the vertex buffer. */
    };

    /**
     * @brief The OpenGL implementation of an index buffer.
     *
     * This class represents an index buffer in OpenGL.
     * It inherits from the base class index_buffer.
     */
    class TRIMANA_API gl_index_buffer : public index_buffers
    {
    public:
        /**
         * @brief Constructs a gl_index_buffer object.
         *
         * @param indices A pointer to the index data.
         * @param size The size of the index data in bytes.
         */
        gl_index_buffer(unsigned int *indices, size_t count, gl_draw_type type);

        /**
         * @brief Destroys the gl_index_buffer object.
         */
        virtual ~gl_index_buffer();

        /**
         * @brief Binds the index buffer.
         *
         * This function binds the index buffer to the OpenGL context.
         */
        void bind() const override;

        /**
         * @brief Unbinds the index buffer.
         *
         * This function unbinds the index buffer from the OpenGL context.
         */
        void unbind() const override;

        /**
         * @brief Gets the count of indices in the index buffer.
         * @return The count of indices in the index buffer.
         */
        size_t get_count() const override { return m_count; }

    private:
        size_t m_count;             /**< The count of indices in the index buffer. */
        unsigned int m_renderer_id; /**< The ID of the OpenGL renderer. */
    };
}

#endif // __gl_buffers_h__