#include "mutate.h"
#include "../abot.h"

bool alGeneMutate::doGene(alBot* bot) {
    bot->mutate();
    bot->mutate();
    bot->incCmdAdr(1);
    return true;
}

