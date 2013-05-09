// DO NOT MODIFY THE HEADERS IF FORZE IS ALREADY COMPILED AS A STATIC LIBRARY
#ifndef __FZGLPROGRAM_H_INCLUDED__
#define __FZGLPROGRAM_H_INCLUDED__
/*
 * FORZE ENGINE: http://forzefield.com
 *
 * Copyright (c) 2011-2012 FORZEFIELD Studios S.L.
 * Copyright (c) 2012 Manuel Martínez-Almeida
 * Copyright (c) 2008-2010 Ricardo Quesada
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 @author Manuel Martínez-Almeida
 */

#include "FZOSW.h"

#if FZ_GL_SHADERS

#include "FZLifeCycle.h"
#include STL_STRING
#if FZ_STL_CPLUSPLUS11
#include STL_UNORDERED_MAP
#else
#include STL_MAP
#endif


using namespace STD;

namespace FORZE {
        
    // uniform names
#define kFZUniformMVMatrix_s                "u_MVMatrix"
#define kFZUniformSampler_s                 "u_texture"
#define kFZUniformColor_s                   "u_color"

    // Attribute names
#define	kFZAttributeNameColor               "a_color"
#define	kFZAttributeNamePosition            "a_position"
#define	kFZAttributeNameTexCoord            "a_texCoord"
    
    enum {
        kFZAttribPosition,
        kFZAttribColor,
        kFZAttribTexCoords,
        
        kFZAttrib_MAX
    };
    
    
#pragma mark - GLShader
    /** GLShader */
    class GLShader
    {
    private:
        GLuint m_shader;
        GLenum m_shaderType;
        bool compileShader(const char*);
       
        
    public:
        //! Constructs an compile an OpenGL shader.
        //! @param source NULL-terminated GLSL code to be compiled.
        //! @param type {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}
        GLShader(const char *source, GLenum type);
        ~GLShader();
        
        
        //! Returns the opengl shader reference.
        GLuint getShader() const {
            return m_shader;
        }
        
        
        //! Returns the shader type.
        //! - GL_VERTEX_SHADER
        //! - GL_FRAGMENT_SHADER.
        GLenum getShaderType() const {
            return m_shaderType;
        }
        
        
        //! Returns the compilation log, useful for debugging.
        string getShaderLog() const;
    };
    
    
#pragma mark - GLProgram

    class GLProgram : public LifeCycle
    {
    private:
        GLuint  m_program;
        
#if FZ_STL_CPLUSPLUS11
        typedef unordered_map<int32_t, GLint> uniformsMap;
#else
        typedef map<int32_t, GLint> uniformsMap;
#endif
        typedef pair<int32_t, GLint> uniformsPair;

        
        uniformsMap m_uniforms;
        
    public:
        //! Constructs and compiles a OpenGl program from two shaders pointers.
        GLProgram(const GLShader *shader1, const GLShader *shader2);
        
        
        //! Constructs and compiles a OpenGl program from two shaders.
        GLProgram(const GLShader& shader1, const GLShader& shader2);

        
        //! Constructs and compiles a OpenGl program given the shader's filenames.
        GLProgram(const char* vertexSFilename, const char* fragmentSFilename);
        
        // Destructor
        ~GLProgram();
        
        
        //! Adds a new shader attribute.
        //! @warning This method must be called before linking the program.
        //! @see link()
        void addAttribute(const char* attributeName, GLuint index);
        
        
        //! Links the program with the attached shaders.
        //! and caches the uniforms' locations.
        //! @warning This method must be called before using the program.
        bool link();
        
        
        //! Prepares the opengl program to be used.
        //! @code fzGLUseProgram(program->getName())
        void use() const;
        
        
        //! This method add the three default attributes.
        //! @code addAttribute(kFZAttributeNamePosition, kFZAttribPosition);
        //! @code addAttribute(kFZAttributeNameColor, kFZAttribColor);
        //! @code addAttribute(kFZAttributeNameTexCoord, kFZAttribTexCoords);
        //! @warning This method must be called before linking the program.
        //! @see addAttribute()
        void addGenericAttributes();
        
        
        //! Returns opengl program reference.
        GLuint getName() const {
            return m_program;
        }
        
        
        //! Returns the program log.
        string getProgramLog();
        
        
        //! Returns the uniform locations given the key value.
        //! @warning this method should be called before link the program.
        GLint getUniform(const char* uniform) const;
        
        void setUniform1i(const char* uniform, int v1) const;
        void setUniform1f(const char* uniform, float v1) const;
        void setUniform2f(const char* uniform, float v1, float v2) const;
        void setUniform3f(const char* uniform, float v1, float v2, float v3) const;
        void setUniform4f(const char* uniform, float v1, float v2, float v3, float v4) const;
        
        void setUniform1iv(const char* uniform, GLsizei count, int* values) const;
        void setUniform1fv(const char* uniform, GLsizei count, float* values) const;
        void setUniform2fv(const char* uniform, GLsizei count, float* values) const;
        void setUniform3fv(const char* uniform, GLsizei count, float* values) const;
        void setUniform4fv(const char* uniform, GLsizei count, float* values) const;
        
        void setUniform4x4f(const char* uniform, GLsizei count, bool transpose, float *matrix) const;
    };
}
#endif
#endif
