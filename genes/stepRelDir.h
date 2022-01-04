#ifndef GENESTEPRELDIR_H
#define GENESTEPRELDIR_H

#include "abstract.h"

class alGeneStepRelDir : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
