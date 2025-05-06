#pragma once

/// <summary>
/// �����-�� ����� ������� ������/������, ������� ����� ���� �� ������� � ������������ ���������� ��� �� ����
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
/// ��������� ��������
/// </summary>
class AspectStorage
{
public:
	/// <summary>
	/// ������ ��������� ������ �� ������
	/// </summary>
	/// <typeparam name="T">��� �������</typeparam>
	template <typename T>
	void addAspect(T&& aspect);

	/// <summary>
	/// ������� ��������� ������ � �������
	/// </summary>
	/// <typeparam name="T">��� �������</typeparam>
	template <typename T>
	void removeAspect();

	/// <summary>
	/// �������� ������ �������, ���� �� ���� �� �������. ����� nullptr
	/// </summary>
	/// <typeparam name="T">��� �������</typeparam>
	template <typename T>
	T* getAspect();

	/// <summary>
	/// �������� ������ �������, ���� �� ���� �� �������. ����� nullptr
	/// </summary>
	/// <typeparam name="T">��� �������</typeparam>
	template <typename T>
	const T* getAspect() const;

private:
	/// <summary>
	/// ���� ������ ������ �� type_index, �� ��-�������� ���� ��� ������� ������� ����� �����-�� �������������, ����� ��� ����� ���� ��������� ��������������� � ���������
	/// </summary>
	std::unordered_map<std::type_index, std::unique_ptr<Aspect>> mAspects;
};

#include "AspectStorage.inl.hpp"
