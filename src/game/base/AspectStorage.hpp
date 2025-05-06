#pragma once

/// <summary>
/// Какой-то кусок игровой логики/данных, который может быть на объекте в единственном экземпляре или не быть
/// </summary>
class Aspect
{
public:
	Aspect() = default;
	virtual ~Aspect() = default;

	Aspect(Aspect&&) = default;
	Aspect& operator=(Aspect&&) = default;

	Aspect(const Aspect&) = delete;
	Aspect& operator=(const Aspect&) = delete;
};

/// <summary>
/// Хранилище аспектов
/// </summary>
class AspectStorage
{
public:
	/// <summary>
	/// Вешаем указанный аспект на объект
	/// </summary>
	/// <typeparam name="T">Тип аспекта</typeparam>
	template <typename T>
	void addAspect(T&& aspect);

	/// <summary>
	/// Удаляем указанный аспект с объекта
	/// </summary>
	/// <typeparam name="T">Тип аспекта</typeparam>
	template <typename T>
	void removeAspect();

	/// <summary>
	/// Получаем данные аспекта, если он есть на объекте. Иначе nullptr
	/// </summary>
	/// <typeparam name="T">Тип аспекта</typeparam>
	template <typename T>
	T* getAspect();

	/// <summary>
	/// Получаем данные аспекта, если он есть на объекте. Иначе nullptr
	/// </summary>
	/// <typeparam name="T">Тип аспекта</typeparam>
	template <typename T>
	const T* getAspect() const;

private:
	/// <summary>
	/// Пока храним просто по type_index, но по-хорошему надо для каждого аспекта иметь какой-то идентификатор, чтобы это можно было нормально десериализовать и конфигать
	/// </summary>
	std::unordered_map<std::type_index, std::unique_ptr<Aspect>> mAspects;
};

#include "AspectStorage.inl.hpp"
