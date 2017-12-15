/*
 * =====================================================================================
 *
 *       Filename:  nsga_config.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/13/14 09:53:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

//#include "nsga_config.h"
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;


extern const string prog_name = "flex";
//"space" "bash" "v8" "flex" "commons-io" "commons-lang" "checkstyle" "joda-time"

extern const string input_path = "../total_cover/";
//extern const string input_path = "../../" + prog_name + "/";
extern const string cover_file = prog_name + ".cov";
//extern const string cover_file = "_" + prog_name + "_subSuite.out";
extern const string eet_file = prog_name + ".time";
//extern const string eet_file = "_" + prog_name + "_time.out";
extern const string output_path = "../../learn_eps/";

extern void Init_sequence(int *temp_sequence, int gen_num)
{
    for (int i = 0; i < gen_num; i++)
    {
        temp_sequence[i] = i;
    }
    return;
}

extern void Init_sequence_binary(int *temp_sequence, int gen_num, int loop)
{
    srand((unsigned int)time(0) * loop);
    for (int i = 0; i < gen_num; i++)
    {
        int temp_rand = rand();
        //temp_sequence[i] = temp_rand % 2;
        int num = temp_rand % 10;
        if (num < 2) 
        {
            temp_sequence[i] = 1;
        }
        else
            temp_sequence[i] = 0;
    }
    return;
}


extern void Shuffle(int *temp_sequence, int gen_num, unsigned int loop_count)
{
    srand((unsigned int)time(0) * loop_count);
    for (int i = gen_num - 1; i > 0; i--)
    {
        int rand_num = rand()%i;
        int temp = temp_sequence[i];
        temp_sequence[i] = temp_sequence[rand_num];
        temp_sequence[rand_num] = temp;
    }

    return;
}


extern int Check(bool* max_cover, bool* mark_line, int code_line)
{
    int finish = 1;

    for (int i = 0; i < code_line; i++)
    {
        if (max_cover[i] == 0) continue;
        else
        {
            if (mark_line[i] == 0)
            {
                finish = 0;
                break;
            }
        }
    }

    return finish;
}
