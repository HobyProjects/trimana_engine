#ifndef __gbuffers_h__
#define __gbuffers_h__

#include <GL/glew.h>
#include "platform_detection.hpp"

namespace trimana_core::renderer
{
    /**
     * @brief Enumeration representing the draw type of a vertex buffer object.
     */
    enum class draw_type
    {
        draw_static = GL_STATIC_DRAW,  /**< Static draw type */
        draw_dynamic = GL_DYNAMIC_DRAW /**< Dynamic draw type */
    };

    /**
     * @brief The vertex_buffers class represents a base class for vertex buffer objects.
     *
     * This class provides an interface for binding and unbinding vertex buffer objects.
     * Derived classes can implement these functions based on their specific requirements.
     */
    class TRIMANA_API vertex_buffers
    {
    public:
        /**
         * @brief
         *   Default constructor for the vertex_buffers class.
         */
        vertex_buffers() = default;

        /**
         * @brief Default destructor for the vertex_buffers class.
         */
        virtual ~vertex_buffers() = default;

        /**
         * @brief Binds the vertex buffer object.
         *
         * This function is responsible for binding the vertex buffer object to the rendering pipeline.
         * Derived classes should implement this function to perform the necessary binding operations.
         */
        virtual void bind() const = 0;

        /**
         * @brief Unbinds the vertex buffer object.
         *
         * This function is responsible for unbinding the vertex buffer object from the rendering pipeline.
         * Derived classes should implement this function to perform the necessary unbinding operations.
         */
        virtual void unbind() const = 0;
    };

    /**
     * @brief The index_buffer class represents an abstract index buffer.
     *
     * This class provides an interface for index buffers used in rendering.
     * Subclasses of this class should implement the necessary functionality
     * for binding and unbinding the index buffer.
     */
    class TRIMANA_API index_buffers
    {
    public:
        /**
         * @brief Default constructor for the index_buffer class.
         */
        index_buffers() = default;

        /**
         * @brief Default destructor for the index_buffer class.
         */
        virtual ~index_buffers() = default;

        /**
         * @brief Binds the index buffer for rendering.
         *
         * This function should be implemented by subclasses to bind the index buffer
         * for rendering.
         */
        virtual void bind() const = 0;

        /**
         * @brief Unbinds the index buffer.
         *
         * This function should be implemented by subclasses to unbind the index buffer.
         */
        virtual void unbind() const = 0;

        /**
         * @brief Gets the count of indices in the index buffer.
         * @return The count of indices in the index buffer.
         */
        virtual size_t get_count() const = 0;
    };

    /**
     * @brief Creates a new instance of the vertex_buffers class.
     * @param vertices The array of vertices.
     * @param size The size of the vertices array.
     * @param type The draw type of the vertex buffer object.
     * @return A pointer to the created vertex_buffers object.
     */
    TRIMANA_API vertex_buffers *create_vertex_buffers(float *vertices, size_t size, draw_type type);

    /**
     * @brief Creates a new instance of the index_buffer class.
     * @param indices The array of indices.
     * @param size The size of the indices array.
     * @return A pointer to the created index_buffer object.
     */
    TRIMANA_API index_buffers *create_index_buffers(unsigned int *indices, size_t size, draw_type type);

} // namespace trimana::core::renderer

#endif // __gbuffers_h__