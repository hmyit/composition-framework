#ifndef COMPOSITION_FRAMEWORK_PRESERVEDVALUEREGISTRY_HPP
#define COMPOSITION_FRAMEWORK_PRESERVEDVALUEREGISTRY_HPP

#include <llvm/IR/Value.h>
#include <llvm/Support/Debug.h>
#include <llvm/Support/raw_ostream.h>
#include <composition/trace/TraceableValue.hpp>

class PreservedValueRegistry {
public:
	static bool Register(std::string name, llvm::Value *v);

	static void Clear();
protected:
	static TraceableValueState *TraceableValues();;
};

#endif //COMPOSITION_FRAMEWORK_PRESERVEDVALUEREGISTRY_HPP