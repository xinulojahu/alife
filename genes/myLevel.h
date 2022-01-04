#ifndef GENEMYLEVEL_H
#define GENEMYLEVEL_H

#include "abstract.h"

class alGeneMyLevel : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
