#include "giveRelDir.h"
#include "../abot.h"

bool alGeneGiveRelDir::doGene(alBot* bot) {
    bot->incCmdAdr(bot->get_command(
        bot->get_adr() + bot->give((bot->get_dir() + bot->get_param()) % 8)));
    return false;
}

