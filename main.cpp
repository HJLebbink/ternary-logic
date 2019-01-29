#pragma once

#include "ternary_logic.cpp"


// main for testing
int main()
{
	printf("\nGoing to run:\n");
	ternarylogic::test::tests();
	printf("\nPress RETURN to finish:");
	static_cast<void>(getchar());
	return 0;
}
