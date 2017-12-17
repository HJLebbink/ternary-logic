#pragma once

#include "ternary_logic.cpp"


// main for testing
int main()
{
	ternarylogic::test::tests();
	ternarylogic::test::create_method_reduced_ternary();
	printf("\nPress RETURN to finish:");
	getchar();
	return 0;
}
