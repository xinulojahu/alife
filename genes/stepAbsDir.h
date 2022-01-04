#ifndef GENESTEPABSDIR_H
#define GENESTEPABSDIR_H

#include "abstract.h"

class alGeneStepAbsDir : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
