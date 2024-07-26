#ifndef __gbuffers_h__
#define __gbuffers_h__

#include "platform_detection.hpp"

namespace trimana_core::renderer
{
    /**
     * @brief The vertex_buffers class represents a base class for vertex buffer objects.
     *
     * This class provides an interface for binding and unbinding vertex buffer objects.
     * Derived classes can implement these functions based on their specific requirements.
     */
    class TRIMANA_API vertex_buffers
    {
    public:
        vertex_buffers() = default;
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
    class TRIMANA_API index_buffer
    {
    public:
        /**
         * @brief Default constructor for the index_buffer class.
         */
        index_buffer() = default;

        /**
         * @brief Default destructor for the index_buffer class.
         */
        virtual ~index_buffer() = default;

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
    };

    TRIMANA_API vertex_buffers *create_vertex_buffers();
    TRIMANA_API index_buffer *create_index_buffers();

}

#endif // __gbuffers_h__