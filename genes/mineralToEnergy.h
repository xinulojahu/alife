#ifndef GENEMINERALTOENERGY_H
#define GENEMINERALTOENERGY_H

#include "abstract.h"

class alGeneMineralToEnergy : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
