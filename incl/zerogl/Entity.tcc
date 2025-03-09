/**
 * @author: Corentin Asso
 * @date: 2025-02-24
 * @brief: Template file for class 'zerogl.Entity'.
 */
 
namespace zgl
{
	template<typename T>
	inline T& Entity::getAttachment(const Component::Key& key) {
		auto attachment = m_attachments[key];
		if (!attachment) {
			throw std::runtime_error("Attachment not found.");
		}

		// Perform dynamic cast to ensure the correct type.
		T* castedAttachment = dynamic_cast<T*>(attachment.get());
		if (!castedAttachment) {
			throw std::runtime_error("Failed to cast attachment to Model.");
		}

		return *castedAttachment;
	}
	// Implementation template's functions and inline functions
	// ...
} // End namespace zgl
