#ifndef __grenderer_h__
#define __grenderer_h__

#include "platform_detection.hpp"

namespace trimana_core::renderer
{
    /**
     * @brief Enumeration representing the graphic_renderer API.
     */
    enum class renderer_api
    {
        none = 0,
        opengl = 1
    };

    /**
     * @brief The graphic_renderer class represents the rendering API.
     * 
     * This class provides an interface for the rendering API.
     * It allows the user to query the current rendering API.
     */
    class TRIMANA_API graphic_renderer
    {
    public:

        /**
         * @brief Construct a new graphic_renderer object   
         */
        graphic_renderer() = default;

        /**
         * @brief Destroy the graphic_renderer object
         */
        ~graphic_renderer() = default;

        /**
         * @brief Constructs a graphic_renderer object.
         */
        static renderer_api get_api() { return s_renderer_api; }

    private:
        /**
         * @brief  The current graphic_renderer API.
         */
        static renderer_api s_renderer_api;
    };
}

#endif // __grenenderer_h__