#ifndef GENEMYLIFETIME_H
#define GENEMYLIFETIME_H

#include "abstract.h"

class alGeneMyLifeTime : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
