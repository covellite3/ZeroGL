/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: C++ file for class 'zerogl.opengl.OpenGL'.
 */
 
// Import header file.
#include "zerogl/opengl/OpenGL.hpp"
#include <sstream>
#include <iomanip>

namespace zgl
{
	std::string OpenGL::toStringEnum(const GLenum e)
	{
		switch (e) {
			// Shader types
			case GL_COMPUTE_SHADER: return "GL_COMPUTE_SHADER";
			case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
			case GL_TESS_EVALUATION_SHADER: return "GL_TESS_EVALUATION_SHADER";
			case GL_TESS_CONTROL_SHADER: return "GL_TESS_CONTROL_SHADER";
			case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
			case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";

			// Error codes
			case GL_NO_ERROR: return "GL_NO_ERROR";
			case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
			case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
			case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
			case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
			case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
			case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
			case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
			case GL_CONTEXT_LOST: return "GL_CONTEXT_LOST";
			case GL_TABLE_TOO_LARGE: return "GL_TABLE_TOO_LARGE";

			// Framebuffer and renderbuffer
			case GL_FRAMEBUFFER_COMPLETE: return "GL_FRAMEBUFFER_COMPLETE";
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
			case GL_FRAMEBUFFER_UNSUPPORTED: return "GL_FRAMEBUFFER_UNSUPPORTED";

			// Texture
			case GL_TEXTURE_2D: return "GL_TEXTURE_2D";
			case GL_TEXTURE_CUBE_MAP: return "GL_TEXTURE_CUBE_MAP";
			case GL_TEXTURE_3D: return "GL_TEXTURE_3D";
			case GL_TEXTURE_2D_ARRAY: return "GL_TEXTURE_2D_ARRAY";

			// Buffers
			case GL_ARRAY_BUFFER: return "GL_ARRAY_BUFFER";
			case GL_ELEMENT_ARRAY_BUFFER: return "GL_ELEMENT_ARRAY_BUFFER";
			case GL_UNIFORM_BUFFER: return "GL_UNIFORM_BUFFER";

			// Drawing modes
			/*case GL_POINTS: return "GL_POINTS";
			case GL_LINES: return "GL_LINES";
			case GL_LINE_STRIP: return "GL_LINE_STRIP";
			case GL_LINE_LOOP: return "GL_LINE_LOOP";
			case GL_TRIANGLES: return "GL_TRIANGLES";
			case GL_TRIANGLE_STRIP: return "GL_TRIANGLE_STRIP";
			case GL_TRIANGLE_FAN: return "GL_TRIANGLE_FAN";*/

			// General
			case GL_DEPTH_TEST: return "GL_DEPTH_TEST";
			case GL_BLEND: return "GL_BLEND";
			case GL_CULL_FACE: return "GL_CULL_FACE";
			case GL_SCISSOR_TEST: return "GL_SCISSOR_TEST";
			case GL_STENCIL_TEST: return "GL_STENCIL_TEST";

			default: {
				std::ostringstream oss;
				oss << "UNKNOWN_ENUM (0x" << std::hex << std::uppercase << e << ")";
			    return oss.str();
			}
		}
	}
} // End namespace zgl
