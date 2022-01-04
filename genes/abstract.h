#ifndef GENEABSTRACT_H
#define GENEABSTRACT_H

class alBot;

class alGene {
   public:
    virtual bool doGene(alBot* bot) = 0;
};

#endif
