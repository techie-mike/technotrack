// shared_ptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>

#include "shered_ptr.h"

struct var {
	int data_;
	var () { printf ("Construtor var\n"); }
	var (int init):
		data_ (init)
	{ 
		printf ("Consturtor var\n"); 
	}
	~var () { printf ("Destructor var\n"); }

};
int main()
{
	/*std::unique_ptr<var> first_point (new var);
	std::unique_ptr<var> second_point (std::move(first_point));
	*/

	//
	//std::unique_ptr<int> first_point_int (new int[10]);
	//std::unique_ptr<int> second_point_int;
	//printf ("point befor first %p\n", first_point_int);
	//second_point_int = std::move(first_point_int);

	//printf ("point after first %p\n", first_point_int);
	//printf ("point after to second %p\n", second_point_int

	//std::shared_ptr<var> first (new var);
	//std::shared_ptr<var> second;
	//

	//printf ("first cout %d\n", first.use_count());
	//printf ("first get %p\n", first.get ());
	//second = std::move(first);
	////first.reset ();
	////second.reset ();
	//printf ("second after cout %d\n", first.use_count ());
	//printf ("first after get %p\n", first.get ());


	my::shered_ptr<var> temp1 (new var);
	my::shered_ptr<var> temp2;

	temp2 = temp1;
	
	printf ("---------------END---------------\n");
    return 0;
}

