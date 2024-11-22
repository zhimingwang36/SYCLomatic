//===--------------- RulesLangGraphInterop.cpp----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AnalysisInfo.h"
#include "RuleInfra/ASTmatcherCommon.h"
#include "RuleInfra/CallExprRewriter.h"
#include "RuleInfra/CallExprRewriterCommon.h"
#include "RuleInfra/ExprAnalysis.h"
#include "RuleInfra/MemberExprRewriter.h"
#include "RuleInfra/MigrationStatistics.h"
#include "RulesLang.h"
#include "RulesLang/BarrierFenceSpaceAnalyzer.h"
#include "RulesLang/GroupFunctionAnalyzer.h"
#include "RulesLang/MapNamesLang.h"
#include "RulesMathLib/MapNamesRandom.h"
#include "TextModification.h"
#include "Utility.h"
#include "clang/AST/Decl.h"
#include "clang/AST/Expr.h"
#include "clang/AST/ExprCXX.h"
#include "clang/AST/Stmt.h"
#include "clang/AST/Type.h"
#include "clang/AST/TypeLoc.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Analysis/AnalysisDeclContext.h"
#include "clang/Analysis/CallGraph.h"
#include "clang/Basic/Cuda.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Lex/MacroArgs.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/Path.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::dpct;
using namespace clang::tooling;

extern clang::tooling::UnifiedPath
    DpctInstallPath; // Installation directory for this tool
extern DpctOption<opt, bool> ProcessAll;
extern DpctOption<opt, bool> AsyncHandler;

namespace clang {
namespace dpct {

void GraphicsInteropRule::registerMatcher(ast_matchers::MatchFinder &MF) {
  auto graphicsInteropAPI = [&]() {
    return hasAnyName(
        "cudaGraphicsD3D11RegisterResource", "cudaGraphicsResourceSetMapFlags",
        "cudaGraphicsMapResources", "cudaGraphicsResourceGetMappedPointer",
        "cudaGraphicsResourceGetMappedMipmappedArray",
        "cudaGraphicsSubResourceGetMappedArray", "cudaGraphicsUnmapResources",
        "cudaGraphicsUnregisterResource");
  };

  MF.addMatcher(
      callExpr(callee(functionDecl(graphicsInteropAPI()))).bind("call"), this);
}

void GraphicsInteropRule::runRule(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  const CallExpr *CE = getNodeAsType<CallExpr>(Result, "call");
  if (!CE) {
    return;
  }

  ExprAnalysis EA(CE);
  emplaceTransformation(EA.getReplacement());
  EA.applyAllSubExprRepl();
}

} // namespace dpct
} // namespace clang
