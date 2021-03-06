#include <composition/graph/vertex.hpp>
#include <composition/util/strings.hpp>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>
#include <sstream>

namespace composition::graph {
using composition::graph::constraint::Constraint;
using composition::graph::constraint::constraint_idx_t;
using composition::util::ltrim;

vertex_idx_t &operator++(vertex_idx_t &i) {
  auto val = static_cast<typename std::underlying_type<vertex_idx_t>::type>(i);
  i = vertex_idx_t(++val);
  return i;
}

const vertex_idx_t operator++(vertex_idx_t &i, int) {
  vertex_idx_t res(i);
  ++i;
  return res;
}

bool operator<(vertex_idx_t lhs, vertex_idx_t rhs) {
  using T = typename std::underlying_type<vertex_idx_t>::type;
  return static_cast<T>(lhs) < static_cast<T>(rhs);
}

std::ostream &operator<<(std::ostream &os, const vertex_type &obj) {
  os << static_cast<std::underlying_type<vertex_type>::type>(obj);
  return os;
}

std::ostream &vertex_t::operator<<(std::ostream &os) noexcept {
  os << this->index << "," << this->name << "," << this->type << ",";
  for (const auto &c : this->constraints) {
    os << c.second->getInfo() << " ";
  }
  return os;
}

bool vertex_t::operator==(const vertex_t &rhs) noexcept { return this->index == rhs.index; }

bool vertex_t::operator!=(const vertex_t &rhs) noexcept { return !(*this == rhs); }

vertex_t::vertex_t(vertex_idx_t index, llvm::Value *value, std::string name, vertex_type type,
                   std::unordered_map<constraint_idx_t, std::shared_ptr<Constraint>> constraints) noexcept
    : index(index), value(value), name(std::move(name)), type(type), constraints(std::move(constraints)) {}

vertex_type llvmToVertexType(const llvm::Value *v) {
  assert(v != nullptr && "Value for llvmToVertexType is nullptr");

  if (llvm::isa<llvm::Instruction>(v)) {
    return vertex_type::INSTRUCTION;
  }
  if (llvm::isa<llvm::BasicBlock>(v)) {
    return vertex_type::BASICBLOCK;
  }
  if (llvm::isa<llvm::Function>(v)) {
    return vertex_type::FUNCTION;
  }
  return vertex_type::VALUE;
}

std::string llvmToVertexName(const llvm::Value *v) {
  std::stringstream name{};
  if (auto *I = llvm::dyn_cast<llvm::Instruction>(v)) {
    if (I->getParent() != nullptr && I->getParent()->getParent() != nullptr) {
      name << I->getFunction()->getName().str() << "_" << static_cast<const void *>(I->getFunction()) << "_";
    }
    name << reinterpret_cast<uintptr_t>(v);
  } else if (auto *F = llvm::dyn_cast<llvm::Function>(v)) {
    // name << F->getName().str() << "_" << reinterpret_cast<uintptr_t>(F);
    name << F->getName().str();
  } else {
    name << v->getName().str();
  }

  auto n = name.str();
  return ltrim(n);
}
} // namespace composition::graph