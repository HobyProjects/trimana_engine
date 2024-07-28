#ifndef __gvertex_array_h__
#define __gvertex_array_h__

#include <memory>
#include "gbuffers.hpp"

namespace trimana_core::renderer
{
    class TRIMANA_API vertex_array
    {
    public:
        vertex_array() = default;
        virtual ~vertex_array() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void emplace_vertex_buffer(const std::shared_ptr<vertex_buffers>& vertex_buffer) = 0;
        virtual void emplace_index_buffer(const std::shared_ptr<index_buffers>& index_buffer) = 0;
    };

    TRIMANA_API vertex_array* create_vertex_array();
}


#endif // __gvertex_array_h__