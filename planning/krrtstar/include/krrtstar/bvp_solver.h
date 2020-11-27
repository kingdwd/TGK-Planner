#ifndef _BVP_SOLVER_H_
#define _BVP_SOLVER_H_

#include "poly_traj_utils/traj_utils.hpp"
#include <Eigen/Eigen>

#define DOUBLE_INTEGRATOR 2
#define TRIPLE_INTEGRATOR 3

namespace BVPSolver
{

using Eigen::Vector3d;
using Eigen::Vector2d;
using Eigen::VectorXd;

class IntegratorBVP {
public:
  void init(int model)
  {
    model_ = model;
    if (model_ == DOUBLE_INTEGRATOR)
    {
      x0_ = Eigen::Matrix<double, 6, 1>::Zero();
      x1_ = Eigen::Matrix<double, 6, 1>::Zero(); 
    }
    else if (model_ == TRIPLE_INTEGRATOR) 
    {
      x0_ = Eigen::Matrix<double, 9, 1>::Zero();
      x1_ = Eigen::Matrix<double, 9, 1>::Zero(); 
    }
  };

  void setRho(double rho) 
  {
    rho_ = rho;
  };

  bool solve(const VectorXd& start, const VectorXd& goal)
  {
    setBoundaries(start, goal);
    if (model_ == DOUBLE_INTEGRATOR)
    {
      return solveDouble();
    }
    else if (model_ == TRIPLE_INTEGRATOR) 
    {
      return solveTriple();
    }
    else
    {
      printf("Input model is neither double integrator nor triple.");
      return false;
    }
    
  };

  double getTauStar()
  {
    return tau_star_;
  };

  double getCostStar()
  {
    return cost_star_;
  };

  void getCoeff(CoefficientMat &coeff)
  {
    coeff = coeff_;
  };


private:
  VectorXd x0_, x1_;
  double rho_;
  int model_;
  CoefficientMat coeff_;
  double tau_star_, cost_star_;

  bool solveDouble();

  bool solveTriple();

  void setBoundaries(const VectorXd& start, const VectorXd& goal) 
  {
    x0_ = start;
    x1_ = goal;
  };

};

}
#endif