/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Template file for class 'zerogl.opengl.OpenGL'.
 */
 
namespace zgl
{
	inline const char* OpenGL::toStringEnum(GLenum e)
	{
		switch(e) {
			case GL_COMPUTE_SHADER: return "GL_COMPUTE_SHADER";
			case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
			case GL_TESS_EVALUATION_SHADER: return "GL_TESS_EVALUATION_SHADER";
			case GL_GEOMETRY_SHADER: return "GL_GEOMETRY_SHADER";
			case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
			case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
			case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
			case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
			case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
			case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
			case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
			case GL_CONTEXT_LOST: return "GL_CONTEXT_LOST";
			case GL_TABLE_TOO_LARGE: return "GL_TABLE_TOO_LARGE";
			case GL_NO_ERROR: return "GL_NO_ERROR";
			default: return "UNKOWN_ENUM";
			//default: return (const char*) gluErrorString(e);
		}
	}

	inline void OpenGL::checkError (const char* file, const char* func, int line) {
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr
				<< "\x1B[36m"
				<< "AT::"
				<< file
				<< "::"
				<< func
				<< "::"
				<< line
				<< "::\x1B[31m"
				<< "ERROR::"
				<< toStringEnum(err)
				<< "\033[0m"
				<< std::endl;
		}
		if (err == GL_NO_ERROR) return;
		exit(EXIT_FAILURE);
	}
} // End namespace zgl
