#include "photosynthesis.h"
#include "../abot.h"
#include "../world.h"

bool alGenePhotosynthesis::doGene(alBot* bot) {
    int t = 0;
    if (bot->get_mineral() < 400) {
        t = 1;
    } else {
        t = 2;
    }

    int hpAdd = 16 * bot->get_y() / alWorld::get_p_v_count() - 6 + t;
    if (hpAdd > 0) {
        bot->set_hp(bot->get_hp() + hpAdd);
        bot->goGreen(float(hpAdd) / 250.f);
    }
    bot->incCmdAdr(1);
    return true;
}

