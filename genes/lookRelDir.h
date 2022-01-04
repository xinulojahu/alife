#ifndef GENELOOKRELDIR_H
#define GENELOOKRELDIR_H

#include "abstract.h"

class alGeneLookRelDir : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
