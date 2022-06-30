// Project Identifier : 9504853406CBAC39EE89AA3AD238AA12CA198043
//  zombiegame.cpp
//  EECS281Project2PartA
//
//  Created by DIVYANGA on 04/10/21.
//

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
#include "zombiegame.h"
#include "P2random.h"
#include "xcode_redirect.hpp"

void Game::get_options(int argc, char **argv)
{
    int option_index = 0;
    int choice = 0;
    opterr = false;
    option long_options[] = {
        {"verbose", no_argument, nullptr, 'v'},
        {"statistics", required_argument, nullptr , 's'},
        {"median", no_argument, nullptr, 'm'},
        {"help", no_argument, nullptr, 'h'},
        { nullptr, 0,                 nullptr, '\0' }
    };
    while ((choice = getopt_long(argc, argv, "vs:mh", long_options, &option_index)) != -1)
    {
        switch (choice)
        {
            case 'v':
                verbose_mode = true;
                break;
                
            case 's':
                stats_mode = true;
                num_stats = atoi(optarg);
                break;
                
            case 'm':
                median_mode = true;
                break;
           
            case 'h':
               std::cout << "This program plays games with zombies and tries to save the\n"
                         << "the player from zombies. The game ends if the player is killed\n"
                         << "or if all zombies have been killes(no more to read from file)\n";
               exit(0);
         }
     }
}

void Game::read_header()
{
    string header1 = "";
    string header = "";
    string quiver = "";
    string seed = "";
    string rand_m_distance = "";
    string rand_m_speed = "";
    string rand_m_health = "";
    
    getline(cin,header);
    cin >> quiver >> quiver_capacity;
    cin >> seed >> random_seed;
    cin >> rand_m_distance >> rand_distance;
    cin >> rand_m_speed >> rand_speed;
    cin >> rand_m_health >> rand_health;
    cin >> header1;
    P2random::initialize(random_seed, rand_distance, rand_speed, rand_health);
}

uint32_t Game::median_calculation(uint32_t a)
{
    if (max_median.size() > min_median.size())
    {
        if (a < median)
        {
            min_median.push(max_median.top());
            max_median.pop();
            max_median.push(a);
        }
        else
        {
            min_median.push(a);
        }
        median = (max_median.top() + min_median.top())/2;
    }
    else if (max_median.size() < min_median.size())
    {
        if (a > median)
        {
            max_median.push(min_median.top());
            min_median.pop();
            min_median.push(a);
        }
        else
        {
            max_median.push(a);
        }
        median = (max_median.top() + min_median.top())/2;
    }
    else
    {
        if (a > median)
        {
            min_median.push(a);
            median = min_median.top();
        }
        else
        {
            max_median.push(a);
            median = max_median.top();
        }
    }
    return  median;
}


void Game::main_game_played()
{
    string header_reader_2 = "";
    uint32_t random_zombies_num = 0;
    uint32_t named_zombies_num = 0;
    string round_st = "";
    string no_random_zombies= "";
    string no_named_zombies = "";
    string distance_named = "";
    string speed_named = "";
    string health_named = "";
    read_header();
    current_round = 1;
    cin >> round_st >> round_number;

    while (!zombie_alive.empty() || more_rounds_to_read)
    {
        if (verbose_mode == true)
        {
            cout << "Round: " << current_round << '\n';
        }
      
        quiver_capacity_refill = quiver_capacity;

        for (size_t i = 0; i < masterlist.size(); ++i)
        {
            if(masterlist[i]->health != 0)
            {
                if (masterlist[i]->distance > masterlist[i]->speed)
                {
                    masterlist[i]->distance = masterlist[i]->distance - masterlist[i]->speed;
                }
                else
                {
                    masterlist[i]->distance = 0;
                    if (first_name_or_not == false)
                    {
                        name_killer_zombie = masterlist[i]->name;
                        first_name_or_not = true;
                        player_killed = true;
                    }
                }
                ++(masterlist[i]->no_rounds);
                if (verbose_mode == true)
                {
                    cout << "Moved: " << masterlist[i]->name << " (distance: " << masterlist[i]->distance <<", speed: " << masterlist[i]->speed << ", health: " << masterlist[i]->health << ")" << '\n';
                }
            }
        }
        if (player_killed == true)
        {
            return;
        }
        if (current_round == round_number)
        {
            cin >> no_random_zombies >> random_zombies_num;
            cin >> no_named_zombies >> named_zombies_num;
            for(uint32_t i = 0; i < random_zombies_num; ++i)
             {
                zombie *p = new zombie;
                std::string name_1 = P2random::getNextZombieName();
                uint32_t distance_1 = P2random::getNextZombieDistance();
                uint32_t speed_1 = P2random::getNextZombieSpeed();
                uint32_t health_1 = P2random::getNextZombieHealth();
                p->name = name_1;
                p->distance = distance_1;
                p->speed = speed_1;
                p->health = health_1;
                p->no_rounds = 1;
                masterlist.push_back(p);
                zombie_alive.push(p);
                if (verbose_mode == true)
                 {
                     cout << "Created: " << p->name << " (distance: " << p->distance <<", speed: " << p->speed << ", health: " << p->health << ")" << '\n';
                 }
             }
            for (uint32_t i = 0; i < named_zombies_num; ++i)
            {
                zombie *p = new zombie;
                cin >> p->name >> distance_named >> p->distance >> speed_named >> p->speed >> health_named >> p->health;
                p->no_rounds = 1;
                masterlist.push_back(p);
                zombie_alive.push(p);
                if (verbose_mode == true)
                {
                    cout << "Created: " << p->name << " (distance: " << p->distance <<", speed: " << p->speed << ", health: " << p->health << ")" << '\n';
                }
            }
            if (cin >> header_reader_2)
            {
                cin >> round_st >> round_number;
            }
            else
            {
                more_rounds_to_read = false;
            }
        }
        
        while (quiver_capacity_refill != 0 && !zombie_alive.empty())
        {
             if (quiver_capacity_refill >= zombie_alive.top()->health)
             {
                 zombie_destroyed = true;
                 quiver_capacity_refill = quiver_capacity_refill - zombie_alive.top()->health;
                 zombie_alive.top()->health = 0;
                 if (verbose_mode == true)
                 {
                    cout << "Destroyed: " << zombie_alive.top()->name << " (distance: " << zombie_alive.top()->distance <<", speed: " << zombie_alive.top()->speed << ", health: " << zombie_alive.top()->health << ")" << '\n';
                 }
                 if (median_mode == true)
                 {
                    median_calculation(zombie_alive.top()->no_rounds);
                 }
                 if (stats_mode == true)
                 {
                    zombie_names.push_back(zombie_alive.top()->name);
                  }
                  name_last_zombie = zombie_alive.top()->name;
                  zombie_alive.pop();
              }
              else
              {
                 zombie_alive.top()->health = zombie_alive.top()->health - quiver_capacity_refill;
                 quiver_capacity_refill = 0;
              }
         }
          
       if (median_mode == true && zombie_destroyed == true)
        {
            cout << "At the end of round " << current_round  << ", the median zombie lifetime is " << median << '\n';
        }
        ++current_round;
    }
}


bool Game::stats_on_or_not()
{
    if(stats_mode == true)
    {
        return true;
    }
    return false;
}

void Game::stats_print()
{
    num_stats_final = static_cast<uint32_t>(num_stats);
    num_stats_first_last = num_stats_final;
    num_stats_least_most = num_stats_final;
    if (zombie_names.size() < num_stats_first_last)
    {
        num_stats_first_last = static_cast<uint32_t>(zombie_names.size());
    }
    if (masterlist.size() < num_stats_least_most)
    {
        num_stats_least_most = static_cast<uint32_t>(masterlist.size());
    }
    no_zombies_still_active = masterlist.size() - zombie_names.size();
    std::priority_queue<zombie*, vector<zombie*>, zombie_active_comparator> active_names (masterlist.begin(), masterlist.end(),zombie_active_comparator());
    std::priority_queue<zombie*, vector<zombie*>, zombie_least_active_comparator> least_names (masterlist.begin(), masterlist.end(), zombie_least_active_comparator());
    
    std::cout << "Zombies still active: " << no_zombies_still_active << '\n';
    std::cout << "First zombies killed:" << '\n';
    for (uint32_t i = 0 ; i < num_stats_first_last; ++i)
    {
        std::cout << zombie_names[i] << " " << (i+1) << '\n';
    }
    std::cout << "Last zombies killed:" << '\n';
    size_t zombie_last_size = zombie_names.size();
    for (uint32_t i = num_stats_first_last ; i > 0; --i)
    {
        std::cout << zombie_names[zombie_last_size - 1] << " " << i << '\n';
        --(zombie_last_size);
    }
    std::cout << "Most active zombies:" << '\n';
    for(uint32_t i = 0; i < num_stats_least_most; ++i)
    {
        std::cout << active_names.top()->name << " " << active_names.top()->no_rounds << '\n' ;
        active_names.pop();
    }
    std::cout << "Least active zombies:" << '\n';
    for(uint32_t i = 0; i < num_stats_least_most; ++i)
    {
        std::cout << least_names.top()->name << " " << least_names.top()->no_rounds << '\n' ;
        least_names.pop();
    }
}

void Game::final_output()
{
    if (player_killed == true)
    {
        std::cout << "DEFEAT IN ROUND " << current_round << "! " << name_killer_zombie << " ate your brains!" << '\n';
    }
    else 
    {
        std::cout << "VICTORY IN ROUND " << (current_round - 1) << "! " << name_last_zombie << " was the last zombie." << '\n';
    }
}

void Game::zombie_destroy()
{
    for (size_t i = 0; i < masterlist.size(); ++i)
    {
        delete masterlist[i];
    }
}
