#ifndef GENEPHOTOSYNT_H
#define GENEPHOTOSYNT_H

#include "abstract.h"

class alGenePhotosynthesis : public alGene {
   public:
    virtual bool doGene(alBot* bot) override;
};

#endif
