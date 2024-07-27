#include "gl_buffers.hpp"

namespace trimana_core::renderer::opengl
{
    /////////////////////////////////////////////////////////////////////////////////
    ///                              gl_vertex_buffer                             ///
    /////////////////////////////////////////////////////////////////////////////////

    gl_vertex_buffer::gl_vertex_buffer(float *vertices, size_t size, gl_draw_type type)
    {
        glGenBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, static_cast<GLenum>(type));
    }

    gl_vertex_buffer::~gl_vertex_buffer()
    {
        glDeleteBuffers(1, &m_renderer_id);
    }

    void gl_vertex_buffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    }

    void gl_vertex_buffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////////////
    ///                              gl_index_buffer                              ///
    /////////////////////////////////////////////////////////////////////////////////

    gl_index_buffer::gl_index_buffer(unsigned int *indices, size_t count, gl_draw_type type)
    {
        m_count = count;
        glGenBuffers(1, &m_renderer_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(size_t), indices, static_cast<GLenum>(type));
    }

    gl_index_buffer::~gl_index_buffer()
    {
        glDeleteBuffers(1, &m_renderer_id);
    }

    void gl_index_buffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    }

    void gl_index_buffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}