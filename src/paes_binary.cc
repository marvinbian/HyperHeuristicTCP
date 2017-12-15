/*
 * =====================================================================================
 *
 *       Filename:  nsga_ii.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/03/15 15:18:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "nsga_config.h"

#include "cal_fitness_kernel_binary.h"
#include "pso_selection.h"
#include "nsga_crossover.h"
#include "nsga_crossover_binary.h"
#include "nsga_mutation.h"
#include "eliter_selection.h"
#include "check_sequence.h"

#include <iostream>

using namespace std;

int Paes_binary(Swarms *sw_pt, int num_testcase, int code_line, bool* CMatrix, float* TVector, 
        bool* max_cover, int start, int front_0, int *change_cro)
{
    //Taea_selection(sw_pt, num_testcase);
    
    int *temp_ind = NULL;
    temp_ind = (int*) malloc(sizeof(int) * SWARMSIZE * 2);
    
    bool *temp_pos = NULL;
    temp_pos = (bool*) malloc(sizeof(bool) * SWARMSIZE * num_testcase);
    
    //int count = Pso_selection(sw_pt, temp_ind);
    Pso_selection(sw_pt, temp_ind, temp_pos, front_0, num_testcase);
    
    //Pso_crossover_nor(sw_pt, temp_ind, num_testcase, count);
            
    Nsga_crossover_serial_binary(sw_pt, temp_ind, num_testcase);
    //Nsga_crossover_singlepoint_binary(sw_pt, temp_ind, num_testcase); 
    //Nsga_crossover_uniform_binary(sw_pt, temp_ind, temp_pos, num_testcase); 
    //Nsga_copy(sw_pt, num_testcase);
    
    //Check_sequence(sw_pt, num_testcase);
    //cout << "Check" << endl;
    
    free(temp_ind);
    free(temp_pos);
    

    //Nsga_mutation_change_binary(sw_pt, num_testcase);
    Nsga_mutation_reverse_binary(sw_pt, num_testcase);

    Cal_fitness_binary(sw_pt, num_testcase, code_line, CMatrix, TVector, max_cover, start);
    
    int eliter = Eliter_selection_taea(sw_pt, num_testcase);

    return eliter;
}
