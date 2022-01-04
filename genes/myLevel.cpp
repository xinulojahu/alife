#include "myLevel.h"
#include "../abot.h"
#include "../world.h"

bool alGeneMyLevel::doGene(alBot* bot) {
    int ret;
    if (bot->get_y() < bot->get_param() * alWorld::get_p_v_count() / 64) {
        ret = 2;
    } else {
        ret = 3;
    }
    bot->incCmdAdr(bot->get_command(bot->get_adr() + ret));
    return false;
}

