//
// Created by Lea on 6/4/2025.
//

#include "operationStack.h"
#include "../exceptions/exception.h"
using std::vector;

operationStack::operationStack() {
    nextIndex = 0;
    operations.clear();
}

operationStack::~operationStack() {
    for (auto operation: operations)
        delete operation;
}

void operationStack::recordOperation(Operation *newOperation) {
    for (int i = operations.size() - 1; i >= nextIndex; i--) {
        delete operations[i];
        operations.pop_back();
    }
    operations.push_back(newOperation);
    nextIndex++;
}

Operation* operationStack::getRedoOperation() {
    if (nextIndex == operations.size())
        throw UndoRedoException("There's no operation to redo!");
    nextIndex++;
    return operations[nextIndex-1];
}

Operation *operationStack::getUndoOperation() {
    if (nextIndex == 0)
        throw UndoRedoException("There's no operation to undo!");
    nextIndex--;
    return operations[nextIndex];
}
