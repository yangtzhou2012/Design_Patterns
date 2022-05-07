#include <iostream>
#include "Vector.h"
#include "List.h"

int main()
{
	LinearStruct<int> *table[2] = {NULL};

	table[0] = new Vector<int>;
	table[1] = new List<int>;

	for (int i = 0; i < 2; i++) {
		table[i]->PushBack(1);
		table[i]->PushBack(5);
		table[i]->PushBack(8);
		table[i]->PushFront(11);
	}

	for (int i = 0; i < 2; i++) {
		LinearIterator<int> *it = table[i]->CreateIterator();
		for (it->First(); !it->IsDone(); it->Next())
			std::cout << *(it->CurrentItem()) << " ";
		std::cout << "\n";
		delete it;
	}

	for (int i = 0; i < 2; i++)
		delete table[i];

	return 0;
}
