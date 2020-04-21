// Virtual_table.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>

class ActionArea {
	size_t x, y, w, h;
public:
	virtual void print() { printf("Default\n"); };
};

class Button: public ActionArea {
public:
	virtual void print() { printf("Button\n"); }
};

class Canvas : public ActionArea {
public:
	virtual void print() { printf("Canvas\n"); }
};

void call(ActionArea* base) {
	base->print();
}

int main()
{
	Button but = {};
	Canvas cas = {};
	
	printf("------Class content------\n");
	for (size_t i = 0; i < 5; i++) {
		printf("But num %d: %x\n", i, *(((size_t*)&but) + i));
	}
	putchar('\n');
	for (size_t i = 0; i < 5; i++) {
		printf("Cas num %d: %x\n", i, *((size_t*)&cas + i));
	}
	printf("------Class content------\n");

	std::swap(*(size_t*)&but, *(size_t*)&cas);
	printf("\nThen call 'but' and should be write 'Button'\nBut virtual table swap with Canvas\n");
	call(&but);

	printf("'but' usual print: ");
	but.print();
    return 0;
}

