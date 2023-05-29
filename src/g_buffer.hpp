#include "common.hpp"

class GBuffer {
public:
    GBuffer(
        GLuint screen_w,
        GLuint screen_h
    ) {
        // glTextureParameteri(m_position_texture.get_id(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTextureParameteri(m_position_texture.get_id(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // glTextureStorage2D(m_position_texture.get_id(), 0, GL_RGBA16F, screen_w, screen_h);
        // glNamedFramebufferTexture(m_framebuffer.get_id(), GL_COLOR_ATTACHMENT0, m_position_texture.get_id(), 0);
    
        // glTextureParameteri(m_normal_texture.get_id(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTextureParameteri(m_normal_texture.get_id(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // glTextureStorage2D(m_normal_texture.get_id(), 0, GL_RGBA16F, screen_w, screen_h);
        // glNamedFramebufferTexture(m_framebuffer.get_id(), GL_COLOR_ATTACHMENT1, m_normal_texture.get_id(), 0);

        // glTextureParameteri(m_diffuse_texture.get_id(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTextureParameteri(m_diffuse_texture.get_id(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // glTextureStorage2D(m_diffuse_texture.get_id(), 0, GL_RGBA, screen_w, screen_h);
        // glNamedFramebufferTexture(m_framebuffer.get_id(), GL_COLOR_ATTACHMENT2, m_diffuse_texture.get_id(), 0);
    
        // glTextureParameteri(m_depth_texture.get_id(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTextureParameteri(m_depth_texture.get_id(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // glTextureStorage2D(m_depth_texture.get_id(), 0, GL_DEPTH_COMPONENT32F, screen_w, screen_h);
        // glNamedFramebufferTexture(m_framebuffer.get_id(), GL_DEPTH_ATTACHMENT, m_depth_texture.get_id(), 0);

        glGenFramebuffers(1, &m_framebuffer_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_id);

        glGenTextures(1, &m_position_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_position_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 800, 600, 0, GL_RGBA, GL_FLOAT, NULL);
        glTextureParameteri(m_position_texture_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_position_texture_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_position_texture_id, 0);
        
        glGenTextures(1, &m_normal_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_normal_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 800, 600, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normal_texture_id, 0);
        
        glGenTextures(1, &m_diffuse_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_diffuse_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_diffuse_texture_id, 0);
        
        glGenTextures(1, &m_depth_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_depth_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture_id, 0);

        GLuint attachments[3] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
        };

        glNamedFramebufferDrawBuffers(m_framebuffer_id, 3, attachments);

        if(glCheckNamedFramebufferStatus(m_framebuffer_id, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            throw "error";
        }
    }

    GLuint
    get_framebuffer_id() const {
        return m_framebuffer_id;
    }

    GLuint
    get_position_texture_id() const {
        return m_position_texture_id;
    }

    GLuint
    get_normal_texture_id() const {
        return m_normal_texture_id;
    }

    GLuint
    get_diffuse_texture_id() const {
        return m_diffuse_texture_id;
    }

    void bind_framebuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer_id);
    }

    void bind_position(GLuint unit) {
        glBindTextureUnit(unit, m_position_texture_id);
    }

    void bind_normal(GLuint unit) {
        glBindTextureUnit(unit, m_normal_texture_id);
    }

    void bind_diffuse(GLuint unit) {
        glBindTextureUnit(unit, m_diffuse_texture_id);
    }

    GLuint m_framebuffer_id;

    GLuint m_position_texture_id;
    GLuint m_normal_texture_id;
    GLuint m_diffuse_texture_id;
    GLuint m_depth_texture_id;
};