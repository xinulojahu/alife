#ifndef GENEEATABSDIR_H
#define GENEEATABSDIR_H

#include "abstract.h"

class alGeneEatAbsDir : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
