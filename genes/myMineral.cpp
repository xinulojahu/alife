#include "myMineral.h"
#include "../abot.h"

bool alGeneMyMineral::doGene(alBot* bot) {
    int ret;
    if (bot->get_mineral() < bot->get_param() * 15) {
        ret = 2;
    } else {
        ret = 3;
    }
    bot->incCmdAdr(bot->get_command(bot->get_adr() + ret));
    return false;
}

