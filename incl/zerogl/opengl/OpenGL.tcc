/**
 * @author: Corentin Asso
 * @date: 2023-02-10
 * @brief: Template file for class 'zerogl.opengl.OpenGL'.
 */
 
namespace zgl
{
	inline void OpenGL::checkError (const char* file, const char* func, int line) {
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr
				<< "[OPENGL ERROR DETECTED]\x1B[36m"
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
