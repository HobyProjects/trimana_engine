#ifndef __gvertex_array_h__
#define __gvertex_array_h__

#include <memory>
#include "gbuffers.hpp"

namespace trimana_core::renderer
{
    /**
     * @brief The vertex_array class represents a vertex array object.
     * 
     * This class provides an interface for managing vertex array objects.
     * It allows binding and unbinding of the vertex array, as well as
     * adding vertex buffers and index buffers to the array.
     */
    class TRIMANA_API vertex_array
    {
    public:
        /**
         * @brief Default constructor for the vertex_array class.
         */
        vertex_array() = default;

        /**
         * @brief Default destructor for the vertex_array class.
         */
        virtual ~vertex_array() = default;

        /**
         * @brief Binds the vertex array.
         */
        virtual void bind() const = 0;

        /**
         * @brief Unbinds the vertex array.
         */
        virtual void unbind() const = 0;

        /**
         * @brief Adds a vertex buffer to the vertex array.
         * 
         * @param vertex_buffer The vertex buffer to be added.
         */
        virtual void emplace_vertex_buffer(const std::shared_ptr<vertex_buffers>& vertex_buffer) = 0;

        /**
         * @brief Adds an index buffer to the vertex array.
         * 
         * @param index_buffer The index buffer to be added.
         */
        virtual void set_index_buffer(const std::shared_ptr<index_buffers>& index_buffer) = 0;

        /**
         * @brief Returns the vector of vertex buffers associated with the vertex array.
         * 
         * @return The vector of vertex buffers.
         */
        virtual const std::vector<std::shared_ptr<vertex_buffers>>& get_vertex_buffers() const = 0;

        /**
         * @brief Returns the index buffer associated with the vertex array.
         * 
         * @return The index buffer.
         */
        virtual const std::shared_ptr<index_buffers>& get_index_buffer() const = 0;
    };

    /**
     * @brief Creates a new instance of the vertex_array class.
     * 
     * @return A pointer to the newly created vertex_array object.
     */
    TRIMANA_API vertex_array* create_vertex_array();
}

#endif // __gvertex_array_h__