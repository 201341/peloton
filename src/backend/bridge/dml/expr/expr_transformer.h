/*-------------------------------------------------------------------------
 *
 * expr_transformer.h
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 *-------------------------------------------------------------------------
 */

#pragma once

#include "backend/expression/abstract_expression.h"

#include "postgres.h"
#include "nodes/execnodes.h"

namespace peloton {
namespace bridge {

/**
 * @brief Helper class to transform a Postgres Expr tree to Peloton Expr tree
 */
class ExprTransformer {
 public:
  ExprTransformer(const ExprTransformer&) = delete;
  ExprTransformer& operator=(const ExprTransformer&) = delete;
  ExprTransformer(const ExprTransformer&&) = delete;
  ExprTransformer& operator=(const ExprTransformer&&) = delete;

  static void PrintPostgressExprTree(const ExprState* expr_state,
                                     std::string prefix = "");

  static expression::AbstractExpression* TransformExpr(
      const ExprState* expr_state);

  static bool CleanExprTree(expression::AbstractExpression* root);
  static expression::AbstractExpression* TranformMergeJoinClauses(
      const MergeJoinClause *join_clauses,
      const int num_clauses);

 private:
  /*
   * This set of TransformXXX methods should transform an PG ExprState tree
   * rooted at a ExprState pointing to a XXX Expr node.
   * A XXX Expr node should have a nodeTag of T_XXX.
   */

  static expression::AbstractExpression* TransformConst(const ExprState* es);
  static expression::AbstractExpression* TransformOp(const ExprState* es);
  static expression::AbstractExpression* TransformVar(const ExprState* es);
  static expression::AbstractExpression* TransformBool(const ExprState* es);
  static expression::AbstractExpression* TransformParam(const ExprState* es);
  static expression::AbstractExpression* TransformRelabelType(
      const ExprState* es);
  static expression::AbstractExpression* TransformFunc(const ExprState* es);

  static expression::AbstractExpression* TransformList(
      const ExprState* es, ExpressionType et = EXPRESSION_TYPE_CONJUNCTION_AND);
};

}  // namespace bridge
}  // namespace peloton
