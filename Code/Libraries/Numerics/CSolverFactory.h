/*
*
*  Copyright 2011 by the CALATK development team
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*
*/

#ifndef C_SOLVER_FACTORY_H
#define C_SOLVER_FACTORY_H

#include "JSONParameterUtils.h"
#include "CALATKCommon.h"
#include "CProcessBase.h"

// includes for all the supported solvers
#include "CSolverLineSearchUnconstrained.h"
#include "CSolverLineSearchConstrained.h"
#include "CSolverIpOpt.h"
#include "CSolverLBFGS.h"
//#include "CSolverNLOpt.h"  // unsupported solver

#include <algorithm>

namespace CALATK
{
/**
  * Factory class to dynamically create different numerical solvers.
  *
  */

template < class TState >
class CSolverFactory :
    public CProcessBase
{
public:

  // all the kernel typdefs
  typedef CSolver< TState > SolverType;
  typedef CSolverLineSearchUnconstrained< TState > SolverLineSearchUnconstrainedType;
  typedef CSolverLineSearchConstrained< TState > SolverLineSearchConstrainedType;
  typedef CSolverIpOpt< TState > SolverIpOptType;
  typedef CSolverLBFGS< TState > SolverLBFGSType;

  enum NumericSolverType { LineSearchUnconstrained, LineSearchConstrained, IpOpt, LBFGS };

  CSolverFactory();
  ~CSolverFactory();

  static SolverType* CreateNewSolver( std::string sSolver );
  static SolverType* CreateNewSolver( NumericSolverType solver );

protected:
  static NumericSolverType GetSolverTypeFromString( std::string sSolver );
};

#include "CSolverFactory.txx"

} // end namespace

#endif // C_SOLVER_FACTORY_H