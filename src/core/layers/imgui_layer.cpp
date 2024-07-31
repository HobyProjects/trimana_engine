#include "imgui_layer.hpp"

#ifndef __assert_h__
#include "assert.hpp"
#endif

/**
 * Maps a GLFW key code to the corresponding ImGui key code.
 *
 * @param key The GLFW key code to map.
 * @return The corresponding ImGui key code.
 */
static ImGuiKey glfw_to_imgui_keymap(int key)
{
    switch (key)
    {
    case GLFW_KEY_TAB:
        return ImGuiKey_Tab;
    case GLFW_KEY_LEFT:
        return ImGuiKey_LeftArrow;
    case GLFW_KEY_RIGHT:
        return ImGuiKey_RightArrow;
    case GLFW_KEY_UP:
        return ImGuiKey_UpArrow;
    case GLFW_KEY_DOWN:
        return ImGuiKey_DownArrow;
    case GLFW_KEY_PAGE_UP:
        return ImGuiKey_PageUp;
    case GLFW_KEY_PAGE_DOWN:
        return ImGuiKey_PageDown;
    case GLFW_KEY_HOME:
        return ImGuiKey_Home;
    case GLFW_KEY_END:
        return ImGuiKey_End;
    case GLFW_KEY_INSERT:
        return ImGuiKey_Insert;
    case GLFW_KEY_DELETE:
        return ImGuiKey_Delete;
    case GLFW_KEY_BACKSPACE:
        return ImGuiKey_Backspace;
    case GLFW_KEY_SPACE:
        return ImGuiKey_Space;
    case GLFW_KEY_ENTER:
        return ImGuiKey_Enter;
    case GLFW_KEY_ESCAPE:
        return ImGuiKey_Escape;
    case GLFW_KEY_APOSTROPHE:
        return ImGuiKey_Apostrophe;
    case GLFW_KEY_COMMA:
        return ImGuiKey_Comma;
    case GLFW_KEY_MINUS:
        return ImGuiKey_Minus;
    case GLFW_KEY_PERIOD:
        return ImGuiKey_Period;
    case GLFW_KEY_SLASH:
        return ImGuiKey_Slash;
    case GLFW_KEY_SEMICOLON:
        return ImGuiKey_Semicolon;
    case GLFW_KEY_EQUAL:
        return ImGuiKey_Equal;
    case GLFW_KEY_LEFT_BRACKET:
        return ImGuiKey_LeftBracket;
    case GLFW_KEY_BACKSLASH:
        return ImGuiKey_Backslash;
    case GLFW_KEY_RIGHT_BRACKET:
        return ImGuiKey_RightBracket;
    case GLFW_KEY_GRAVE_ACCENT:
        return ImGuiKey_GraveAccent;
    case GLFW_KEY_CAPS_LOCK:
        return ImGuiKey_CapsLock;
    case GLFW_KEY_SCROLL_LOCK:
        return ImGuiKey_ScrollLock;
    case GLFW_KEY_NUM_LOCK:
        return ImGuiKey_NumLock;
    case GLFW_KEY_PRINT_SCREEN:
        return ImGuiKey_PrintScreen;
    case GLFW_KEY_PAUSE:
        return ImGuiKey_Pause;
    case GLFW_KEY_KP_0:
        return ImGuiKey_Keypad0;
    case GLFW_KEY_KP_1:
        return ImGuiKey_Keypad1;
    case GLFW_KEY_KP_2:
        return ImGuiKey_Keypad2;
    case GLFW_KEY_KP_3:
        return ImGuiKey_Keypad3;
    case GLFW_KEY_KP_4:
        return ImGuiKey_Keypad4;
    case GLFW_KEY_KP_5:
        return ImGuiKey_Keypad5;
    case GLFW_KEY_KP_6:
        return ImGuiKey_Keypad6;
    case GLFW_KEY_KP_7:
        return ImGuiKey_Keypad7;
    case GLFW_KEY_KP_8:
        return ImGuiKey_Keypad8;
    case GLFW_KEY_KP_9:
        return ImGuiKey_Keypad9;
    case GLFW_KEY_KP_DECIMAL:
        return ImGuiKey_KeypadDecimal;
    case GLFW_KEY_KP_DIVIDE:
        return ImGuiKey_KeypadDivide;
    case GLFW_KEY_KP_MULTIPLY:
        return ImGuiKey_KeypadMultiply;
    case GLFW_KEY_KP_SUBTRACT:
        return ImGuiKey_KeypadSubtract;
    case GLFW_KEY_KP_ADD:
        return ImGuiKey_KeypadAdd;
    case GLFW_KEY_KP_ENTER:
        return ImGuiKey_KeypadEnter;
    case GLFW_KEY_KP_EQUAL:
        return ImGuiKey_KeypadEqual;
    case GLFW_KEY_LEFT_SHIFT:
        return ImGuiKey_LeftShift;
    case GLFW_KEY_LEFT_CONTROL:
        return ImGuiKey_LeftCtrl;
    case GLFW_KEY_LEFT_ALT:
        return ImGuiKey_LeftAlt;
    case GLFW_KEY_LEFT_SUPER:
        return ImGuiKey_LeftSuper;
    case GLFW_KEY_RIGHT_SHIFT:
        return ImGuiKey_RightShift;
    case GLFW_KEY_RIGHT_CONTROL:
        return ImGuiKey_RightCtrl;
    case GLFW_KEY_RIGHT_ALT:
        return ImGuiKey_RightAlt;
    case GLFW_KEY_RIGHT_SUPER:
        return ImGuiKey_RightSuper;
    case GLFW_KEY_MENU:
        return ImGuiKey_Menu;
    case GLFW_KEY_0:
        return ImGuiKey_0;
    case GLFW_KEY_1:
        return ImGuiKey_1;
    case GLFW_KEY_2:
        return ImGuiKey_2;
    case GLFW_KEY_3:
        return ImGuiKey_3;
    case GLFW_KEY_4:
        return ImGuiKey_4;
    case GLFW_KEY_5:
        return ImGuiKey_5;
    case GLFW_KEY_6:
        return ImGuiKey_6;
    case GLFW_KEY_7:
        return ImGuiKey_7;
    case GLFW_KEY_8:
        return ImGuiKey_8;
    case GLFW_KEY_9:
        return ImGuiKey_9;
    case GLFW_KEY_A:
        return ImGuiKey_A;
    case GLFW_KEY_B:
        return ImGuiKey_B;
    case GLFW_KEY_C:
        return ImGuiKey_C;
    case GLFW_KEY_D:
        return ImGuiKey_D;
    case GLFW_KEY_E:
        return ImGuiKey_E;
    case GLFW_KEY_F:
        return ImGuiKey_F;
    case GLFW_KEY_G:
        return ImGuiKey_G;
    case GLFW_KEY_H:
        return ImGuiKey_H;
    case GLFW_KEY_I:
        return ImGuiKey_I;
    case GLFW_KEY_J:
        return ImGuiKey_J;
    case GLFW_KEY_K:
        return ImGuiKey_K;
    case GLFW_KEY_L:
        return ImGuiKey_L;
    case GLFW_KEY_M:
        return ImGuiKey_M;
    case GLFW_KEY_N:
        return ImGuiKey_N;
    case GLFW_KEY_O:
        return ImGuiKey_O;
    case GLFW_KEY_P:
        return ImGuiKey_P;
    case GLFW_KEY_Q:
        return ImGuiKey_Q;
    case GLFW_KEY_R:
        return ImGuiKey_R;
    case GLFW_KEY_S:
        return ImGuiKey_S;
    case GLFW_KEY_T:
        return ImGuiKey_T;
    case GLFW_KEY_U:
        return ImGuiKey_U;
    case GLFW_KEY_V:
        return ImGuiKey_V;
    case GLFW_KEY_W:
        return ImGuiKey_W;
    case GLFW_KEY_X:
        return ImGuiKey_X;
    case GLFW_KEY_Y:
        return ImGuiKey_Y;
    case GLFW_KEY_Z:
        return ImGuiKey_Z;
    case GLFW_KEY_F1:
        return ImGuiKey_F1;
    case GLFW_KEY_F2:
        return ImGuiKey_F2;
    case GLFW_KEY_F3:
        return ImGuiKey_F3;
    case GLFW_KEY_F4:
        return ImGuiKey_F4;
    case GLFW_KEY_F5:
        return ImGuiKey_F5;
    case GLFW_KEY_F6:
        return ImGuiKey_F6;
    case GLFW_KEY_F7:
        return ImGuiKey_F7;
    case GLFW_KEY_F8:
        return ImGuiKey_F8;
    case GLFW_KEY_F9:
        return ImGuiKey_F9;
    case GLFW_KEY_F10:
        return ImGuiKey_F10;
    case GLFW_KEY_F11:
        return ImGuiKey_F11;
    case GLFW_KEY_F12:
        return ImGuiKey_F12;
    case GLFW_KEY_F13:
        return ImGuiKey_F13;
    case GLFW_KEY_F14:
        return ImGuiKey_F14;
    case GLFW_KEY_F15:
        return ImGuiKey_F15;
    case GLFW_KEY_F16:
        return ImGuiKey_F16;
    case GLFW_KEY_F17:
        return ImGuiKey_F17;
    case GLFW_KEY_F18:
        return ImGuiKey_F18;
    case GLFW_KEY_F19:
        return ImGuiKey_F19;
    case GLFW_KEY_F20:
        return ImGuiKey_F20;
    case GLFW_KEY_F21:
        return ImGuiKey_F21;
    case GLFW_KEY_F22:
        return ImGuiKey_F22;
    case GLFW_KEY_F23:
        return ImGuiKey_F23;
    case GLFW_KEY_F24:
        return ImGuiKey_F24;
    default:
        return ImGuiKey_None;
    }
}

using namespace core::windows;
using namespace core::events;

namespace core::layers
{
    imgui_layer::imgui_layer(std::shared_ptr<window> window, ui_color_scheme color_scheme) : m_window(window), m_color_scheme(color_scheme), layer("imgui_layer") {}

    void imgui_layer::on_attach()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        // io.ConfigViewportsNoAutoMerge = true;
        // io.ConfigViewportsNoTaskBarIcon = true;

        io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
        io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;

        TRIMANA_ASSERT(m_window.expired() == true, "Window is expired");

        auto window_ptr = m_window.lock();
        ImGui_ImplGlfw_InitForOpenGL(window_ptr->get_native_window(), false);
        ImGui_ImplOpenGL3_Init(window_ptr->get_context()->get_info()->glsl_version().c_str());

        if (m_color_scheme == ui_color_scheme::dark)
            use_color_scheme_dark();
        else
            use_color_scheme_light();
    }

    void imgui_layer::on_detach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void imgui_layer::on_update(core::timers::time_steps delta_time)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.DeltaTime = delta_time;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //[TODO]: enable dockspace when we working with framebuffers / multiple viewports
        //create_dockspace();

        ImGui::ShowDemoWindow();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void imgui_layer::on_event(core::events::event &e)
    {
        event_handler handler(e);
        handler.dispatch<window_frame_resize_event>(EVENTS_CALLBACK(imgui_layer::on_window_frame_resize));
        handler.dispatch<window_focus_lost_event>(EVENTS_CALLBACK(imgui_layer::on_window_focus_lost));
        handler.dispatch<window_focus_gain_event>(EVENTS_CALLBACK(imgui_layer::on_window_focus_gain));
        handler.dispatch<keyboard_keypress_event>(EVENTS_CALLBACK(imgui_layer::on_keyboard_keypress));
        handler.dispatch<keyboard_keyrelease_event>(EVENTS_CALLBACK(imgui_layer::on_keyboard_keyrelease));
        handler.dispatch<keyboard_keyrepeate_event>(EVENTS_CALLBACK(imgui_layer::on_keyboard_keyrepeat));
        handler.dispatch<keyboard_keychar_event>(EVENTS_CALLBACK(imgui_layer::on_keyboard_charinput));
        handler.dispatch<mouse_cursorpos_change_event>(EVENTS_CALLBACK(imgui_layer::on_cursor_move));
        handler.dispatch<mouse_button_press_event>(EVENTS_CALLBACK(imgui_layer::on_mouse_button_press));
        handler.dispatch<mouse_button_release_event>(EVENTS_CALLBACK(imgui_layer::on_mouse_button_release));
        handler.dispatch<mouse_wheel_scroll_event>(EVENTS_CALLBACK(imgui_layer::on_mouse_wheel_scroll));
    }

    void imgui_layer::use_color_scheme_dark()
    {
        ImGui::StyleColorsDark();
        auto &colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.1f, 0.1f, 1.0f};

        colors[ImGuiCol_Header] = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.3f, 0.3f, 1.0f};
        colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

        colors[ImGuiCol_Button] = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.3f, 0.3f, 1.0f};
        colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

        colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.3f, 0.3f, 1.0f};
        colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

        colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
        colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.38f, 0.38f, 1.0f};
        colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.28f, 0.28f, 1.0f};
        colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.2f, 0.2f, 1.0f};

        colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
        colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.15f, 0.15f, 1.0f};

        ImGuiIO &io = ImGui::GetIO();
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 2.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
    }

    void imgui_layer::use_color_scheme_light()
    {
        ImGui::StyleColorsLight();
        ImGuiStyle &style = ImGui::GetStyle();

        // light style from Pacôme Danhiez (user itamago)
        style.Alpha = 1.0f;
        style.FrameRounding = 3.0f;
        style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 2.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
    }

    void imgui_layer::create_dockspace()
    {
        // ImGui DockSpace
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        if (opt_fullscreen)
        {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= -ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        static bool show_dockspace = true;
        ImGui::Begin("Dockspace", &show_dockspace, window_flags);

        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::End();
    }

    bool imgui_layer::on_window_frame_resize(window_frame_resize_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)e.width(), (float)e.height());
        return false;
    }

    bool imgui_layer::on_window_focus_lost(window_focus_lost_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddFocusEvent(false);
        return false;
    }

    bool imgui_layer::on_window_focus_gain(window_focus_gain_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddFocusEvent(true);
        return false;
    }

    bool imgui_layer::on_keyboard_keypress(keyboard_keypress_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddKeyEvent(glfw_to_imgui_keymap(e.keycode()), true);
        return false;
    }

    bool imgui_layer::on_keyboard_keyrelease(keyboard_keyrelease_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddKeyEvent(glfw_to_imgui_keymap(e.keycode()), false);
        return false;
    }

    bool imgui_layer::on_keyboard_keyrepeat(keyboard_keyrepeate_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddKeyEvent(glfw_to_imgui_keymap(e.keycode()), true);
        return false;
    }

    bool imgui_layer::on_keyboard_charinput(keyboard_keychar_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddInputCharacter(e.codepoint());
        return false;
    }

    bool imgui_layer::on_cursor_move(mouse_cursorpos_change_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMousePosEvent((float)e.posx(), (float)e.posy());
        return false;
    }

    bool imgui_layer::on_mouse_button_press(mouse_button_press_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.button(), true);
        return false;
    }

    bool imgui_layer::on_mouse_button_release(mouse_button_release_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.button(), false);
        return false;
    }

    bool imgui_layer::on_mouse_wheel_scroll(mouse_wheel_scroll_event &e)
    {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMouseWheelEvent(e.xoffset(), e.yoffset());
        return false;
    }

}
