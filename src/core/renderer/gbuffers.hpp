#ifndef __gbuffers_h__
#define __gbuffers_h__

#include <string>
#include <vector>
#include <initializer_list>

#include <GL/glew.h>
#include "platform_detection.hpp"

namespace trimana_core::renderer
{
    /**
     * @brief Enumeration representing the draw type of a vertex buffer object.
     */
    enum class draw_type
    {
        draw_static,
        draw_dynamic
    };

    /**
     * @brief Enumeration representing the component type of a shader attribute.
     */
    enum element_components : int
    {
        none = 0, // No components
        xy = 2,   // Two components
        xyz = 3,  // Three components
        xyzw = 4, // Four components
        rgba = 4, // Red, green, blue, and alpha components
        uv = 2,   // U and V components
    };

    /**
     * @brief Enumeration representing the data type of a shader attribute.
     */
    enum class shader_data_type
    {
        none, // No data type
        _1f,  // Single float
        _2f,  // Two floats
        _3f,  // Three floats
        _4f,  // Four floats
        _1i,  // Single integer
        _2i,  // Two integers
        _3i,  // Three integers
        _4i,  // Four integers
        _1ui, // Single unsigned integer
        _2ui, // Two unsigned integers
        _3ui, // Three unsigned integers
        _4ui, // Four unsigned integers
        mat2, // 2x2 matrix
        mat3, // 3x3 matrix
        mat4, // 4x4 matrix
        _bool // Boolean
    };

    /**
     * @brief The buffer_element struct represents an element in a vertex buffer.
     */
    struct TRIMANA_API buffer_element
    {
        std::string name;          // The name of the element
        shader_data_type type;     // The data type of the element
        element_components component_type; // The component type of the element
        size_t size;               // The size of the element
        size_t offset;             // The offset of the element
        bool normalized;           // Whether the element is normalized

        /**
         * @brief Default constructor for the buffer_element class.
         */
        buffer_element(){}

        /**
         * @brief Constructs a buffer_element object.
         * @param type The data type of the element.
         * @param name The name of the element.
         * @param normalized Whether the element is normalized.
         */
        buffer_element(shader_data_type type, const std::string &name, element_components comp_type, bool normalized = false)
            : name(name), type(type), component_type(comp_type), size(shader_date_type_size(type)), offset(0), normalized(normalized)
        {
        }

        /**
         * @brief Default destructor for the buffer_element class.
         */
        ~buffer_element() = default;

        /**
         * @brief Gets the size of the data type.
         * @param type The data type.
         * @return The size of the data type.
         */
        size_t shader_date_type_size(shader_data_type type)
        {
            switch (type)
            {
            case shader_data_type::_1f:
                return 4;
            case shader_data_type::_2f:
                return 8;
            case shader_data_type::_3f:
                return 12;
            case shader_data_type::_4f:
                return 16;
            case shader_data_type::_1i:
                return 4;
            case shader_data_type::_2i:
                return 8;
            case shader_data_type::_3i:
                return 12;
            case shader_data_type::_4i:
                return 16;
            case shader_data_type::_1ui:
                return 4;
            case shader_data_type::_2ui:
                return 8;
            case shader_data_type::_3ui:
                return 12;
            case shader_data_type::_4ui:
                return 16;
            case shader_data_type::mat2:
                return 4 * 2 * 2;
            case shader_data_type::mat3:
                return 4 * 3 * 3;
            case shader_data_type::mat4:
                return 4 * 4 * 4;
            case shader_data_type::_bool:
                return 1;
            default:
                return 0;
            }
        }
    };

    /**
     * @brief The buffer_layout class represents the layout of a vertex buffer.
     */
    class TRIMANA_API buffer_layout
    {
    public:

        /**
         * @brief Default constructor for the buffer_layout class.
         */
        buffer_layout() {}
        
        /**
         * @brief Constructs a buffer_layout object.
         */
        buffer_layout(std::initializer_list<buffer_element> elements)
            : m_elements(elements), m_stride(0)
        {
            size_t offset = 0; // The offset of the element
            for (auto &element : m_elements)
            {
                element.offset = offset;  // Set the offset of the element
                offset += element.size;   // Increment the offset
                m_stride += element.size; // Increment the stride
            }
        }

        /**
         * @brief Default destructor for the buffer_layout class.
         */
        ~buffer_layout() = default;

        /**
         * @brief Gets the elements in the buffer layout.
         * @return The elements in the buffer layout.
         */
        const std::vector<buffer_element> &get_elements() const { return m_elements; }

        /**
         * @brief Gets the stride of the buffer layout.
         * @return The stride of the buffer layout.
         */
        size_t get_stride() const { return m_stride; }

        /**
         * @brief  Gets the begin and end iterators for the buffer layout.
         * @return std::vector<buffer_element>::iterator
         */
        std::vector<buffer_element>::iterator begin() { return m_elements.begin(); }

        /**
         * @brief  Gets the begin and end iterators for the buffer layout.
         * @return std::vector<buffer_element>::iterator
         */
        std::vector<buffer_element>::iterator end() { return m_elements.end(); }

        /**
         * @brief  Gets the begin and end const iterators for the buffer layout.
         * @return std::vector<buffer_element>::const_iterator
         */
        std::vector<buffer_element>::const_iterator begin() const { return m_elements.begin(); }

        /**
         * @brief  Gets the begin and end const iterators for the buffer layout.
         * @return std::vector<buffer_element>::const_iterator
         */
        std::vector<buffer_element>::const_iterator end() const { return m_elements.end(); }

    private:
        std::vector<buffer_element> m_elements; // The elements in the buffer layout
        size_t m_stride{NULL};                  // The stride of the buffer layout
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

        /**
         * @brief Gets the layout of the vertex buffer object.
         * @return The layout of the vertex buffer object.
         */
        virtual const buffer_layout &get_layout() const = 0;

        /**
         * @brief Sets the layout of the vertex buffer object.
         * @param layout The layout of the vertex buffer object.
         */
        virtual void set_layout(const buffer_layout &layout) = 0;
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

}

#endif // __gbuffers_h__