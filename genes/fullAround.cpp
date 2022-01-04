#include "fullAround.h"
#include <cstdlib>
#include "../abot.h"
#include "../world.h"

bool alGeneFullAround::doGene(alBot* bot) {
    int ret = 1;
    for (int i = 0; i < 8; i++) {
        int dx = bot->get_new_x(i);
        int dy = bot->get_new_y(i);
        if ((dy >= 0) && (dy < alWorld::get_p_v_count())) {
            if (alWorld::get_bot(dx, dy) == NULL) {
                ret = 2;
            }
        }
    }
    bot->incCmdAdr(bot->get_command(bot->get_adr() + ret));
    return false;
}

