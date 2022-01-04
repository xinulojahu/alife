#ifndef GENEISMINERALGROW_H
#define GENEISMINERALGROW_H

#include "abstract.h"

class alGeneIsMineralGrow : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
