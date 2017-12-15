/*
 * =====================================================================================
 *
 *       Filename:  nsga_crossover.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/22/14 10:38:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _LEARNING_H_
#define _LEARNING_H_

int Learning_layer(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        double gen_time, int num_testcase);

int Learning_second(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        double gen_time, int num_testcase);

int Learning_weight(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        double gen_time, int num_testcase);

int Learning_bandit(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        float* learn_layer, double gen_time, int num_testcase, int g);

int Learning_epsilon_big(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        float* learn_layer, double gen_time, int num_testcase, int g);

int Learning_epsilon_small(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        float* learn_layer, double gen_time, int num_testcase, int g);

#endif 

