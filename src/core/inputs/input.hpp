#ifndef __input_h__
#define __input_h__

#include "window.hpp"

namespace core::inputs
{
    /**
     * @brief The input class provides functions to handle user input such as keyboard and mouse events.
     */
    class TRIMANA_API input
    {
    public:
        /**
         * @brief Sets the target window for input events.
         * @param window A shared pointer to the target window.
         */
        static void target_window(const std::shared_ptr<core::windows::window> window);

        /**
         * @brief Checks if a specific key is currently pressed.
         * @param key_code The key code of the key to check.
         * @return true if the key is pressed, false otherwise.
         */
        static bool is_key_pressed(int32_t key_code);

        /**
         * @brief Checks if a specific mouse button is currently pressed.
         * @param button The button code of the mouse button to check.
         * @return true if the mouse button is pressed, false otherwise.
         */
        static bool is_mouse_button_pressed(int32_t button);

        /**
         * @brief Gets the current mouse position.
         * @return A pair of floats representing the x and y coordinates of the mouse position.
         */
        static std::pair<float, float> mouse_pos();

        /**
         * @brief Gets the current x-coordinate of the mouse position.
         * @return The x-coordinate of the mouse position.
         */
        static float mouse_pos_x();

        /**
         * @brief Gets the current y-coordinate of the mouse position.
         * @return The y-coordinate of the mouse position.
         */
        static float mouse_pos_y();

    private:
        input() = default;
        virtual ~input() = default;
        input(const input&) = delete;
        input& operator=(const input&) = delete;

    private:
        static std::weak_ptr<core::windows::window> m_window;
    };
    
} // namespace trimana_core::inputs

#endif // __input_h__