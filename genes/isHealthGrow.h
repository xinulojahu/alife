#ifndef GENEISHEALTHGROW_H
#define GENEISHEALTHGROW_H

#include "abstract.h"

class alGeneIsHealthGrow : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
