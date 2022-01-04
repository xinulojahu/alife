#ifndef GENEMUTATE_H
#define GENEMUTATE_H

#include "abstract.h"

class alGeneMutate : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
