// Project Identifier : 9504853406CBAC39EE89AA3AD238AA12CA198043
//  zombiegame.hpp
//  EECS281Project2PartA
//
//  Created by DIVYANGA on 04/10/21.
//

#ifndef zombiegame_h
#define zombiegame_h

#include <stdio.h>
#include <vector>
#include <deque>
#include <queue>
#include <iostream>
#include <cassert>
#include <string>
#include <array>
#include <algorithm>
#include <stack>
#include <getopt.h>
#include "xcode_redirect.hpp"
#include "P2random.h"
using namespace std;


class Game
{
   private:
   
    struct zombie
    {
        string name = "";
        uint32_t distance = 0;
        uint32_t speed = 0;
        uint32_t health = 0;
        uint32_t no_rounds = 0;
    };
    
    class zombie_eta_comparator
    {
        public:
        bool operator()(const zombie* a, const zombie* b) const
        {
            uint32_t ETA_a;
            uint32_t ETA_b;
            ETA_a = a->distance/a->speed ;
            ETA_b = b->distance/b->speed;
            if (ETA_a != ETA_b)
            {
                return ETA_a > ETA_b ;
            }
            else if (a->health != b->health)
            {
                return a->health > b->health;
            }
            else
            {
                return a->name > b->name;
            }
            
        }
    };
    
    class zombie_active_comparator
    {
       public:
        bool operator()(const zombie* a, const zombie* b) const
        {
            if(a->no_rounds != b->no_rounds)
            {
                return a->no_rounds < b->no_rounds;
            }
            else
            {
                return a->name > b->name;
            }
            
        }
    };
    
    class zombie_least_active_comparator
    {
        public:
        bool operator()(const zombie* a, const zombie* b) const
        {
            if(a->no_rounds != b->no_rounds)
            {
                return a->no_rounds > b->no_rounds;
            }
            else
            {
                return a->name > b->name;
            }
            

        }
    };
    
    // zombie master list
    vector <zombie*> masterlist;
    // zombie fighter list
    std::priority_queue<zombie*, vector<zombie*>, zombie_eta_comparator> zombie_alive;
    // finding the median
    std::priority_queue<uint32_t> max_median;
    std::priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t> >min_median;
    // statistics_mode named of dead zombies
    vector<string> zombie_names;
    uint32_t median = 0;
    uint32_t quiver_capacity_refill = 0;
    uint32_t current_round = 0;
    uint32_t round_number = 0; // for reading in values
    uint32_t quiver_capacity = 0; // for reading in values
    uint32_t random_seed = 0; // for reading in values
    uint32_t rand_distance = 0; // for reading in values
    uint32_t rand_speed = 0; // for reading in values
    uint32_t rand_health = 0; // for reading in values
    string name_last_zombie = ""; // for final output
    string name_killer_zombie = ""; // for final output
    bool first_name_or_not = false; // printing final output
    size_t no_zombies_still_active = 0; // printing in the statistics mode
    int num_stats = 0; // printing in the statistics mode
    uint32_t num_stats_final = 0;
    bool verbose_mode = false; // getopt()
    bool stats_mode = false; // getopt()
    bool median_mode = false; // getopt()
    bool player_killed = false; // for final output
    bool zombie_destroyed = false;
    bool more_rounds_to_read = true;
    uint32_t num_stats_first_last = 0;
    uint32_t num_stats_least_most = 0;
    
   public:
 
    void get_options(int agrc, char **argv);
    uint32_t median_calculation(uint32_t time);
    void read_header();
    void main_game_played();
    bool stats_on_or_not();
    void stats_print();
    void final_output();
    void zombie_destroy();
  
};
#endif /* zombiegame_h */
