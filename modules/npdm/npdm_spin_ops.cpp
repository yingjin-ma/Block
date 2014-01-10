/*
Developed by Sandeep Sharma and Garnet K.-L. Chan, 2012
Copyright (c) 2012, Garnet K.-L. Chan

This program is integrated in Molpro with the permission of
Sandeep Sharma and Garnet K.-L. Chan
*/

#include "npdm_spin_ops.h"

namespace SpinAdapted {

//===========================================================================================================================================================
// NOTE transpose applied to RHS operator here

boost::shared_ptr<SparseMatrix> NpdmSpinOps::build_compound_operator( bool is_fermion, int sign,
                                                                      boost::shared_ptr<SparseMatrix> lhsOp,
                                                                      boost::shared_ptr<SparseMatrix> rhsOp,
                                                                      int ispin, std::vector<int> indices, bool transpose )
{
  // Initialize new operator
//FIXME new optype not general!
  boost::shared_ptr<SparseMatrix> newOp (new Cre);
  assert( lhsOp->get_orbs().size() + rhsOp->get_orbs().size() == indices.size() );
  newOp->set_orbs() = indices;
  newOp->set_initialised() = true;
  newOp->set_fermion() = is_fermion;
  if (sign == 1) newOp->set_deltaQuantum() = ( lhsOp->get_deltaQuantum() + rhsOp->get_deltaQuantum() ).at(ispin);
  else newOp->set_deltaQuantum() = ( lhsOp->get_deltaQuantum() - rhsOp->get_deltaQuantum() ).at(ispin);
//cout << "Building compound operator.......................................................\n";
//cout << "2*lhs spin = " << lhsOp->get_deltaQuantum().get_s() << std::endl;
//cout << "2*rhs spin = " << rhsOp->get_deltaQuantum().get_s() << std::endl;
//cout << "2*total spin = " << newOp->get_deltaQuantum().get_s() << std::endl;
  newOp->allocate( spinBlock_->get_stateInfo() );

  if (transpose) {
    // Build compound operator as product of LHS and TRANSPOSE( RHS )
    operatorfunctions::Product(spinBlock_, *lhsOp, Transposeview(*rhsOp), *newOp, 1.0 );
  }
  else {
    // Build compound operator as product of LHS and RHS
    operatorfunctions::Product(spinBlock_, *lhsOp, *rhsOp, *newOp, 1.0 );
  }
//cout << *newOp;
//cout << "Done Building compound operator.......................................................\n";

  return newOp;
}

//===========================================================================================================================================================

}
