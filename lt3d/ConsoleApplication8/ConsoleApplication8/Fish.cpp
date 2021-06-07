#include<stdlib.h>
#include<vector>
class Fish {
public:
	int count = 0;
	int range = 50;
	std::vector<int> type;
	std::vector<float> X;
	std::vector<float> Y;
	std::vector<float> Z;
	std::vector<float> angle;
	std::vector<float> angle_step;
	std::vector<int> direction;

	void show(int count) {
		for (int i = 0; i < count; i++)
			add();
	}
	
	void add() {
		int type = rand() % 4;
		this->type.push_back(type);

		int dir = rand() % 2 ? 1 : -1;
		this->direction.push_back(dir);
		
		int x = ((rand() % (range / 2)) + 5)*(-dir);
		this->X.push_back(x);
		
		int y = rand() % 10+1;
		this->Y.push_back(y);
		
		this->Z.push_back(0);
		
		this->angle.push_back(0);
		float step = ((float)((rand() % 100)) / 100 + 0.01)*(float)dir;
		this->angle_step.push_back(step);
		

		this->count++;
	}

	void remove() {
		if (this->count > 0)
		{
			this->type.pop_back();
			this->X.pop_back();
			this->Y.pop_back();
			this->Z.pop_back();
			this->direction.pop_back();
			this->angle_step.pop_back();
			this->angle.pop_back();
			count--;
		}	
	}
};