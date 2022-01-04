#ifndef GENECREATEBOT_H
#define GENECREATEBOT_H

#include "abstract.h"

class alGeneCreateBot : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
