#pragma once

#include "pp/fun/IFunction.h"

/**
    Breeding/mating of expressions. See section 4.3 of Karl Sims's SIGGRAPH '91
    paper Artificial Evolution for Computer Graphics.
**/

namespace pp {
    class IFunction;
    class Registry;

    /**
        Breed two expressions. If they are of the same type, inspect their args.
        When a difference is encountered, a sub-expression is randomly chosen.
        The Sims paper shows the following example, in which two parents
        are bred to produce one of four outcomes:

        parent1: (* (abs X) (mod X Y))
        parent2: (* (/ Y X) (* X -.7))

        child1: (* (abs X) (mod X Y))  <-- Same as parent1
        child2: (* (abs X) (* X -.7))  <-- Same as parent2
        child3: (* (/ Y X) (mod X Y))
        child4: (* (/ Y X) (* X -.7))

        If the expressions are not of the same type, return one at random.
    **/
    IFunctionPtr Breed(const IFunctionPtr& parent1, const IFunctionPtr& parent2, const Registry& registry);
}
