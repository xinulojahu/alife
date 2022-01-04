#include "lookAbsDir.h"
#include "../abot.h"

bool alGeneLookAbsDir::doGene(alBot* bot) {
    bot->incCmdAdr(
        bot->get_command(bot->get_adr() + bot->look(bot->get_param() % 8)));
    return false;
}

