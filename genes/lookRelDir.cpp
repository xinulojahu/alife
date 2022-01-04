#include "lookRelDir.h"
#include "../abot.h"

bool alGeneLookRelDir::doGene(alBot* bot) {
    bot->incCmdAdr(bot->get_command(
        bot->get_adr() + bot->look((bot->get_dir() + bot->get_param()) % 8)));
    return false;
}

