#include "giveAbsDir.h"
#include "../abot.h"

bool alGeneGiveAbsDir::doGene(alBot* bot) {
    bot->incCmdAdr(
        bot->get_command(bot->get_adr() + bot->give(bot->get_param()) % 8));
    return false;
}

