#pragma once

class Map
{
public:
	Map(int w, int h);

	/// <summary>
	/// �������� ������ �����
	/// </summary>
	/// <returns></returns>
	int getWidth() const;
	
	/// <summary>
	/// �������� ������ �����
	/// </summary>
	/// <returns></returns>
	int getHeight() const;

protected:
	// ������ �����
	int mWidth = 0;
	// ������ �����
	int mHeight = 0;
};
