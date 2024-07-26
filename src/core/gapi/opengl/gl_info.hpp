#ifndef __glinfo_h__
#define __glinfo_h__

#include <string>
#include <sstream>
#include <GL/glew.h>

#include "log.hpp"
#include "platform_detection.hpp"

namespace trimana_core::renderer::opengl
{
    class TRIMANA_API gl_info
    {
    public:
        gl_info()
        {
            m_gl_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
            m_gl_vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
            m_gl_renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
            m_glsl_version = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));

            char GL_MAJOR = m_gl_version[0];
            char GL_MINOR = m_gl_version[2];
            char GL_PATCH = m_gl_version[4];

            std::stringstream ss;
            ss << "#version " << GL_MAJOR << GL_MINOR << GL_PATCH << " core";
            m_glsl_version = ss.str();
        }

        ~gl_info() = default;

        const std::string &gl_version() const { return m_gl_version; }
        const std::string &gl_vendor() const { return m_gl_vendor; }
        const std::string &gl_renderer() const { return m_gl_renderer; }
        const std::string &glsl_version() const { return m_glsl_version; }

        void show_gl_info() const
        {
            TRIMANA_CORE_INFO("--------------------------------------------------------");
            TRIMANA_CORE_INFO("OpenGL Info:");
            TRIMANA_CORE_INFO("     Version:        {0}", m_gl_version);
            TRIMANA_CORE_INFO("     Vendor:         {0}", m_gl_vendor);
            TRIMANA_CORE_INFO("     Renderer:       {0}", m_gl_renderer);
            TRIMANA_CORE_INFO("     GLSL Version:   {0}", m_glsl_version);
            TRIMANA_CORE_INFO("--------------------------------------------------------");
        }

    private:
        std::string m_gl_version;
        std::string m_gl_vendor;
        std::string m_gl_renderer;
        std::string m_glsl_version;
    };
}

#endif // __glinfo_h__