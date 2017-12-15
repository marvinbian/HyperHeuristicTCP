/*
 * =====================================================================================
 *
 *       Filename:  learning.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/03/15 12:25:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "nsga_config.h"
#include "stdlib.h"
#include "eliter_selection.h"
#include <iostream>
#include <fstream>

using namespace std;


int Learning_layer(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        double gen_time, int num_testcase)
{
    for (int i = 0; i < SWARMSIZE; i++)
    {
        sw_cp->apsc[i + SWARMSIZE] = sw_pt->apsc[i];
        sw_cp->exetime[i + SWARMSIZE] = sw_pt->exetime[i];
        sw_cp->distance[i + SWARMSIZE] = sw_pt->distance[i];

        sw_cp->newgen[i] = 0;
        sw_cp->newgen[i + SWARMSIZE] = 1;
    }

    int newrange = Eliter_selection(sw_cp, num_testcase);

    int g_count = 0;
    int m_value = sw_cp->batch[SWARMSIZE - 1];
    
    //cout << "batch: " << m_value << endl;

    for (int i = 0; i < SWARMSIZE; i++)
    {
        if (sw_cp->newgen[i] == 1)
        {
            g_count += m_value - sw_cp->batch[i];
        }
    }

    // Update the new result
    int strategy = change_alg * CRO_NUM + change_cro;
    /*
    int g_count = 0;
    //int m_value = sw_pt->batch[SWARMSIZE - 1];
    for (int i = 0; i < sw_pt->range; i++)
    {
        if (sw_pt->newgen[i] == 1)
        {
            //g_count += m_value - sw_pt->batch[i];
            g_count += 1;
        }
    }
    */

    //cout << sw_pt->range << "  " << g_count << endl;

    //learn_val[strategy] = g_count; //original one 
    learn_val[strategy] = (learn_val[strategy] + g_count) / 2; 
    //learn_val[strategy] = g_count * 100 / sw_pt->range; 
    //learn_time[strategy] += 1;

    // Get the next best strategy
    //int max = (int)(learn_val[STR - 1]); // / learn_time[0];
    //int num = STR - 1;
    int max = (int)(learn_val[0]);
    int num = 0;
    //for (int i = STR - 2; i >= 0; i--) 
    for (int i = 1; i < STR; i++) 
    {
        //if (learn_time[i] == 0) continue;

        int temp = (int)(learn_val[i]);
        //int temp = (int)(learn_val[i]);// * 100 / learn_time[i];
        if (temp >= max) 
        {
            max = temp;
            num = i;
        }
    }

    cout << "------------------" << endl;
    cout << "first * " << num << " *" << endl;
    if (learn_val[num] == 1 || learn_val[num] == 0)
    {
        num = (strategy + 1) % STR;
    }
    cout << "check * " << num << " *" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < STR; i++)
    {
        cout << "(" << i << ") ";
        cout << "  " << learn_val[i];
        if (i == num) cout << "  <";
        cout << endl;
    }
    
    //getchar();

    return num;
}


int Learning_second(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        double gen_time, int num_testcase)
{
    for (int i = 0; i < SWARMSIZE; i++)
    {
        sw_cp->apsc[i + SWARMSIZE] = sw_pt->apsc[i];
        sw_cp->exetime[i + SWARMSIZE] = sw_pt->exetime[i];
        sw_cp->distance[i + SWARMSIZE] = sw_pt->distance[i];

        sw_cp->newgen[i] = 0;
        sw_cp->newgen[i + SWARMSIZE] = 1;
    }

    int newrange = Eliter_selection(sw_cp, num_testcase);

    int g_count = 0;
    int m_value = sw_cp->batch[SWARMSIZE - 1];
    
    //cout << "batch: " << m_value << endl;

    for (int i = 0; i < SWARMSIZE; i++)
    {
        if (sw_cp->newgen[i] == 1)
        {
            g_count += m_value - sw_cp->batch[i];
        }
    }

    // Update the new result
    int strategy = change_alg * CRO_NUM + change_cro;
    /*
    int g_count = 0;
    //int m_value = sw_pt->batch[SWARMSIZE - 1];
    for (int i = 0; i < sw_pt->range; i++)
    {
        if (sw_pt->newgen[i] == 1)
        {
            //g_count += m_value - sw_pt->batch[i];
            g_count += 1;
        }
    }
    */

    //cout << sw_pt->range << "  " << g_count << endl;

    //learn_val[strategy] = g_count; //original one 
    learn_val[strategy] = (learn_val[strategy] + g_count) / 2; 
    //learn_val[strategy] = g_count * 100 / sw_pt->range; 
    //learn_time[strategy] += 1;

    // Get the next best strategy
    //int max = (int)(learn_val[STR - 1]); // / learn_time[0];
    //int num = STR - 1;
    int temp_max = 0;
    int temp_num = 0;
    for (int i = 0; i < STR; i++) 
    {
        int temp = (int)(learn_val[i]);
        if (temp >= temp_max) 
        {
            temp_max = temp;
            temp_num = i;
        }
    }
    int max = 0;
    int num = 0;
    for (int i = 0; i < STR; i++) 
    {
        if (i == temp_num)
            continue;

        int temp = (int)(learn_val[i]);
        if (temp >= max) 
        {
            max = temp;
            num = i;
        }
    }

    cout << "------------------" << endl;
    cout << "first * " << num << " *" << endl;
    if (learn_val[num] == 1 || learn_val[num] == 0)
    {
        num = (strategy + 1) % STR;
    }
    cout << "check * " << num << " *" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < STR; i++)
    {
        cout << "(" << i << ") ";
        cout << "  " << learn_val[i];
        if (i == num) cout << "  <";
        cout << endl;
    }
    
    //getchar();

    return num;
}




int Learning_weight(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        double gen_time, int num_testcase)
{
    for (int i = 0; i < SWARMSIZE; i++)
    {
        sw_cp->apsc[i + SWARMSIZE] = sw_pt->apsc[i];
        sw_cp->exetime[i + SWARMSIZE] = sw_pt->exetime[i];
        sw_cp->distance[i + SWARMSIZE] = sw_pt->distance[i];

        sw_cp->newgen[i] = 0;
        sw_cp->newgen[i + SWARMSIZE] = 1;
    }

    float avg_apsc = 0.0f;
    float avg_eet = 0.0f;
    float avg_distance =0.0f;

    float max_apsc = 0.0f;
    float min_eet = 1000000.0f;
    float max_distance = 0.0f;

    for (int i = 0; i < SWARMSIZE * 2; i++)
    {
        avg_apsc += sw_cp->apsc[i];
        avg_eet  += sw_cp->exetime[i];
        avg_distance += sw_cp->distance[i];

        if (sw_pt->apsc[i] > max_apsc)
            max_apsc = sw_cp->apsc[i];
        if (sw_pt->exetime[i] < min_eet)
            min_eet = sw_cp->exetime[i];
        if (sw_pt->distance[i] > max_distance)
            max_distance = sw_cp->distance[i];
    }

    avg_apsc = avg_apsc / SWARMSIZE;
    avg_eet = avg_eet / SWARMSIZE;
    avg_distance = avg_distance / SWARMSIZE;
    
    float finalres = 0.0;
    float finalapsc = 0.0;
    float finaleet = 0.0;
    float finaldistance = 0.0;
    for (int i = SWARMSIZE; i < SWARMSIZE * 2; i++)
    {
        finalapsc += abs(sw_cp->apsc[i] - avg_apsc) / (max_apsc - avg_apsc); 
        finaleet += abs(sw_cp->exetime[i] - avg_eet) / (avg_eet - min_eet); 
        finalapsc += abs(sw_cp->distance[i] - avg_distance) / (max_distance - avg_distance); 
    }
    
    finalres = 0.4 * finalapsc + 0.4 * finaleet + 0.2 * finaldistance;


    // Update the new result
    int strategy = change_alg * CRO_NUM + change_cro;
    /*
    int g_count = 0;
    //int m_value = sw_pt->batch[SWARMSIZE - 1];
    for (int i = 0; i < sw_pt->range; i++)
    {
        if (sw_pt->newgen[i] == 1)
        {
            //g_count += m_value - sw_pt->batch[i];
            g_count += 1;
        }
    }
    */

    //cout << sw_pt->range << "  " << g_count << endl;

    //learn_val[strategy] = g_count; 
    learn_val[strategy] = finalres; 
    //learn_val[strategy] = g_count * 100 / sw_pt->range; 
    //learn_time[strategy] += 1;

    // Get the next best strategy
    //int max = (int)(learn_val[STR - 1]); // / learn_time[0];
    //int num = STR - 1;
    int max = (int)(learn_val[0]);
    int num = 0;
    //for (int i = STR - 2; i >= 0; i--) 
    for (int i = 1; i < STR; i++) 
    {
        //if (learn_time[i] == 0) continue;

        int temp = (int)(learn_val[i]);
        //int temp = (int)(learn_val[i]);// * 100 / learn_time[i];
        if (temp >= max) 
        {
            max = temp;
            num = i;
        }
    }
    cout << "------------------" << endl;
    cout << "first * " << num << " *" << endl;
    if (learn_val[num] == 1 || learn_val[num] == 0)
    {
        num = (strategy + 1) % STR;
    }
    cout << "check * " << num << " *" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < STR; i++)
    {
        cout << "(" << i << ") ";
        cout << "  " << learn_val[i];
        if (i == num) cout << "  <";
        cout << endl;
    }
    
    //getchar();

    return num;
}

int Learning_bandit(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        float* learn_layer, double gen_time, int num_testcase, int g)
{
    for (int i = 0; i < SWARMSIZE; i++)
    {
        sw_cp->apsc[i + SWARMSIZE] = sw_pt->apsc[i];
        sw_cp->exetime[i + SWARMSIZE] = sw_pt->exetime[i];
        sw_cp->distance[i + SWARMSIZE] = sw_pt->distance[i];

        sw_cp->newgen[i] = 0;
        sw_cp->newgen[i + SWARMSIZE] = 1;
    }

    int newrange = Eliter_selection(sw_cp, num_testcase);

    int g_count = 0;
    int m_value = sw_cp->batch[SWARMSIZE - 1];
    

    for (int i = 0; i < SWARMSIZE; i++)
    {
        if (sw_cp->newgen[i] == 1)
        {
            g_count += m_value - sw_cp->batch[i];
        }
    }

    // Update the new result
    int strategy = change_alg * CRO_NUM + change_cro;


    learn_val[strategy] = (learn_val[strategy] + g_count) / 2;
   
    /*  
    if (g < STR) // STR: 0 - 18 generation
    {
        learn_val[strategy]   = g_count; 
        learn_layer[strategy] = g_count; 
    }
    else
    {
        learn_val[strategy] = learn_val[strategy] + 
            0.1 * (g_count - learn_layer[strategy]);
        
        learn_layer[strategy] = (learn_layer[strategy] + g_count) / 2; 
    }
    */ 
    srand((unsigned int)time(0) * g * 11);
    //int learn_rate = rand() % 10;
    int learn_rate = rand() % 100;

    if (learn_rate < 10)
    {
        int rand1 = rand() % STR;
        cout << "random:  " << rand1 << endl;
        return rand1;
    }


    /*
    if (g < 100)
    {
        if (learn_rate < 4)
        {
            int rand1 = rand() % STR;
            cout << "random:  " << rand1 << endl;
            return rand1;
        }
    }
    else if (g > 100)
    {
        if (learn_rate < 2)
        {
            int rand2 = rand() % STR;
            cout << "random:  " << rand2 << endl;
            return rand2;
        }
    }
    */

    int max = (int)(learn_val[0]);
    int num = 0;
    //for (int i = STR - 2; i >= 0; i--) 
    for (int i = 1; i < STR; i++) 
    {
        //if (learn_time[i] == 0) continue;

        int temp = (int)(learn_val[i]);
        //int temp = (int)(learn_val[i]);// * 100 / learn_time[i];
        if (temp >= max) 
        {
            max = temp;
            num = i;
        }
    }

    cout << "------------------" << endl;
    cout << "first * " << num << " *" << endl;
    if (learn_val[num] == 1 || learn_val[num] == 0)
    {
        num = (strategy + 1) % STR;
    }
    cout << "check * " << num << " *" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < STR; i++)
    {
        cout << "(" << i << ") ";
        cout << "  " << learn_val[i];
        if (i == num) cout << "  <";
        cout << endl;
    }
    
    //getchar();

    return num;
}

int Learning_epsilon_small(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        float* learn_layer, double gen_time, int num_testcase, int g)
{
    for (int i = 0; i < SWARMSIZE; i++)
    {
        sw_cp->apsc[i + SWARMSIZE] = sw_pt->apsc[i];
        sw_cp->exetime[i + SWARMSIZE] = sw_pt->exetime[i];
        sw_cp->distance[i + SWARMSIZE] = sw_pt->distance[i];

        sw_cp->newgen[i] = 0;
        sw_cp->newgen[i + SWARMSIZE] = 1;
    }

    int newrange = Eliter_selection(sw_cp, num_testcase);

    int g_count = 0;
    int m_value = sw_cp->batch[SWARMSIZE - 1];
    

    int front_level = 0;
    for (int i = 0; i < SWARMSIZE; i++)
    {
        if (sw_cp->newgen[i] == 1)
        {
            g_count += m_value - sw_cp->batch[i];
        }
    }

    // Update the new result
    int strategy = change_alg * CRO_NUM + change_cro;

    learn_val[strategy] = (learn_val[strategy] + g_count) / 2;
    //learn_val[strategy] += g_count;
    //learn_layer[strategy] += 1;

    float avg_g_count = 0.0f;
    float max_val = 0.0f;
    for (int i = 0; i < STR; i++) 
    {
        //float temp = learn_val[i] / learn_layer[i];
        avg_g_count += learn_val[i];
        //avg_g_count += temp;
        //if (temp > max_val)
        //    max_val = temp;
        if (learn_val[i] > max_val)
            max_val = learn_val[i];
    }
    float total_count = avg_g_count;
    avg_g_count = avg_g_count / STR;

    float stand_div = 0.0f;
    for (int i = 0; i < STR; i++)
    {
        stand_div += pow(learn_val[i] - avg_g_count, 2.0);
        //stand_div += pow((learn_val[i]/learn_layer[i] - avg_g_count), 2.0);
    }
    float sum_div = pow(avg_g_count, 2.0) * (STR - 1) + 
        pow(total_count - avg_g_count, 2.0);
    float rate = 1 - sqrt(stand_div / sum_div);
    
    srand((unsigned int)time(0) * g * 11);
    //int learn_rate = rand() % 10;
    int learn_rate = rand() % 100;

    if (learn_rate < rate * 10)
    {
        int rand1 = rand() % STR;
        //cout << "random:  " << rand1 << endl;
        return rand1;
    }

    int max = 0;
    int num = 0;
    //for (int i = STR - 2; i >= 0; i--) 
    for (int i = 0; i < STR; i++) 
    {
        //if (learn_time[i] == 0) continue;

        //int temp = (int)(learn_val[i] / learn_layer[i]);
        int temp = (int)(learn_val[i]);// * 100 / learn_time[i];
        if (temp >= max) 
        {
            max = temp;
            num = i;
        }
    }

    /*  
    cout << "------------------" << endl;
    cout << "first * " << num << " *" << endl;
    if (learn_val[num] == 1 || learn_val[num] == 0)
    {
        num = (strategy + 1) % STR;
    }
    cout << "check * " << num << " *" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < STR; i++)
    {
        cout << "(" << i << ") ";
        cout << "  " << learn_val[i];
        if (i == num) cout << "  <";
        cout << endl;
    }
    */ 
    //getchar();

    return num;
}

int Learning_epsilon_big(Swarms* sw_pt, Swarms* sw_cp, int change_alg, int change_cro, float* learn_val, 
        float* learn_layer, double gen_time, int num_testcase, int g)
{
    for (int i = 0; i < SWARMSIZE; i++)
    {
        sw_cp->apsc[i + SWARMSIZE] = sw_pt->apsc[i];
        sw_cp->exetime[i + SWARMSIZE] = sw_pt->exetime[i];
        sw_cp->distance[i + SWARMSIZE] = sw_pt->distance[i];

        sw_cp->newgen[i] = 0;
        sw_cp->newgen[i + SWARMSIZE] = 1;
    }

    int newrange = Eliter_selection(sw_cp, num_testcase);

    int g_count = 0;
    int m_value = sw_cp->batch[SWARMSIZE - 1];
    

    int front_level = 0;
    for (int i = 0; i < SWARMSIZE; i++)
    {
        if (sw_cp->newgen[i] == 1)
        {
            g_count += m_value - sw_cp->batch[i];
        }
    }

    // Update the new result
    int strategy = change_alg * CRO_NUM + change_cro;

    //learn_val[strategy] = (learn_val[strategy] + g_count) / 2;
    learn_val[strategy] += g_count;
    learn_layer[strategy] += 1;

    /* 
    if (g < STR) // STR: 0 - 18 generation
    {
        learn_val[strategy]   = g_count; 
        learn_layer[strategy] = g_count; 
    }
    else
    {
        learn_val[strategy] = learn_val[strategy] + 
            0.1 * (g_count - learn_layer[strategy]);
        
        learn_layer[strategy] = (learn_layer[strategy] + g_count) / 2; 
    }
    */ 
    
    float avg_g_count = 0.0f;
    float max_val = 0.0f;
    for (int i = 0; i < STR; i++) 
    {
        float temp = learn_val[i] / learn_layer[i];
        //avg_g_count += learn_val[i];
        avg_g_count += temp;
        //if (learn_val[i] > max_val)
        if (temp > max_val)
            max_val = temp;
            //max_val = learn_val[i];
    }
    float total_count = avg_g_count;
    avg_g_count = avg_g_count / STR;

    float stand_div = 0.0f;
    for (int i = 0; i < STR; i++)
    {
        //stand_div += pow(learn_val[i] - avg_g_count, 2.0);
        stand_div += pow((learn_val[i]/learn_layer[i] - avg_g_count), 2.0);
    }
    float sum_div = pow(avg_g_count, 2.0) * (STR - 1) + 
        pow(total_count - avg_g_count, 2.0);
    float rate = 1 - sqrt(stand_div / sum_div);
    
    srand((unsigned int)time(0) * g * 11);
    //int learn_rate = rand() % 10;
    int learn_rate = rand() % 100;

    if (learn_rate < rate * 100)
    {
        int rand1 = rand() % STR;
        //cout << "random:  " << rand1 << endl;
        return rand1;
    }

    /*  
    srand((unsigned int)time(0) * g * 11);
    int learn_rate = rand() % 10;

    if (g < 100)
    {
        if (learn_rate < 4)
        {
            int rand1 = rand() % STR;
            cout << "random:  " << rand1 << endl;
            return rand1;
        }
    }
    else if (g > 100)
    {
        if (learn_rate < 2)
        {
            int rand2 = rand() % STR;
            cout << "random:  " << rand2 << endl;
            return rand2;
        }
    }
    */

    int max = 0;
    int num = 0;
    //for (int i = STR - 2; i >= 0; i--) 
    for (int i = 0; i < STR; i++) 
    {
        //if (learn_time[i] == 0) continue;

        int temp = (int)(learn_val[i] / learn_layer[i]);
        //int temp = (int)(learn_val[i]);// * 100 / learn_time[i];
        if (temp >= max) 
        {
            max = temp;
            num = i;
        }
    }

    /*  
    cout << "------------------" << endl;
    cout << "first * " << num << " *" << endl;
    if (learn_val[num] == 1 || learn_val[num] == 0)
    {
        num = (strategy + 1) % STR;
    }
    cout << "check * " << num << " *" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < STR; i++)
    {
        cout << "(" << i << ") ";
        cout << "  " << learn_val[i];
        if (i == num) cout << "  <";
        cout << endl;
    }
    */ 
    //getchar();

    return num;
}
