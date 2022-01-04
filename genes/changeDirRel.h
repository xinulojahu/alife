#ifndef GENECHANGEDIRREL_H
#define GENECHANGEDIRREL_H

#include "abstract.h"

class alGeneChangeDirRel : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
