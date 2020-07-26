#ifndef EL_TIGRE_SHARED_H
#define EL_TIGRE_SHARED_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>    // std::fill
#include <math.h>
#include "data.h"

#define PRINT_DATA

enum Action { BuyBuyBuy, Hodl, PanicSell };
enum State { Below, Above };

typedef struct {
	int length; // max number of elements in struct
	int tail;   // newest element
	float sum;
	std::vector<float> data;
}moving_average;

moving_average ret_ma;
int state;

float cash_position = 100000;
int n_stonks = 0;
int n_transactions = 0;


moving_average construct_ma(int length) {
	ret_ma.length = length;
	ret_ma.sum = 0;
	ret_ma.tail = 0;

	//initialise array with 0s
	ret_ma.data.resize(length);
	std::fill(ret_ma.data.begin(), ret_ma.data.end(), 0);
	return ret_ma;
}

float add_elem(moving_average* ma, float elem) {
	ma->sum = ma->sum - ma->data[ma->tail] + elem;
	ma->data[ma->tail] = elem;
	ma->tail = ++ma->tail % ma->length;
	return ma->sum / ma->length;
}

int dump_it(float curr_avg_200, float curr_avg_50)
{
	int jim_cramer_move = Hodl;
	if (state == Below && curr_avg_50 > curr_avg_200) {
		jim_cramer_move = BuyBuyBuy;
		state = Above;
	}
	else if (state == Above && curr_avg_50 < curr_avg_200) {
		jim_cramer_move = PanicSell;
		state = Below;
	}
	return jim_cramer_move;
}

void compute_polling_moving_average(float data[]) {
	moving_average ma50 = construct_ma(50);
	moving_average ma200 = construct_ma(200);
	float curr_avg_50, curr_avg_200;
	int action;

	for (int i = 0; i < DATA_SIZE; i++) {

#ifndef PRINT_DATA
		printf("new data = %f \n", data[i]);
		printf("%d ma = %f \n", i, add_elem(&ma50, data[i]));
#else
		curr_avg_50 = add_elem(&ma50, data[i]);
		curr_avg_200 = add_elem(&ma200, data[i]);
		if (i >= 200) {
			if (i == 200)
				state = curr_avg_50 < curr_avg_200 ? Below : Above;
			else {
				action = dump_it(curr_avg_200, curr_avg_50);
				switch (action) {
				case BuyBuyBuy:
					n_stonks = floor(cash_position / data[i]);
					cash_position -= n_stonks * data[i];
					n_transactions++;
					printf("Bought %i @ %f\n", n_stonks, data[i]);
					break;
				case Hodl:
					break;
				case PanicSell:
					printf("Sold %i @ %f\n", n_stonks, data[i]);
					cash_position += n_stonks * data[i];
					n_stonks = 0;
					n_transactions++;
					break;
				}
			}
		}

#endif
	}
}

#endif //EL_TIGRE_SHARED_H