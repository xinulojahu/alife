#include "createBot.h"
#include "../abot.h"

bool alGeneCreateBot::doGene(alBot* bot) {
    bot->burnNew();
    bot->incCmdAdr(1);
    return true;
}

