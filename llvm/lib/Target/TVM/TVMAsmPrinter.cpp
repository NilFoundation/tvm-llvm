//===-- TVMAsmPrinter.cpp - TVM LLVM assembly writer ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the TVM assembly language.
//
//===----------------------------------------------------------------------===//

#include "InstPrinter/TVMInstPrinter.h"
#include "TVM.h"
#include "TVMInstrInfo.h"
#include "TVMMCInstLower.h"
#include "TVMMachineFunctionInfo.h"
#include "TVMTargetMachine.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {
class TVMAsmPrinter : public AsmPrinter {
public:
  TVMAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  StringRef getPassName() const override { return "TVM Assembly Printer"; }

  void printOperand(const MachineInstr *MI, int OpNum, raw_ostream &O,
                    const char *Modifier = nullptr);
  void EmitInstruction(const MachineInstr *MI) override;
  std::string regToString(const MachineOperand &MO);
  void EmitBasicBlockStart(const MachineBasicBlock &MBB) const override;
  bool runOnMachineFunction(MachineFunction &MF) override;
protected:
  void EmitSubBlockForPushcont(const TVMMCInstLower &lower, const MCInst &Inst,
                               int depth);
  void EmitBBEntry(const MachineBasicBlock &MBB) const;
private:
  TVMFunctionInfo *MFI;
};
} // end of anonymous namespace

std::string TVMAsmPrinter::regToString(const MachineOperand &MO) {
  unsigned RegNo = MO.getReg();
  assert(TargetRegisterInfo::isVirtualRegister(RegNo) &&
         "Unlowered physical register encountered during assembly printing");
  assert(!MFI->isVRegStackified(RegNo));
  unsigned TVMReg = MFI->getTVMReg(RegNo);
  assert(TVMReg != TVMFunctionInfo::UnusedReg);
  return 's' + utostr(TVMReg);
}

void TVMAsmPrinter::printOperand(const MachineInstr *MI, int OpNum,
                                 raw_ostream &O, const char *Modifier) {
  const MachineOperand &MO = MI->getOperand(OpNum);
  switch (MO.getType()) {
  default:
    llvm_unreachable("Not implemented yet!");
  case MachineOperand::MO_Register:
    O << regToString(MO);
    return;
  case MachineOperand::MO_Immediate:
    if (!Modifier || strcmp(Modifier, "nohash"))
      O << '#';
    O << MO.getImm();
    return;
  }
}

//===----------------------------------------------------------------------===//
void TVMAsmPrinter::EmitInstruction(const MachineInstr *MI) {
  LLVM_DEBUG(dbgs() << "EmitInstruction: " << *MI << '\n');
  if (isVerbose())
    for (auto Comment : MFI->getStackModelComments(MI)) {
      OutStreamer->AddComment(Comment);
    }
  switch (MI->getOpcode()) {
  case TVM::ARGUMENT:
    llvm_unreachable("CG only instruction mustn't reach ASM printer");
    break;
  case TVM::REG_TO_REG_COPY_S:
    break;
  case TVM::FALLTHROUGH_RETURN:
    if (isVerbose()) {
      OutStreamer->AddComment("fallthrough return");
      OutStreamer->AddBlankLine();
    }
    break;
  default:
    TVMMCInstLower MCInstLowering(OutContext, *this);

    MCInst TmpInst;
    MCInstLowering.lower(MI, TmpInst);
    // We need to access OutStreamer->GetOS() to have such code pattern:
    // (tabs for first offset from labels ans 2-spaces nested PUSHCONTs)
    // \tInstr1
    // \tInstr2
    // \tPUSHCONT
    // \t{
    // \t  Instr3
    // \t  Instr4
    // \t  PUSHCONT
    // \t  {
    // \t    Instr5
    // \t    Instr6
    // \t  }
    // \t}
    OutStreamer->GetOS() << "\t";
    EmitToStreamer(*OutStreamer, TmpInst);
    if (TmpInst.getOpcode() == TVM::PUSHCONT_MBB_S) {
      if (MI->getParent() == &MF->front())
        EmitSubBlockForPushcont(MCInstLowering, TmpInst, 0);
      else
        OutStreamer->EmitRawText("\t{ }\n");
    }
  }
}

void TVMAsmPrinter::EmitBBEntry(const MachineBasicBlock &MBB) const {
  if (isVerbose()) {
    if (const BasicBlock *BB = MBB.getBasicBlock()) {
      if (BB->hasName()) {
        BB->printAsOperand(OutStreamer->GetCommentOS(), false, BB->getModule());
        OutStreamer->GetCommentOS() << '\n';
      }
    }
    auto BBStackComment = MFI->getStackModelBBComment(&MBB);
    if (!BBStackComment.empty())
      OutStreamer->AddComment(BBStackComment, true);
  }
  OutStreamer->emitRawComment(" %bb." + Twine(MBB.getNumber()) + ":", false);
}

void TVMAsmPrinter::EmitSubBlockForPushcont(const TVMMCInstLower &lower,
                                            const MCInst &Inst,
                                            int depth) {
  OutStreamer->EmitRawText("\t" + std::string(depth, ' ') + "{\n");

  const auto &Mapping = lower.getMCInstrsMap();
  const MachineBasicBlock *MBB = nullptr;

  auto I = llvm::find_if(Inst, [](const MCOperand &op) { return op.isInst(); });
  if (I != Inst.end()) {
    auto MIit = Mapping.find(I->getInst());
    if (MIit != Mapping.end()) {
      if ((MBB = MIit->second->getParent()))
        EmitBBEntry(*MBB);
    }
  }

  for (const auto &op : Inst) {
    if (op.isInst()) {
      auto &curInst = *op.getInst();
      if (isVerbose()) {
        auto MIit = Mapping.find(&curInst);
        if (MIit != Mapping.end())
          for (auto &Comment : MFI->getStackModelComments(MIit->second))
            OutStreamer->AddComment(Comment);
        if (curInst.getOpcode() == TVM::FALLTHROUGH_RETURN) {
          OutStreamer->AddComment("fallthrough return");
          OutStreamer->AddBlankLine();
        }
      }
      OutStreamer->GetOS() << "\t";
      static_cast<formatted_raw_ostream &>(OutStreamer->GetOS()).
          PadToColumn(10 + depth);
      EmitToStreamer(*OutStreamer, curInst);
      if (curInst.getOpcode() == TVM::PUSHCONT_MBB_S)
        EmitSubBlockForPushcont(lower, curInst, depth + 2);
    }
  }
  OutStreamer->EmitRawText("\t" + std::string(depth, ' ') + "}\n");
}

void TVMAsmPrinter::EmitBasicBlockStart(const MachineBasicBlock &MBB) const {
  EmitBBEntry(MBB);
}

bool TVMAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
  MFI = MF.getInfo<TVMFunctionInfo>();
  return AsmPrinter::runOnMachineFunction(MF);
}

// Force static initialization.
extern "C" void LLVMInitializeTVMAsmPrinter() {
  RegisterAsmPrinter<TVMAsmPrinter> X(getTheTVMTarget());
}
