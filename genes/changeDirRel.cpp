#include "changeDirRel.h"
#include "../abot.h"

bool alGeneChangeDirRel::doGene(alBot* bot) {
    bot->set_dir((bot->get_dir() + bot->get_param()) % 8);
    bot->incCmdAdr(2);
    return false;
}

