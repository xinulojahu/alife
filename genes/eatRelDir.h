#ifndef GENEEATRELDIR_H
#define GENEEATRELDIR_H

#include "abstract.h"

class alGeneEatRelDir : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
