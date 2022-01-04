#include "stepRelDir.h"
#include "../abot.h"

bool alGeneStepRelDir::doGene(alBot* bot) {
    bot->incCmdAdr(bot->get_command(
        bot->get_adr() + bot->move((bot->get_dir() + bot->get_param()) % 8)));
    return true;
}

