#ifndef GENEGIVEABSDIR_H
#define GENEGIVEABSDIR_H

#include "abstract.h"

class alGeneGiveAbsDir : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
