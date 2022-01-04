#include "eatRelDir.h"
#include "../abot.h"

bool alGeneEatRelDir::doGene(alBot* bot) {
    bot->incCmdAdr(bot->get_command(
        bot->get_adr() + bot->eat((bot->get_dir() + bot->get_param()) % 8)));
    return true;
}

