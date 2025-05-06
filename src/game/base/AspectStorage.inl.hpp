
template <typename T>
inline void AspectStorage::addAspect(T&& aspect)
{
	static_assert(std::is_base_of<Aspect, T>::value, "T must be derived from Aspect");

	bool ok = mAspects.emplace(std::type_index(typeid(T)), std::make_unique<T>(std::forward<T>(aspect))).second;
	if (not ok)
	{
		// Пока ошибку проигнорим, но когда-то в будущем надо будет обрабатывать
	}
}

template <typename T>
inline void AspectStorage::removeAspect()
{
	static_assert(std::is_base_of<Aspect, T>::value, "T must be derived from Aspect");

	mAspects.erase(std::type_index(typeid(T)));
}

template <typename T>
inline T* AspectStorage::getAspect()
{
	static_assert(std::is_base_of<Aspect, T>::value, "T must be derived from Aspect");

	if (auto it = mAspects.find(std::type_index(typeid(T))); it != mAspects.end())
	{
		return dynamic_cast<T*>(it->second.get());
	}

	return nullptr;
}

template <typename T>
inline const T* AspectStorage::getAspect() const
{
	static_assert(std::is_base_of<Aspect, T>::value, "T must be derived from Aspect");

	if (auto it = mAspects.find(std::type_index(typeid(T))); it != mAspects.end())
	{
		return dynamic_cast<T*>(it->second.get());
	}

	return nullptr;
}
