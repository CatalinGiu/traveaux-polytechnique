#include "ma.h"

int main() 
{
	printf("initial cash position: %f \n", cash_position);

	compute_polling_moving_average(data);
	if (n_stonks > 0) {
		printf("Sold %i @ %f\n", n_stonks, data[DATA_SIZE - 1]);
		cash_position += n_stonks * data[DATA_SIZE - 1];
	}
	
	printf("cash position after %i days and %i transactions: %f \n", DATA_SIZE, n_transactions, cash_position);
	return 0;
}
