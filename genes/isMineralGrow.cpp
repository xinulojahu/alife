#include "isMineralGrow.h"
#include "../abot.h"
#include "../world.h"

bool alGeneIsMineralGrow::doGene(alBot* bot) {
    int ret = 2;
    if (bot->get_y() < alWorld::get_p_v_count() / 2) {
        ret = 1;
    }
    bot->incCmdAdr(bot->get_command(bot->get_adr() + ret));
    return false;
}

