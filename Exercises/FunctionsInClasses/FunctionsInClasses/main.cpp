#include <iostream>

class Box
{
public:

	int getVolume()
	{
		return length * width * height;
	}

	void setLength(int l)
	{
		length = l;
	}

	void setWidth(int w)
	{
		width = w;
	}

	void setHeight(int h)
	{
		height = h;
	}

private:

	int length;
	int width;
	int height;

};

int main()
{
	Box box1;
	Box box2;

	box1.setLength(10);
	box1.setWidth(10);
	box1.setHeight(10);
	
	std::cout << box1.getVolume() << std::endl;

	box2.setLength(5);
	box2.setWidth(10);
	box2.setHeight(40);

	std::cout << box2.getVolume() << std::endl;

	system("pause");
	return 0;
}