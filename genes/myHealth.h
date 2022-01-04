#ifndef GENEMYHEALTH_H
#define GENEMYHEALTH_H

#include "abstract.h"

class alGeneMyHealth : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
