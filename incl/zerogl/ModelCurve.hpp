/**
 * @author: Asso Corentin
 * @date: 2023-04-19
 * @brief: Header for class 'zerogl.ModelCurve'.
 */

#ifndef H_ZGL_ZEROGL_MODELCURVE
#define H_ZGL_ZEROGL_MODELCURVE

// Includes
#include "zerogl/IModel.hpp"
// End includes

namespace zgl
{
	/**
	 * @author: Asso Corentin
	 * @date: 2023-04-19
	 * @brief: Model for curves and lines.
	 */
	class ModelCurve : public IModel
	{
	private:
	protected:
	public:
		ModelCurve();
		void init(const IMesh& mesh);
	}; // End class ModelCurve

} // End namespace zgl

// Import template file.
#include "zerogl/ModelCurve.tcc"

#endif // H_ZGL_ZEROGL_MODELCURVE
