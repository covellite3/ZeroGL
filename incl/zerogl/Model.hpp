/**
 * @author: Corentin Asso
 * @date: 2023-03-31
 * @brief: Header for class 'zerogl.Model'.
 */

#ifndef H_ZGL_ZEROGL_MODEL
#define H_ZGL_ZEROGL_MODEL

// Includes
#include "zerogl/IModel.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Corentin Asso
	 * @date: 2023-03-31
	 * @brief: Model class.
	 */
	class Model : public IModel
	{
	public:
		Model();
		void init(const IMesh& mesh);
	}; // End class Model

} // End namespace zgl

// Import template file.
#include "zerogl/Model.tcc"

#endif // H_ZGL_ZEROGL_MODEL
