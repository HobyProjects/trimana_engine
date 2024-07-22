/**
 * @file window.hpp
 * @author HobyProjects (https://github.com/HobyProjects/HobyProjects)
 * @brief cross platform window creation
 * @version 0.1
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __window_h__
#define __window_h__

#ifndef _glfw3_h_

/**
 * @brief
 * GLFW_INCLUDE_NONE is special macro
 * that helps us void GL library redefinition
 * or including GL library before glfw
 */
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif

// Our cross-platform api
#include <GLFW/glfw3.h>
#endif

#ifndef __log_h__
#include "log.hpp"
#endif

namespace trimana_core::window
{
    /**
     * @brief
     * This enum class show state of window
     */
    enum class window_status
    {
        maximized, // Window state maximized
        minimized, // Window state minimized
        normal,    // Normal is special case, This enum represent window state that between minimized and maximized (more like windowed state).
    }

    /**
     * @brief `window_fixed_sizes` class hold fixed sizes for  the  window  size
     * changes. All sizes going be evaluate in run-time. after that these  value
     * can not be change. But max_w and  max_h  could  change  base  on  monitor
     * changes events
     */
    struct TRIMANA_CORE_API window_fixed_sizes
    {
        uint32_t min_w{NULL}; // minimum width that window reach
        uint32_t min_h{NULL}; // minimum heihgt that window reach
        uint32_t max_w{NULL}; // maximum width that window reach
        uint32_t max_h{NULL}; // maximum height that window reach
    };

    /**
     * @brief `window_sizes` structure is the one that hold actual window  sizes
     * aka width and height. The `window_fixed_sizes` structure work as  limiter
     * for this struct keeping the width and height between fixed sizes range.
     */
    struct TRIMANA_CORE_API window_sizes
    {
        uint32_t width{NULL};
        uint32_t height{NULL};
    };

    /**
     * @brief Represent window position relevant to the our primary monitor
     */
    struct TRIMANA_CORE_API window_position
    {
        uint32_t posx{NULL}; // X-axis
        uint32_t posy{NULL}; // Y-axis
    }

    /**
     * @brief  `window_attribute`  structure  is  collection  of  condition  and
     * properties  for  example,  structure  holds  our  window  state  and  its
     * activeness also our interaction with the window. As property window title
     * is the major property its hold.
     */
    struct TRIMANA_CORE_API window_attributes
    {
        bool is_vsync_enabled{false};               // Represent is the window double buffered or not
        bool is_focused{false};                     // Represent is the user currently focus on the window or not
        bool is_active{false};                      // Represent activeness of window (This should useful for close window)
        window_status state{window_status::normal}; // Check out `window_status` enum class
        std::string title{"Unknown"};               // Window title
    }

}

#endif // __window_h__