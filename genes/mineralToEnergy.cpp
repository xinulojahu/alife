#include "mineralToEnergy.h"
#include "../abot.h"

bool alGeneMineralToEnergy::doGene(alBot* bot) {
    int min = bot->get_mineral() % 100;
    bot->set_mineral(bot->get_mineral() - min);
    bot->set_hp(bot->get_hp() + min * 3);
    bot->goBlue(float(min) / 250.f);
    bot->incCmdAdr(1);
    return true;
}

