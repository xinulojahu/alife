#ifndef GENELOOKABSDIR_H
#define GENELOOKABSDIR_H

#include "abstract.h"

class alGeneLookAbsDir : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
