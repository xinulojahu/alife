#include "stepAbsDir.h"
#include "../abot.h"

bool alGeneStepAbsDir::doGene(alBot* bot) {
    bot->incCmdAdr(
        bot->get_command(bot->get_adr() + bot->move(bot->get_param() % 8)));
    return true;
}

