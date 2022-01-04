#include "myLifeTime.h"
#include "../abot.h"

bool alGeneMyLifeTime::doGene(alBot* bot) {
    int ret;
    if (bot->get_life_time() < 500) {
        ret = 2;
    } else {
        ret = 3;
    }
    bot->incCmdAdr(bot->get_command(bot->get_adr() + ret));
    return false;
}

