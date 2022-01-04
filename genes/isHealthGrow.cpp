#include "isHealthGrow.h"
#include "../abot.h"
#include "../world.h"

bool alGeneIsHealthGrow::doGene(alBot* bot) {
    int ret = 2;
    int t = 0;
    if (bot->get_mineral() < 400) {
        t = 1;
    } else {
        t = 2;
    }
    int hpAdd = 15 * bot->get_y() / alWorld::get_p_v_count() - 4 + t;
    if (hpAdd > 3) {
        ret = 1;
    }
    bot->incCmdAdr(bot->get_command(bot->get_adr() + ret));
    return false;
}

