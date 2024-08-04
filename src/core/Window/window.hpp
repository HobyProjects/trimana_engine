#ifndef __window_h__
#define __window_h__

#include "log.hpp"
#include "assert.hpp"

#ifdef TRIMANA_PRIMARY_RENDERER_OPENGL
#include <gapi/gapi.hpp>
#endif

namespace core::windows
{
    /**
     * @brief
     * This enum class shows the state of the window
     */
    enum class window_status
    {
        maximized, // Window state when maximized
        minimized, // Window state when minimized
        normal,    // Normal window state between minimized and maximized (windowed state).
    };

    /**
     * @brief `window_fixed_sizes` class holds fixed sizes for the window size changes.
     * All sizes are evaluated at run-time. These values cannot be changed. However, max_w and max_h
     * could change based on monitor change events.
     */
    struct TRIMANA_API window_fixed_sizes
    {
        uint32_t min_w{NULL}; // Minimum width that the window can reach
        uint32_t min_h{NULL}; // Minimum height that the window can reach
        uint32_t max_w{NULL}; // Maximum width that the window can reach
        uint32_t max_h{NULL}; // Maximum height that the window can reach
    };

    /**
     * @brief Structure representing the window sizes.
     *
     * This structure holds the actual width and height of the window.
     * The `window_fixed_sizes` structure is used as a limiter for this struct,
     * keeping the width and height within the fixed size range.
     */
    struct TRIMANA_API window_sizes
    {
        /**
         * @brief Width of the window.
         */
        uint32_t width{NULL};

        /**
         * @brief Height of the window.
         */
        uint32_t height{NULL};
    };

    /**
     * @brief Structure representing the position of a window relative to the primary monitor.
     *
     * This structure holds the x-axis and y-axis positions of the window.
     */
    struct TRIMANA_API window_position
    {
        uint32_t posx{NULL}; // X-axis position of the window
        uint32_t posy{NULL}; // Y-axis position of the window
    };

    /**
     * @brief Structure representing the attributes of a window.
     *
     * This structure holds various attributes of a window, such as whether it is
     * double buffered, focused, active, and so on. The attributes are used to
     * control the behavior of a window.
     */
    struct TRIMANA_API window_attributes
    {
        /**
         * @brief Indicates whether the window is double buffered.
         *
         * If true, the window is double buffered, meaning that the screen
         * updates are done in an intermediate buffer before being displayed on
         * the screen.
         */
        bool is_vsync_enabled{false};

        /**
         * @brief Indicates whether the window has focus.
         *
         * If true, the window has focus, meaning that the user is currently
         * interacting with the window.
         */
        bool is_focused{false};

        /**
         * @brief Indicates whether the window is active.
         *
         * If true, the window is active, meaning that it can be closed.
         */
        bool is_active{false};

        /**
         * @brief Represents the current state of the window.
         *
         * This enum class represents the state of the window, which can be
         * maximized, minimized, or normal.
         */
        window_status state{window_status::normal};

        /**
         * @brief The title of the window.
         *
         * This string represents the title of the window, which is displayed in
         * the title bar of the window.
         */
        std::string title{"Unknown"};
    };

    /**
     * @brief Represents the video modes of a window.
     *
     * This struct contains information about the red, green, and blue color bits,
     * as well as the refresh rate of a window.
     */
    struct window_vid_modes
    {
        int32_t red_color_bit{NULL};   /**< The red color bits of the window */
        int32_t green_color_bit{NULL}; /**< The green color bits of the window */
        int32_t blue_color_bit{NULL};  /**< The blue color bits of the window */
        int32_t refresh_rate{NULL};    /**< The refresh rate of the window */
    };

    /**
     * @brief Represents the sizes of the framebuffer of a window.
     *
     * This struct contains the width and height of the framebuffer of a window.
     *
     * @note On some machines screen coordinates and pixels are the same, but on
     * others they will not be.  For example, on a high-DPI display the screen
     * coordinates for a pixel might be (100, 200), but the pixel's position in
     * the framebuffer might be (500, 1000).  The functions to retrieve the size
     * of the framebuffer, @ref glfwGetFramebufferSize and
     * @ref glfwSetFramebufferSizeCallback, return the size of the framebuffer
     * in pixels, and should be used when setting the viewport and scissor
     * rectangles.
     */
    struct window_framebuffer_sizes
    {
        int32_t width{NULL};  /**< The width of the framebuffer of the window */
        int32_t height{NULL}; /**< The height of the framebuffer of the window */
    };   

    /**
     * @brief Represents a window object.
     *
     * This class represents a window object, which encapsulates both a window
     * and its context.
     */
    class TRIMANA_API window
    {
    public:
        /**
         * @brief Constructs a new window object.
         *
         * This constructor initializes a new window object with the given title.
         *
         * @param title The title of the window
         */
        window(const std::string &title); /**< Constructs a new window object with the given title */

        /**
         * @brief Disables copy constructor.
         *
         * Disables the copy constructor to prevent copying of the window object.
         */
        window(window const &) = delete;

        /**
         * @brief Disables move constructor.
         *
         * Disables the move constructor to prevent moving of the window object.
         */
        window(window &&) = delete;

        /**
         * @brief Disables copy assignment operator.
         *
         * Disables the copy assignment operator to prevent copying of the window
         * object.
         */
        window &operator=(window const &) = delete;

        /**
         * @brief Disables move assignment operator.
         *
         * Disables the move assignment operator to prevent moving of the window
         * object.
         */
        window &operator=(window &&) = delete;

        /**
         * @brief Destructs the window object.
         *
         * Destructs the window object and releases any resources associated with
         * it.
         */
        ~window();

        /**
         * @brief Retrieves the native window pointer.
         *
         * @return The native window pointer.
         */
        GLFWwindow *get_native_window() const { return m_window; }

        /**
         * @brief Retrieves a reference to the window attributes.
         *
         * @return A reference to the window attributes.
         */
        window_attributes &get_attributes() { return m_attributes; }

        /**
         * @brief Retrieves a reference to the window sizes.
         *
         * @return A reference to the window sizes.
         */
        window_sizes &get_sizes() { return m_sizes; }

        /**
         * @brief Retrieves a reference to the window position.
         *
         * @return A reference to the window position.
         */
        window_position &get_position() { return m_position; }

        /**
         * @brief Retrieves a reference to the window fixed sizes.
         *
         * @return A reference to the window fixed sizes.
         */
        window_fixed_sizes &get_fixed_sizes() { return m_fixed_sizes; }

        /**
         * @brief Retrieves a reference to the window video modes.
         *
         * @return A reference to the window video modes.
         */
        window_vid_modes &get_vid_mode() { return m_vid_modes; }

        /**
         * @brief Retrieves a reference to the window framebuffer sizes.
         *
         * Retrieves a reference to the window framebuffer sizes. The framebuffer
         * sizes are the sizes of the window in terms of the number of pixels
         * horizontally and vertically.
         *
         * @return A reference to the window framebuffer sizes.
         */
        window_framebuffer_sizes &get_framebuffer_sizes() { return m_window_framebuffer; }

        /**
         * @brief Swaps the front and back buffers of the window.
         *
         * This function is responsible for swapping the front and back buffers of the window,
         * which is necessary for displaying any changes made to the window's content.
         * It is typically called at the end of each frame in a rendering loop.
         */
        void swap_buffers() const;

        #ifdef TRIMANA_PRIMARY_RENDERER_OPENGL

        /**
         * @brief Retrieves the OpenGL context associated with the window.
         *
         * @return The OpenGL context associated with the window.
         */
        const std::shared_ptr<gapi::opengl::gl_context>& get_context() const { return m_context; }

        #endif // TRIMANA_PRIMARY_RENDERER_OPENGL

    private:
        /**
         * @brief m_window - The native window pointer.
         *
         * This member variable holds a pointer to the native window.
         * The native window is the platform-specific window that
         * represents the window on the screen.
         */
        GLFWwindow *m_window{nullptr};

        /**
         * @brief m_attributes - The window attributes.
         *
         * This member variable holds the attributes of the window.
         * The attributes define various properties of the window,
         * such as whether it is resizable, whether it has a title bar,
         * and whether it is fullscreen.
         */
        window_attributes m_attributes{};

        /**
         * @brief m_sizes - The window sizes.
         *
         * This member variable holds the sizes of the window.
         * The sizes include the width and height of the window.
         */
        window_sizes m_sizes{};

        /**
         * @brief m_position - The window position.
         *
         * This member variable holds the position of the window on the screen.
         * The position includes the x and y coordinates of the top-left corner
         * of the window.
         */
        window_position m_position{};

        /**
         * @brief m_fixed_sizes - The window fixed sizes.
         *
         * This member variable holds the fixed sizes of the window.
         * The fixed sizes define the minimum and maximum sizes that the window
         * can be resized to.
         */
        window_fixed_sizes m_fixed_sizes{};

        /**
         * @brief m_vid_modes - The window video modes.
         *
         * This member variable holds the video modes of the window.
         * The video modes define the various resolutions and refresh rates
         * that the window can be set to.
         */
        window_vid_modes m_vid_modes{};

        /**
         * @brief m_window_framebuffer - The window framebuffer sizes.
         *
         * This structure holds the sizes of the window framebuffer.
         * The framebuffer is the region where the pixels are drawn.
         * The dimensions of the framebuffer are usually the same as the
         * window, but can be different on platforms that support high-DPI
         * displays.
         */
        window_framebuffer_sizes m_window_framebuffer{};

        #ifdef TRIMANA_PRIMARY_RENDERER_OPENGL

        /**
         * @brief m_context - The OpenGL context.
         *
         * This member variable holds the OpenGL context associated with the window.
         * The OpenGL context is used to render graphics to the window.
         */
        std::shared_ptr<gapi::opengl::gl_context> m_context{nullptr};

        #endif

    };

}

#endif // __window_h__