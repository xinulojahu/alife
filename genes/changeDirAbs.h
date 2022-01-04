#ifndef GENECHANGEDIRABS_H
#define GENECHANGEDIRABS_H

#include "abstract.h"

class alGeneChangeDirAbs : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
