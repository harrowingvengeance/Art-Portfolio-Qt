//
// Created by Lea on 6/4/2025.
//

#ifndef OPERATIONSTACK_H
#define OPERATIONSTACK_H

#include "../operations/operation.h"
#include <vector>

using std::vector;

class operationStack {
    vector<Operation*> operations;
    int nextIndex = 0;
public:
    operationStack();
    ~operationStack();

    void recordOperation(Operation* newOperation);
    Operation* getRedoOperation();
    Operation* getUndoOperation();
};


#endif //OPERATIONSTACK_H
