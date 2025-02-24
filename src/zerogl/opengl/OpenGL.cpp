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

	GLenum OpenGL::mapTextureUnit(size_t unit) {
		switch (unit) {
			case 0:		return GL_TEXTURE0;
			case 1:		return GL_TEXTURE1;
			case 2:		return GL_TEXTURE2;
			case 3:		return GL_TEXTURE3;
			case 4:		return GL_TEXTURE4;
			case 5:		return GL_TEXTURE5;
			case 6:		return GL_TEXTURE6;
			case 7:		return GL_TEXTURE7;
			case 8:		return GL_TEXTURE8;
			case 9:		return GL_TEXTURE9;
			case 10:	return GL_TEXTURE10;
			case 11:	return GL_TEXTURE11;
			case 12:	return GL_TEXTURE12;
			case 13:	return GL_TEXTURE13;
			case 14:	return GL_TEXTURE14;
			case 15:	return GL_TEXTURE15;
			case 16:	return GL_TEXTURE16;
			case 17:	return GL_TEXTURE17;
			case 18:	return GL_TEXTURE18;
			case 19:	return GL_TEXTURE19;
			case 20:	return GL_TEXTURE20;
			case 21:	return GL_TEXTURE21;
			case 22:	return GL_TEXTURE22;
			case 23:	return GL_TEXTURE23;
			case 24:	return GL_TEXTURE24;
			case 25:	return GL_TEXTURE25;
			case 26:	return GL_TEXTURE26;
			case 27:	return GL_TEXTURE27;
			case 28:	return GL_TEXTURE28;
			case 29:	return GL_TEXTURE29;
			case 30:	return GL_TEXTURE30;
			case 31:	return GL_TEXTURE31;
			default:	throw std::out_of_range("Invalid texture unit");
		}
	}
} // End namespace zgl
