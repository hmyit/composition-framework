#include <composition/graph/constraint.hpp>

namespace composition {
Constraint::Constraint(Constraint::ConstraintKind Kind, Constraint::ConstraintType Type, std::string Info)
    : Kind(Kind), Type(Type), Info(Info) {}

Constraint::ConstraintKind Constraint::getKind() const { return Kind; }

Constraint::ConstraintType Constraint::getType() const { return Type; }

std::string Constraint::getInfo() const { return Info; }

Dependency::Dependency(std::string info, llvm::Value *from, llvm::Value *to, bool weak)
    : Constraint(ConstraintKind::CK_DEPENDENCY, ConstraintType::EDGE, info), from(from), to(to), weak(weak) {}

llvm::Value *Dependency::getFrom() const {
  return from;
}

llvm::Value *Dependency::getTo() const {
  return to;
}

bool Dependency::classof(const Constraint *S) {
  return S->getKind() == ConstraintKind::CK_DEPENDENCY;
}

Present::Present(std::string info, llvm::Value *target, bool inverse)
    : Constraint(ConstraintKind::CK_PRESENT, ConstraintType::VERTEX, info), target(target),
      inverse(inverse) {}

llvm::Value *Present::getTarget() const {
  return target;
}

bool Present::isInverse() const {
  return inverse;
}

bool Present::classof(const Constraint *S) {
  return S->getKind() == ConstraintKind::CK_PRESENT;
}

Preserved::Preserved(std::string info, llvm::Value *target, bool inverse)
    : Constraint(ConstraintKind::CK_PRESERVED, ConstraintType::VERTEX, info), target(target),
      inverse(inverse) {}

llvm::Value *Preserved::getTarget() const {
  return target;
}

bool Preserved::isInverse() const {
  return inverse;
}

bool Preserved::classof(const Constraint *S) {
  return S->getKind() == ConstraintKind::CK_PRESERVED;
}

}