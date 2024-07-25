#ifndef __imgui_layer_h__
#define __imgui_layer_h__

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "window.hpp"
#include "layer.hpp"
#include "events.hpp"
#include "events_window.hpp"
#include "events_keyboard.hpp"
#include "events_mouse.hpp"

namespace trimana_core::layers
{
    /**
     * @enum ui_color_scheme
     * @brief Enumerates the available UI color schemes.
     */
    enum class ui_color_scheme
    {
        dark, /**< Dark color scheme. */
        light /**< Light color scheme. */
    };

    /**
     * @class imgui_layer
     * @brief Represents an ImGui layer that can be added to a window.
     */
    class TRIMANA_API imgui_layer final : public layer
    {
    public:
        /**
         * @brief Constructs an imgui_layer object.
         * @param window The window to attach the layer to.
         * @param color_scheme The color scheme to use for the UI.
         */
        imgui_layer(std::shared_ptr<trimana_core::windows::window> window, ui_color_scheme color_scheme = ui_color_scheme::dark);

        /**
         * @brief Default destructor.
         */
        virtual ~imgui_layer() = default;

        /**
         * @brief Called when the layer is attached to a window.
         */
        virtual void on_attach() override;

        /**
         * @brief Called when the layer is detached from a window.
         */
        virtual void on_detach() override;

        /**
         * @brief Called every frame to update the layer.
         */
        virtual void on_update() override;

        /**
         * @brief Called when an event occurs.
         * @param e The event that occurred.
         */
        virtual void on_event(trimana_core::events::event &e) override;

    private:
        /**
         * @brief Sets the dark color scheme for the UI.
         */
        void use_color_scheme_dark();

        /**
         * @brief Sets the light color scheme for the UI.
         */
        void use_color_scheme_light();

        /**
         * @brief Event handler for window frame resize events.
         * @param e The window frame resize event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_window_frame_resize(trimana_core::events::window_frame_resize_event &e);

        /**
         * @brief Event handler for window focus lost events.
         * @param e The window focus lost event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_window_focus_lost(trimana_core::events::window_focus_lost_event &e);

        /**
         * @brief Event handler for window focus gain events.
         * @param e The window focus gain event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_window_focus_gain(trimana_core::events::window_focus_gain_event &e);

        /**
         * @brief Event handler for keyboard key press events.
         * @param e The keyboard key press event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_keyboard_keypress(trimana_core::events::keyboard_keypress_event &e);

        /**
         * @brief Event handler for keyboard key release events.
         * @param e The keyboard key release event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_keyboard_keyrelease(trimana_core::events::keyboard_keyrelease_event &e);

        /**
         * @brief Event handler for keyboard key repeat events.
         * @param e The keyboard key repeat event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_keyboard_keyrepeat(trimana_core::events::keyboard_keyrepeate_event &e);

        /**
         * @brief Event handler for keyboard character input events.
         * @param e The keyboard character input event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_keyboard_charinput(trimana_core::events::keyboard_keychar_event &e);

        /**
         * @brief Event handler for mouse cursor position change events.
         * @param e The mouse cursor position change event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_cursor_move(trimana_core::events::mouse_cursorpos_change_event &e);

        /**
         * @brief Event handler for mouse button press events.
         * @param e The mouse button press event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_mouse_button_press(trimana_core::events::mouse_button_press_event &e);

        /**
         * @brief Event handler for mouse button release events.
         * @param e The mouse button release event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_mouse_button_release(trimana_core::events::mouse_button_release_event &e);

        /**
         * @brief Event handler for mouse wheel scroll events.
         * @param e The mouse wheel scroll event.
         * @return True if the event was handled, false otherwise.
         */
        bool on_mouse_wheel_scroll(trimana_core::events::mouse_wheel_scroll_event &e);

    private:
        std::weak_ptr<trimana_core::windows::window> m_window; /**< The window the layer is attached to. */
        ui_color_scheme m_color_scheme; /**< The color scheme for the UI. */
    };
}

#endif // __imgui_layer_h__