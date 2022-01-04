#ifndef GENEFULLAROUND_H
#define GENEFULLAROUND_H

#include "abstract.h"

class alGeneFullAround : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
