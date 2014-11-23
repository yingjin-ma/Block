#ifndef VA_SUBSPACE_HEADER
#define VA_SUBSPACE_HEADER
#include "wavefunction.h"
#include "sweep_params.h"
#include "perturb.h"
#include "fciqmchelper.h"

namespace SpinAdapted{
  namespace mps_nevpt{
    namespace Va{

      double do_one(SweepParams &sweepParams, const bool &warmUp, const bool &forward, const bool &restart, const int &restartSize, perturber& pb, int baseState);
      
      void BlockDecimateAndCompress (SweepParams &sweepParams, SpinBlock& system, SpinBlock& newSystem, const bool &useSlater, const bool& dot_with_sys, perturber& pb, int baseState);
      
//      void Startup (SweepParams &sweepParams, SpinBlock& system, SpinBlock& newSystem, const bool& dot_with_sys, perturber& pb, int baseState);

      void Startup(const SweepParams& sweepParams, const bool &forward, const MPS& statea, perturber& pb, int baseState);
      
      void run(int baseState);

      void calcHamiltonianAndOverlap(const MPS& statea, double& h, double& o, perturber& pb);
    }
  }
}
#endif