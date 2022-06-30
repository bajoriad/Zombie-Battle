// Project Identifier : 9504853406CBAC39EE89AA3AD238AA12CA198043
//  main.cpp
//  EECS281Project2PartA
//
//  Created by DIVYANGA on 04/10/21.
//

#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <deque>
#include <getopt.h>
#include <stack>
#include "xcode_redirect.hpp"
#include "zombiegame.h"
#include "P2random.h"
using namespace std;

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    bool stat_mode_on = false;
    Game zombie_game_played;
    zombie_game_played.get_options(argc, argv);
    zombie_game_played.main_game_played();
    zombie_game_played.final_output();
    stat_mode_on = zombie_game_played.stats_on_or_not();
    if (stat_mode_on == true)
    {
        zombie_game_played.stats_print();
    }
    zombie_game_played.zombie_destroy();
    return 0;
}
