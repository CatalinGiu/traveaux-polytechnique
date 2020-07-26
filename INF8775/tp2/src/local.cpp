#include "local.h"
#include "glouton.h"
#include <iostream>
#include <iterator>
#include <algorithm>

#define SEUIL_VOISIN 2
#define SEUIL_TEMPS 600 // 10 minutes

using namespace std;

int main(int argc, char* argv[]) {
    string filepath;
    bool print_array = false;
    bool print_time = false;

    for (int i = 1; i < argc; i++)
    {
        string arg(argv[i]);
        if (arg == "-p")
            print_array = true;
        else if (arg == "-t")
            print_time = true;
        else
            filepath = arg;
    }

    int size, capacity;
    emplacement* emplacements = get_emplacements_from_file(filepath, &size, &capacity);

	auto start = chrono::steady_clock::now();

    set<int> set_glouton_results = setup_and_run_glouton(emplacements, size, capacity);

    // transformer glouton en vecteur car on a besoin de pouvoir acceder les elements par indice
	vector<emplacement> vec_glouton = vector<emplacement>();
    for(int i : set_glouton_results){
    	vec_glouton.push_back(emplacements[i]);
    }
	vector<emplacement> vec_emplacements(emplacements, emplacements + size);

	vector<emplacement> vec_solution = local_optimization(vec_emplacements, vec_glouton);
	auto end = chrono::steady_clock::now();

	// relique du passe, notre fonction print_solution prend en entree un set avec les indice d'un tableau...
	set<int> solution = set<int>();
	for(emplacement e : vec_solution){
		solution.insert(e.i - 1);
	}

    if (print_array)
        print_solution(solution, emplacements, EXTENDED_PRINT);
    if(PRINT_REVENU)
    	print_revenu(solution, emplacements);
    if (print_time)
        printTime(start, end);

	delete[] emplacements;
}

vector<vector<emplacement>> compute_compbination(vector<emplacement> arr, vector<emplacement> &curr_solution, int r)
{
	// A temporary array to store all combination one by one
	vector<vector<emplacement>> ret = vector<vector<emplacement>>();
	vector<emplacement>::iterator it;
	for(emplacement e: curr_solution){
		it = find_if(arr.begin(), arr.end(),
				[&e](emplacement const& item)
		{
			return item.i == e.i;
		});
		arr.erase(it);
	}
	vector<emplacement> data = vector<emplacement>(r);

	// Print all combination using temprary array 'data[]'
	combinationUtil(arr, r, 0, data, 0, ret);
	return ret;
}

// The following function is taken from https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
// some modifications were brought to it to allow us to send vectors as inputs
/* arr[]  ---> Input Array
   n      ---> Size of input array
   r      ---> Size of a combination to be printed
   index  ---> Current index in data[]
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     */
void combinationUtil(vector<emplacement> arr,int r,int index,vector<emplacement> data, int i, vector<vector<emplacement>> &ret)
{
	// Current cobination is ready, print it
	if (index == r)
	{
		vector<emplacement> v = vector<emplacement>();
		for (int j=0; j<r; j++)
			v.push_back(data[j]);
		ret.push_back(v);
		return;
	}

	// When no more elements are there to put in data[]
	if (i >= arr.size())
		return;

	// current is included, put next at next location
	data[index] = arr[i];
	combinationUtil(arr, r, index+1, data, i+1, ret);

	// current is excluded, replace it with next (Note that
	// i+1 is passed, but index is not changed)
	combinationUtil(arr, r, index, data, i+1, ret);
}

vector<emplacement> local_optimization(std::vector<emplacement> &emplacements, std::vector<emplacement> solution) {

	vector<emplacement> empty_emplacement = vector<emplacement>();
	int r = SEUIL_VOISIN;
	int curr_rentabilite, curr_quantite;
	bool modified = true;
	vector<vector<emplacement>> comb_emplacements;
	vector<vector<emplacement>> comb_solution;
	vector<emplacement> best_combination;

	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	for (int i = 1; i <= r; i++) {
		while (modified && SEUIL_TEMPS > time_elapsed(start, end)) {
			comb_emplacements = compute_compbination(emplacements, solution, i);
			comb_solution = compute_compbination(solution, empty_emplacement, i);
			modified = false;
			for (vector<emplacement> c_s : comb_solution) {
                curr_rentabilite = get_rentabilite(c_s);
                curr_quantite = get_quantite(c_s);
                best_combination = find_best_combination(comb_emplacements, curr_quantite);
                if (get_rentabilite(best_combination) > curr_rentabilite) {
                    replace_emplacements_in_solution(solution, best_combination, c_s);
                    modified = true;
                }
                if (modified)
                    break;
            }
			end = chrono::steady_clock::now();
		}
		modified = true;
	}

	return solution;
}

int get_rentabilite(std::vector<emplacement> &emplacements) {
	int rentabilite = 0;
	for(emplacement e : emplacements) {
		rentabilite += e.r_i;
	}
	return rentabilite;
}

int get_quantite(std::vector<emplacement> &emplacements) {
	int quantite = 0;
	for(emplacement e : emplacements) {
		quantite += e.q_i;
	}
	return quantite;
}


void replace_emplacements_in_solution(std::vector<emplacement> &solution, std::vector<emplacement> &new_emplacements, std::vector<emplacement> &old_emplacements) {
	vector<emplacement>::iterator it;
	int index = 0;
	for(emplacement o_e : old_emplacements){
		it = find_if(solution.begin(), solution.end(),
					 [&o_e](emplacement const& item)
					 {
						 return item.i == o_e.i;
					 });
		*it = new_emplacements[index++];
	}
}

double time_elapsed(chrono::time_point<std::chrono::steady_clock> start, chrono::time_point<std::chrono::steady_clock> end)
{
	chrono::duration<double> s = end - start;
	return s.count();
}

std::vector<emplacement> find_best_combination(std::vector<std::vector<emplacement>> &combinations, int q_i) {
    int max_ri = 0, curr_ri = 0;
    vector<emplacement> best_combination = vector<emplacement>();
    for(vector<emplacement> c: combinations){
        if(get_quantite(c) <= q_i){
            curr_ri = get_rentabilite(c);
            if(curr_ri > max_ri){
                best_combination = c;
                max_ri = curr_ri;
            }
        }
    }
    return best_combination;
}
