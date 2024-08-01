#ifndef __example_layer_h__
#define __example_layer_h__

#include <inputs/input.hpp>
#include <window/window.hpp>
#include <utils/time_steps.hpp>
#include <renderer/renderer.hpp>
#include <layers/imgui_layer.hpp>

namespace engine::app
{
    class example_layer : public core::layers::layer{

        public:
            example_layer() : core::layers::layer("example_layer") {}
            virtual ~example_layer() = default;
        
            void on_attach() override;
            void on_detach() override;
            void on_update(core::timers::time_steps ts) override;
            void on_ui_updates() override;
            void on_event(core::events::event& e) override;

        private:
            core::sptr<core::renderer::shader> m_shader, m_texture_shader;
            core::sptr<core::renderer::texture_2d> m_texture;
            core::sptr<core::renderer::vertex_array> m_vertex_array_triangle;
            core::sptr<core::renderer::vertex_array> m_vertex_array_square;

            core::renderer::orthographic_camera m_camera{-1.0f, 1.0f, -1.0f, 1.0f};
            glm::vec3 m_camera_position{0.0f, 0.0f, 0.0f};
            float m_camera_speed{1.0f};
            float m_camera_rotation{0.0f};
            float m_camera_rotation_speed{30.0f};

            glm::vec4 m_color{0.2f, 0.3f, 0.8f, 1.0f};
            glm::vec3 m_model_position{0.0f, 0.0f, 0.0f};
            float m_model_speed{0.5f};
    };
}

#endif // __example_layer_h__