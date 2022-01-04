#include "eatAbsDir.h"
#include "../abot.h"

bool alGeneEatAbsDir::doGene(alBot* bot) {
    bot->incCmdAdr(
        bot->get_command(bot->get_adr() + bot->eat(bot->get_param() % 8)));
    return true;
}

