#include "TetrisStructures.h"

std::unique_ptr<Goodie::Matrix> tStructs[TStructCount];

void initTStructures() {
    tStructs[I].reset(new Goodie::Matrix(1, 4, true,
        2, 2, 2, 2));
	
    tStructs[O].reset(new Goodie::Matrix(2, 2, true,
        2, 2,
        2, 2));

    tStructs[T].reset(new Goodie::Matrix(2, 3, true,
        2, 2, 2,
        0, 2, 0));

    tStructs[S].reset(new Goodie::Matrix(2, 3, true,
        0, 2, 2,
        2, 2, 0));

    tStructs[Z].reset(new Goodie::Matrix(2, 3, true,
        2, 2, 0,
        0, 2, 2));

    tStructs[L].reset(new Goodie::Matrix(2, 3, true,
        0, 0, 2,
        2, 2, 2));
	
    tStructs[J].reset(new Goodie::Matrix(2, 3, true,
        2, 0, 0,
        2, 2, 2));
}
