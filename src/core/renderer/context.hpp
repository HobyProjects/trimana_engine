#ifndef __gcontext_h__
#define __gcontext_h__

#include "platform_detection.hpp"

namespace trimana_core::renderer
{
    /**
     * @brief The graphics_context class provides an interface for managing the graphics context.
     *
     * This class serves as a base class for different graphics contexts, such as OpenGL or DirectX.
     * It provides common functionality for initializing the graphics context and swapping buffers.
     */
    class TRIMANA_API graphics_context
    {
    public:
        /**
         * @brief Default constructor for the graphics_context class.
         */
        graphics_context() = default;

        /**
         * @brief Virtual destructor for the graphics_context class.
         */
        virtual ~graphics_context() = default;

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
}

#endif // __gcontext_h__