#include "gl_vertex_array.hpp"
#include "gl_buffers.hpp"


namespace trimana_core::renderer::opengl
{
    gl_vertex_array::gl_vertex_array()
    {
        glGenVertexArrays(1, &m_renderer_id);
    }

    gl_vertex_array::~gl_vertex_array()
    {
        glDeleteVertexArrays(1, &m_renderer_id);
    }

    void gl_vertex_array::bind() const
    {
        glBindVertexArray(m_renderer_id);
    }

    void gl_vertex_array::unbind() const
    {
        glBindVertexArray(0);
    }

    void gl_vertex_array::emplace_vertex_buffer(const std::shared_ptr<vertex_buffers>& vertex_buffer)
    {
        this->bind();
        vertex_buffer->bind();

        const auto& layout = vertex_buffer->get_layout();
        const auto& elements = layout.get_elements();
        static unsigned int index = 0;

        for (const auto& element : elements)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.component_type, gl_data_type::gl_float, element.normalized, layout.get_stride(), (const void*)element.offset);
            index++;
        }

        m_vertex_buffers.emplace_back(vertex_buffer);
    }

    void gl_vertex_array::set_index_buffer(const std::shared_ptr<index_buffers>& index_buffer)
    {
        this->bind();
        index_buffer->bind();
        m_index_buffer = index_buffer;
    }
}