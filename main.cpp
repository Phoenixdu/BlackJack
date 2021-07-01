#include "blackjack.h"
#include "debug.h"

int main(int argc, char *argv[])
{
	Blackjack blackjack;

	if (blackjack.graphics()) {
		
		blackjack.execute();
		return 0;
	}
	else {		
		return 1;
	}
}