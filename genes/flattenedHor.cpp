#include "flattenedHor.h"
#include "../abot.h"

bool alGeneFlattenedHor::doGene(alBot* bot) {
    bot->set_dir(3);
    bot->incCmdAdr(1);
    return false;
}

