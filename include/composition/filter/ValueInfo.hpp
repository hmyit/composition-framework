#ifndef COMPOSITION_FRAMEWORK_VALUE_INFO_HPP
#define COMPOSITION_FRAMEWORK_VALUE_INFO_HPP

#include <unordered_set>
#include <llvm/IR/Function.h>
#include <composition/filter/FilterInfo.hpp>

namespace composition {
	class ValueInfo : public FilterInfo<llvm::Value *> {
	};
}

#endif //COMPOSITION_FRAMEWORK_VALUE_INFO_HPP