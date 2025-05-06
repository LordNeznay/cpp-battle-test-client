#pragma once

class Map
{
public:
	Map(int w, int h);

	/// <summary>
	/// Получить ширину карты
	/// </summary>
	/// <returns></returns>
	int getWidth() const;
	
	/// <summary>
	/// Получить высоту карты
	/// </summary>
	/// <returns></returns>
	int getHeight() const;

protected:
	// Ширина карты
	int mWidth = 0;
	// Высота карты
	int mHeight = 0;
};
