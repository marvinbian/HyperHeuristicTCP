/*
 * =====================================================================================
 *
 *       Filename:  domain_judge.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/03/15 17:14:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "nsga_config.h"
#include <iostream>

using namespace std;

int Domain_compare_copy(Swarms *sw_pt, int a, int b)
{
    int a_a = (int)(sw_pt->apsc[a] * 1000000);
    int b_a = (int)(sw_pt->apsc[b] * 1000000);
    int a_t = (int)(sw_pt->exetime[a] * 1000);
    int b_t = (int)(sw_pt->exetime[b] * 1000);

    int apsc_compare;
    int exet_compare;
    
    if (a_a == b_a)
    {
        if (a_t == b_t) return -2;
        else
        {
            if (a_t < b_t) return a;
            else return b;

        }
    }

    if (a_a > b_a) 
        apsc_compare = a; 
    else 
        apsc_compare = b;
    if (a_t < b_t) 
        exet_compare = a;
    else 
        exet_compare = b;

    if (apsc_compare == exet_compare) 
        return apsc_compare;
    else 
        return -1;
}

int Domain_compare_dou(Swarms *sw_pt, int a, int b)
//int Domain_compare(Swarms *sw_pt, int a, int b)
{
    int a_a = (int)(sw_pt->apsc[a] * 1000000);
    int b_a = (int)(sw_pt->apsc[b] * 1000000);
    int a_t = (int)(sw_pt->exetime[a] * 1000);
    int b_t = (int)(sw_pt->exetime[b] * 1000);

    int apsc_compare;
    int exet_compare;
    
    if (a_a == b_a)
    {
        if (a_t == b_t) return -2;
        else
        {
            if (a_t < b_t) return a;
            else return b;

        }
    }

    if (a_a > b_a) 
        apsc_compare = a; 
    else 
        apsc_compare = b;
    if (a_t < b_t) 
        exet_compare = a;
    else 
        exet_compare = b;

    if (apsc_compare == exet_compare) 
        return apsc_compare;
    else 
        return -1;
}


//int Domain_compare_tri(Swarms *sw_pt, int a, int b)
int Domain_compare(Swarms *sw_pt, int a, int b)
{
    int a_a = (int)(sw_pt->apsc[a] * 1000000);
    int b_a = (int)(sw_pt->apsc[b] * 1000000);
    int a_c = 1;
    int b_c = 1;
    int a_t = (int)(sw_pt->exetime[a] * 1000);
    int b_t = (int)(sw_pt->exetime[b] * 1000);
    //int a_c = (int)(sw_pt->apcc[a] * 1000000);
    //int b_c = (int)(sw_pt->apcc[b] * 1000000);

    int apsc_compare;
    int exet_compare;
    int apcc_compare;

    if (a_a == b_a && a_t == b_t && a_c == b_c) return -2;

    int equ[3]; equ[0] = 0; equ[1] = 0; equ[2] = 0;
    
    if (a_a == b_a)  equ[0] = 0;
    else if (a_a > b_a) equ[0] = 1;
    else equ[0] = -1;
    
    if (a_t == b_t)  equ[1] = 0;
    else if (a_t < b_t) equ[1] = 1;
    else equ[1] = -1;
    
    if (a_c == b_c)  equ[2] = 0;
    else if (a_c > b_c) equ[2] = 1;
    else equ[2] = -1;

    bool mark_zero = 0;
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        if ( equ[i] == 0 ) mark_zero = 1;
        sum += equ[i];
    }
    
    //cout << "sum:  " << sum << endl;
    //cout << "        0: " << equ[0] << "  1: " << equ[1] << "  2: " << equ[2] << endl;

    if (mark_zero == 1)
    {
        if (sum == 0) return -1;
        if (sum > 0) return a;
        else return b;
    }
    else
    {
        if (sum == 3) return a;
        if (sum == -3) return b;
        else return -1;
    }

}

int Domain_judge(Swarms *sw_pt, int a, int b)
{
    if (Domain_compare(sw_pt, a, b) < 0)
    {
        return sw_pt->distance[a] > sw_pt->distance[b] ? a : b;
    }
}
