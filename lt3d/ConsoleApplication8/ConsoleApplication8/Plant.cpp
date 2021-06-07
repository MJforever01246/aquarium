#include<stdlib.h>
#include<vector>
class Plant {
public:
	int count = 0;
	std::vector<float> X;
	std::vector<float> Y;
	std::vector<float> Z;
	int range = 50;
	void show(int count) {
		for (int i = 0; i < count; i++)
			add();
	}

	void add()
	{
		int x = (rand() % (range / 2))*(rand() % 2 ? 1 : -1);
		int z = (rand() % (range / 2))*(rand() % 2 ? 1 : -1);
		this->X.push_back(x);
		this->Z.push_back(z);
		this->Y.push_back(0);
		this->count++;
	}

	void remove() {
		if (this->count > 0)
		{
			this->X.pop_back();
			this->Z.pop_back();
			this->Y.pop_back();
			this->count--;
		}		
	}
};