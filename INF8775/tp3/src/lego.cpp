#include "lego.h"
#include "utility.h"

#include <iostream>
#include <string.h>

#define N_SAMPLES 100

using namespace std;
int main(int argc, char* argv[]) {
	string filepath;
	if (argc > 2) {
		cout << "only argument should be exemplaires/XXX";
		return 1;
	}
	filepath = string(argv[1]);
	int n_pieces, n_models;
	int *inventory, *prices;
	int **models;

	read_data(inventory, prices, models, n_pieces, n_models, filepath);
	for(int i = 0; i < n_pieces; i++) {
		inventory_value += inventory[i] * prices[i];
	}

	double *ratios = new double[n_pieces];
	double *variances = new double[n_models];
    int** parents = new int*[N_SAMPLES];
    for(int i = 0; i < N_SAMPLES; i++)
        parents[i] = new int[n_models];
    int* working_inventory = new int[n_pieces];

    while (true) {
//        local_best_solution = INT32_MAX;
        for (int i = 0; i < n_models; i++) {
            compute_ratios(inventory, models[i], n_pieces, ratios);
            variances[i] = compute_variance(ratios, n_pieces);
        }

        IndexGen index_generator(variances, n_models);

        for (int i = 0; i < N_SAMPLES; i++) {
            memset(parents[i], 0, n_models * sizeof(int));
            copy_array(inventory, working_inventory, n_pieces);

            build_models_from_inventory(working_inventory, n_pieces, models, n_models, index_generator, parents[i]);
            buy_models(working_inventory, n_pieces, models, n_models, parents[i], ratios, variances);
        }
        evolve(parents, models, prices, inventory, n_pieces, n_models, ratios, variances);
    }
	// Cleanup, if ever...
	delete[] parents;
	delete[] working_inventory;
	delete[] variances;
	delete[] ratios;
	delete[] inventory;
	delete[] prices;
	for (int i = 0; i < n_models; i++)
		delete[] models[i];
	delete[] models;

	for (int i = 0; i < N_SAMPLES; i++)
		delete[] parents[i];
	delete[] parents;
	return 0;
}

void compute_ratios(int *inventory, int* model, int size, double *ret_ratio) {
	for (int i = 0; i < size; i++){
		if(model[i] && inventory[i] > 0) {
			ret_ratio[i] = inventory[i] / double(model[i]);
		}else{ // model[i] is null
			ret_ratio[i] = 0;
		}
	}
}

void build_models_from_inventory(int* inventory, int n_pieces, int** models, int n_models, IndexGen& index_generator, int* solution){
    int attempts = 0, max_attempts = n_models;
    int index, i;
    while(max_attempts > attempts++){
        index = index_generator.new_index();
        if(model_fits(inventory, models[index], n_pieces)){
            solution[index]++;
            for(i = 0; i < n_pieces; i++) {
				inventory[i] -= models[index][i];
			}
            attempts = 0;
        }
    }
}

bool model_fits(int *inventory, int *model, int n_pieces) {
    for(int i = 0; i < n_pieces; i++){
        if(0 > (inventory[i] - model[i])){
            return false;
        }
    }
    return true;
}

void copy_array(int* original, int* copy, int size){
	for(int i = 0; i < size; i++){
		copy[i] = original[i];
	}
}

int compute_price(int* inventory, int n_pieces, int* prices){
    int total = 0;
    for(int i = 0; i < n_pieces; i++){
        total += inventory[i] * prices[i];
    }
    return abs(total);
}
void buy_models(int* inventory, int n_pieces, int** models, int n_models, int* solution, double* ratios, double* variances){
	IndexGen index_generator(variances, n_models);
	int index, i;
    bool pieces_remaining = false;

    for (i = 0; i < n_pieces; i++) {
        if(inventory[i] > 0 ){
            pieces_remaining = true;
            break;
        }
    }
    while(pieces_remaining) {
        pieces_remaining = false;

		for (i = 0; i < n_models; i++) {
			compute_ratios(inventory, models[i], n_pieces, ratios);
			variances[i] = compute_variance(ratios, n_pieces);
		}
		index_generator.update_generator(variances);

        index = index_generator.new_index();
        solution[index]++;
        for (i = 0; i < n_pieces; i++) {
            inventory[i] -= models[index][i];
            if(inventory[i] > 0 ){
                pieces_remaining = true;
            }
        }
    }
}

void evolve(int **parents, int **models, int *prices, int* initial_inventory, int n_pieces, int n_models, double* ratios, double* variance) {
    int i;
    int local_best_solution = INT32_MAX;

    int **children = new int *[N_SAMPLES];
    for (i = 0; i < N_SAMPLES; i++) {
        children[i] = new int[n_models];
    }

    int *sample_prices = new int[N_SAMPLES];
    int **tmp;
    int** initialC = children;
    int** initialP = parents;
    int *child_inventory = new int[n_pieces];

    IndexGen index_generator(sample_prices, N_SAMPLES);

    int prob_fittyfitty[2] = {1, 1};
    IndexGen fittyfitty(prob_fittyfitty, 2);
    const int mut_chance = 100;
    int mutate_prob[mut_chance] = {1};
    for( i = 0; i < mut_chance; i++){
        mutate_prob[i] = 1;
    }
    IndexGen mutate_gen(mutate_prob, N_SAMPLES);

    for (i = 0; i < N_SAMPLES; i++) {
        copy_array(initial_inventory, child_inventory, n_pieces);
        sample_prices[i] =
                get_inventory_from_solution(parents[i], child_inventory, n_pieces, models, n_models, prices) -
                inventory_value;
        if (sample_prices[i] < local_best_solution) {
            local_best_solution = sample_prices[i];
        }
    }


    int old_price;
    int attempts = 0;
    while(max_attempts > attempts++) {
        index_generator.update_generator(sample_prices);
        for (i = 0; i < N_SAMPLES; i++) {
            old_price = sample_prices[i];
            do {
                copy_array(initial_inventory, child_inventory, n_pieces);
                breed(parents[index_generator.new_index()], parents[index_generator.new_index()], children[i], n_models, fittyfitty, mutate_gen);
                sample_prices[i] = get_inventory_from_solution(children[i], child_inventory, n_pieces, models, n_models, prices) - inventory_value;
            } while (sample_prices[i] > old_price);
            buy_models(child_inventory, n_pieces, models, n_models, children[i], ratios, variance);
            sample_prices[i] = compute_price(child_inventory, n_pieces, prices);
            if (sample_prices[i] < local_best_solution) {
                local_best_solution = sample_prices[i];
                print_solution(children[i], n_models, sample_prices[i]);
//                cout << sample_prices[i] << endl; // TODO: comment this shit
                attempts = 0;
            }
        }
        tmp = parents;
        parents = children;
        children = tmp;
    }
    children = initialC;
    parents = initialP;
    for (i = 0; i < N_SAMPLES; i++) {
        delete[] children[i];
    }
    delete[] children;
}

void breed(int* parent1, int* parent2, int* child, int n_model, IndexGen& fittyfitty, IndexGen& tchernobylizer){
	for(int i = 0; i < n_model; i++){
		if(fittyfitty.new_index()){
			child[i] = parent1[i];
		} else {
			child[i] = parent2[i];
		}
        if(tchernobylizer.new_index() == 0){
            if(child[i] && fittyfitty.new_index()){
                child[i]--;
            } else {
                child[i]++;
            }
        }

	}

}

int get_inventory_from_solution(int* solution, int* new_inventory, int n_pieces, int** models, int n_models, int* prices){
	int grand_total = 0;
	int model_total = 0;
	for(int i = 0; i < n_models; i++){
		if(solution[i] > 0) {
			model_total = 0;
			for (int j = 0; j < n_pieces; j++) {
				model_total += prices[j] * models[i][j];
				new_inventory[j] -= solution[i] * models[i][j];
			}
			grand_total += model_total * solution[i];
		}
	}
	return grand_total;
}

void print_solution(int* sol, int size, int price){
    if(price < global_best_solution) {
        for (int i = 0; i < size; i++) {
            cout << sol[i] << " ";
        }
        global_best_solution = price;
        cout << endl; // TODO: UNCOMMENT THIS SHIT
    }
}

