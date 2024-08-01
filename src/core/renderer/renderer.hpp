#ifndef __renderer_h__
#define __renderer_h__

#include <memory>
#include <string>
#include <vector>
#include <initializer_list>

#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>


#include "platform_detection.hpp"

namespace core::renderer
{
    /**
     * @brief The context class provides an interface for managing the graphics context.
     *
     * This class serves as a base class for different graphics contexts, such as OpenGL or DirectX.
     * It provides common functionality for initializing the graphics context and swapping buffers.
     */
    class TRIMANA_API context
    {
        public:
            /**
             * @brief Default constructor for the context class.
             */
            context() = default;

            /**
             * @brief Virtual destructor for the context class.
             */
            virtual ~context() = default;

            /**
             * @brief Initializes the graphics context.
             *
             * This function should be implemented by derived classes to initialize the specific graphics context.
             */
            virtual void init() = 0;

            /**
             * @brief Swaps the front and back buffers.
             *
             * This function should be implemented by derived classes to swap the front and back buffers of the graphics context.
             */
            virtual void swap_buffers() = 0;
    };

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
        none    = 0,    // No components
        xy      = 2,    // Two components
        xyz     = 3,    // Three components
        xyzw    = 4,    // Four components
        rgba    = 4,    // Red, green, blue, and alpha components
        uv      = 2,    // U and V components
    };

    /**
     * @brief Enumeration representing the data type of a shader attribute.
     */
    enum class shader_data_type
    {
        none                = 0,        
        float_1             = 4,  
        float_2             = 8,  
        float_3             = 12,  
        float_4             = 16,  
        integer_1           = 4,
        integer_2           = 8,
        integer_3           = 12,
        integer_4           = 16,
        unsigned_int_1      = 4, 
        unsigned_int_2      = 8,
        unsigned_int_3      = 12, 
        unsigned_int_4      = 16,
        matrix_2            = 16, 
        matrix_3            = 36, 
        matrix_4            = 64, 
        boolean             = 1
    };

    /**
     * @brief The buffer_element struct represents an element in a vertex buffer.
     */
    struct TRIMANA_API buffer_element
    {
        std::string name{};                                    // The name of the element
        shader_data_type type{shader_data_type::none};                  // The data type of the element
        element_components component_type{element_components::none};    // The component type of the element
        size_t size{NULL};                                              // The size of the element
        size_t offset{NULL};                                            // The offset of the element
        bool normalized{false};                                         // Whether the element is normalized

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
            : name(name), type(type), component_type(comp_type), size(static_cast<size_t>(type)), offset(0), normalized(normalized)
        {
        }

        /**
         * @brief Default destructor for the buffer_element class.
         */
        ~buffer_element() = default;
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
                : m_elements(elements)
            {
                calculate_stride_and_offset(); // Calculate the stride and offset
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
            /**
             * @brief Calculates the stride and offset of the buffer layout.
             */
            void calculate_stride_and_offset()
            {
                m_stride = 0; // Initialize the stride to zero
                size_t offset = 0; // The offset of the element
                for (auto &element : m_elements)
                {
                    element.offset = offset;  // Set the offset of the element
                    offset += element.size;   // Increment the offset
                    m_stride += element.size; // Increment the stride
                }
            }

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
            virtual void emplace_vertex_buffer(const std::shared_ptr<vertex_buffers> &vertex_buffer) = 0;

            /**
             * @brief Adds an index buffer to the vertex array.
             *
             * @param index_buffer The index buffer to be added.
             */
            virtual void set_index_buffer(const std::shared_ptr<index_buffers> &index_buffer) = 0;

            /**
             * @brief Returns the vector of vertex buffers associated with the vertex array.
             *
             * @return The vector of vertex buffers.
             */
            virtual const std::vector<std::shared_ptr<vertex_buffers>> &get_vertex_buffers() const = 0;

            /**
             * @brief Returns the index buffer associated with the vertex array.
             *
             * @return The index buffer.
             */
            virtual const std::shared_ptr<index_buffers> &get_index_buffer() const = 0;
    };

    /**
     * @brief Creates a new instance of the vertex_array class.
     *
     * @return A pointer to the newly created vertex_array object.
     */
    TRIMANA_API vertex_array *create_vertex_array();

     /**
     * @brief The shader class is an abstract base class for shaders.
     */
    class TRIMANA_API shader
    {
        public:
            shader() = default;
            virtual ~shader() = default;

            /**
             * @brief Binds the shader.
             */
            virtual void bind() const = 0;

            /**
             * @brief Unbinds the shader.
             */
            virtual void unbind() const = 0;

            /**
             * @brief Sets a uniform integer value in the shader.
             * @param name The name of the uniform variable.
             * @param value The integer value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_1i(const std::string &name, int value) = 0;

            /**
             * @brief Sets a uniform unsigned integer value in the shader.
             * @param name The name of the uniform variable.
             * @param value The unsigned integer value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_1ui(const std::string &name, unsigned int value) = 0;

            /**
             * @brief Sets a uniform float value in the shader.
             * @param name The name of the uniform variable.
             * @param value The float value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_1f(const std::string &name, float value) = 0;

            /**
             * @brief Sets a uniform 2D vector value in the shader.
             * @param name The name of the uniform variable.
             * @param value The 2D vector value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_2f(const std::string &name, const glm::vec2 &value) = 0;

            /**
             * @brief Sets a uniform 3D vector value in the shader.
             * @param name The name of the uniform variable.
             * @param value The 3D vector value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_3f(const std::string &name, const glm::vec3 &value) = 0;

            /**
             * @brief Sets a uniform 4D vector value in the shader.
             * @param name The name of the uniform variable.
             * @param value The 4D vector value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_4f(const std::string &name, const glm::vec4 &value) = 0;

            /**
             * @brief Sets a uniform 4x4 matrix value in the shader.
             * @param name The name of the uniform variable.
             * @param value The 4x4 matrix value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_mat4(const std::string &name, const glm::mat4 &value) = 0;

            /**
             * @brief Sets a uniform 3x3 matrix value in the shader.
             * @param name The name of the uniform variable.
             * @param value The 3x3 matrix value to set.
             * @return True if the uniform was set successfully, false otherwise.
             */
            virtual bool set_uniform_mat3(const std::string &name, const glm::mat3 &value) = 0;
    };

    /**
     * @brief Creates a shader object with the given vertex and fragment shader source code.
     * @param vertex_shader The source code of the vertex shader.
     * @param fragment_shader The source code of the fragment shader.
     * @return A pointer to the created shader object.
     */
    TRIMANA_API shader *create_shader(const std::string &vertex_shader, const std::string &fragment_shader);

    /**
     * @brief The base class for renderer APIs.
     * 
     * This class provides an interface for different renderer APIs, such as OpenGL.
     * It defines common functions that all renderer APIs should implement.
     */
    class TRIMANA_API renderer_api
    {
        public:
            /**
             * @brief Enumeration of available renderer APIs.
             */
            enum class api
            {
                none    = 0,    /**< No renderer API */
                opengl  = 1     /**< OpenGL renderer API */
            };

        public:
            /**
             * @brief Draw the indexed vertex array.
             * 
             * This function is responsible for drawing the indexed vertex array.
             * 
             * @param vertex_array The vertex array to be drawn.
             */
            virtual void draw_indexed(const std::shared_ptr<vertex_array>& vertex_array) = 0;

            /**
             * @brief Set the clear color for the renderer.
             * 
             * This function sets the clear color for the renderer.
             * 
             * @param color The clear color to be set.
             */
            virtual void set_clear_color(const glm::vec4& color) = 0;

            /**
             * @brief Clear the renderer.
             * 
             * This function clears the renderer.
             */
            virtual void clear() = 0;

            /**
             * @brief Get the current renderer API.
             * 
             * This function returns the current renderer API.
             * 
             * @return The current renderer API.
             */
            inline static api get_api() { return s_api; }

        private:
            static api s_api; /**< The current renderer API. */
    };


    /**
     * @brief The render_command class provides static functions to control the rendering pipeline.
     */
    class TRIMANA_API render_command
    {
        public:
            /**
             * @brief Sets the clear color for the renderer.
             * @param color The color to set as the clear color.
             */
            inline static void set_clear_color(const glm::vec4 &color)
            {
                m_renderer_api->set_clear_color(color);
            }

            /**
             * @brief Clears the renderer.
             */
            inline static void clear()
            {
                m_renderer_api->clear();
            }

            /**
             * @brief Draws the indexed vertex array using the current renderer API.
             * @param vertex_array The vertex array to draw.
             */
            inline static void api_base_draw_indexed(const std::shared_ptr<vertex_array> &vertex_array)
            {
                m_renderer_api->draw_indexed(vertex_array);
            }

        private:
            static std::shared_ptr<renderer_api> m_renderer_api; /**< The current renderer API. */
    };

    class TRIMANA_API orthographic_camera
    {
        public:
            orthographic_camera(float left, float right, float bottom, float top);
            ~orthographic_camera() = default;

            void set_position(const glm::vec3 &position) { m_position = position; recalculate_view_matrix(); }
            void set_rotation(const glm::vec3  &rotation){ m_rotation = rotation; recalculate_view_matrix();}

            const glm::mat4 &get_projection() const { return m_projection; }
            const glm::mat4 &get_view() const { return m_view; }
            const glm::mat4 &get_view_projection() const { return m_view_projection; }

            const glm::vec3 &get_position() const { return m_position; }
            const glm::vec3  &get_rotation() const { return m_rotation; }

        private:
            void recalculate_view_matrix();

        private:
            glm::mat4 m_projection{1.0f};
            glm::mat4 m_view{1.0f};
            glm::mat4 m_view_projection{1.0f};

            glm::vec3 m_position{0.0f, 0.0f, 0.0f};
            glm::vec3  m_rotation{0.0f};
    };

    /**
     * @brief The renderer class provides an interface for rendering graphics.
     */
    class TRIMANA_API renderer
    {
        public:
            /**
             * @brief Default constructor for the renderer class.
             */
            renderer() = default;

            /**
             * @brief Virtual destructor for the renderer class.
             */
            ~renderer() = default;


            /**
             * Submits a vertex array for rendering.
             *
             * This function takes a shared pointer to a vertex array and submits it for rendering.
             * The vertex array contains the geometry data that will be rendered on the screen.
             *
             * @param vertex_array A shared pointer to the vertex array to be submitted.
             */
            static void submit(const std::shared_ptr<shader>& shader_ptr, const std::shared_ptr<vertex_array> &vertex_array, const glm::mat4& model_matrix = glm::mat4(1.0f));

            
            /**
             * Begins a new rendering scene.
             * This function prepares the renderer to start rendering a new scene.
             * It should be called before any rendering commands are issued.
             */
            static void begin_scene(const glm::mat4& camera_projection);

            /**
             * Ends the current rendering scene.
             * This function finalizes the rendering of the current scene.
             * It should be called after all rendering commands have been issued.
             */
            static void end_scene();
            
            /**
             * @brief Gets the current renderer API.
             * @return The current renderer API.
             */
            inline static renderer_api::api get_api() { return renderer_api::get_api(); }

        private:
            static glm::mat4 m_view_projection_matrix; /**< The view projection matrix. */
    };

}

#endif // __renenderer_h__