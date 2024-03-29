#ifndef __REGRESSIONDATA_IMP_HPP__
#define __REGRESSIONDATA_IMP_HPP__

// space case
RegressionData::RegressionData(std::vector<Point>& locations, VectorXr& observations, UInt order, std::vector<Real> lambdaS, MatrixXr& covariates, MatrixXi& incidenceMatrix, std::vector<UInt>& bc_indices, std::vector<Real>& bc_values, bool DOF, bool GCV, UInt search):
					locations_(locations), observations_(observations), covariates_(covariates), incidenceMatrix_(incidenceMatrix),
					order_(order), lambdaS_(lambdaS), bc_values_(bc_values), bc_indices_(bc_indices), DOF_(DOF), GCV_(GCV), flag_SpaceTime_(false), flag_Mixed_(false), search_(search)
{
	nRegions_ = incidenceMatrix_.rows();
	if(locations_.size()==0 && nRegions_==0)
	{
		locations_by_nodes_ = true;
		for(int i = 0; i<observations_.size();++i) observations_indices_.push_back(i);
	}
	else
	{
		locations_by_nodes_ = false;
	}
}

// space-mixed case
RegressionData::RegressionData(std::vector<Point>& locations, VectorXr& observations, UInt num_units, UInt order, std::vector<Real> lambdaS, MatrixXr& covariates, MatrixXi& incidenceMatrix, std::vector<UInt>& bc_indices, std::vector<Real>& bc_values, bool DOF, bool GCV, UInt search):
					locations_(locations), observations_(observations), num_units_(num_units), covariates_(covariates), incidenceMatrix_(incidenceMatrix),
					order_(order), lambdaS_(lambdaS), bc_values_(bc_values), bc_indices_(bc_indices), DOF_(DOF), GCV_(GCV), flag_SpaceTime_(false), flag_Mixed_(true), search_(search)
{
	nRegions_ = incidenceMatrix_.rows();
	if(locations_.size()==0 && nRegions_==0)
	{
		locations_by_nodes_ = true;
		for(int i = 0; i<observations_.size();++i) observations_indices_.push_back(i);
	}
	else
	{
		locations_by_nodes_ = false;
	}
}

// space-time case
RegressionData::RegressionData(std::vector<Point>& locations, std::vector<Real>& time_locations, VectorXr& observations, UInt order, std::vector<Real>& lambdaS, std::vector<Real>& lambdaT, MatrixXr& covariates, MatrixXi& incidenceMatrix, std::vector<UInt>& bc_indices, std::vector<Real>& bc_values, VectorXr& ic, bool flag_mass, bool flag_parabolic, bool DOF, bool GCV, UInt search):
					locations_(locations), time_locations_(time_locations), observations_(observations), covariates_(covariates), incidenceMatrix_(incidenceMatrix),
					order_(order), lambdaS_(lambdaS), lambdaT_(lambdaT), bc_values_(bc_values), bc_indices_(bc_indices), ic_(ic), flag_mass_(flag_mass), flag_parabolic_(flag_parabolic), DOF_(DOF), GCV_(GCV), flag_SpaceTime_(true), flag_Mixed_(false), search_(search)
{
	nRegions_ = incidenceMatrix_.rows();
	if(locations_.size()==0 && nRegions_==0)
	{
		locations_by_nodes_ = true;
		for(int i = 0; i<observations_.size();++i) observations_indices_.push_back(i);
	}
	else
	{
		locations_by_nodes_ = false;
	}
}

// space case
RegressionDataElliptic::RegressionDataElliptic(std::vector<Point>& locations, VectorXr& observations, UInt order,
												std::vector<Real> lambdaS, Eigen::Matrix<Real,2,2>& K,
												Eigen::Matrix<Real,2,1>& beta, Real c, MatrixXr& covariates,
												MatrixXi& incidenceMatrix, std::vector<UInt>& bc_indices,
												std::vector<Real>& bc_values, bool DOF, bool GCV, UInt search):
		 RegressionData(locations, observations, order, lambdaS, covariates, incidenceMatrix, bc_indices, bc_values, DOF, GCV, search), K_(K), beta_(beta), c_(c)
{;}

// space-mixed case
RegressionDataElliptic::RegressionDataElliptic(std::vector<Point>& locations, VectorXr& observations, UInt num_units, UInt order,
												std::vector<Real> lambdaS, Eigen::Matrix<Real,2,2>& K,
												Eigen::Matrix<Real,2,1>& beta, Real c, MatrixXr& covariates,
												MatrixXi& incidenceMatrix, std::vector<UInt>& bc_indices,
												std::vector<Real>& bc_values, bool DOF, bool GCV, UInt search):
		 RegressionData(locations, observations, num_units, order, lambdaS, covariates, incidenceMatrix, bc_indices, bc_values, DOF, GCV, search), K_(K), beta_(beta), c_(c)
{;}

// space-time case
RegressionDataElliptic::RegressionDataElliptic(std::vector<Point>& locations, std::vector<Real>& time_locations, VectorXr& observations, UInt order,
												std::vector<Real>& lambdaS, std::vector<Real>& lambdaT, Eigen::Matrix<Real,2,2>& K,
												Eigen::Matrix<Real,2,1>& beta, Real c, MatrixXr& covariates,
												MatrixXi& incidenceMatrix, std::vector<UInt>& bc_indices,
												std::vector<Real>& bc_values, VectorXr& ic, bool flag_mass, bool flag_parabolic, bool DOF, bool GCV, UInt search):
		 RegressionData(locations, time_locations, observations, order, lambdaS, lambdaT, covariates, incidenceMatrix, bc_indices, bc_values, ic, flag_mass, flag_parabolic, DOF, GCV, search),
		 										K_(K), beta_(beta), c_(c)
{;}

// space case
RegressionDataEllipticSpaceVarying::RegressionDataEllipticSpaceVarying(std::vector<Point>& locations,
									VectorXr& observations, UInt order, std::vector<Real> lambdaS,
									const std::vector<Eigen::Matrix<Real,2,2>, Eigen::aligned_allocator<Eigen::Matrix<Real,2,2> > >& K,
									const std::vector<Eigen::Matrix<Real,2,1>, Eigen::aligned_allocator<Eigen::Matrix<Real,2,1> > >& beta,
									const std::vector<Real>& c, const std::vector<Real>& u,
									MatrixXr& covariates, MatrixXi& incidenceMatrix,
									std::vector<UInt>& bc_indices, std::vector<Real>& bc_values, bool DOF, bool GCV, UInt search):
		RegressionData(locations, observations, order, lambdaS, covariates, incidenceMatrix, bc_indices, bc_values, DOF, GCV, search), K_(K), beta_(beta), c_(c), u_(u)
{;}

// space-mixed case
RegressionDataEllipticSpaceVarying::RegressionDataEllipticSpaceVarying(std::vector<Point>& locations,
									VectorXr& observations, UInt num_units, UInt order, std::vector<Real> lambdaS,
									const std::vector<Eigen::Matrix<Real,2,2>, Eigen::aligned_allocator<Eigen::Matrix<Real,2,2> > >& K,
									const std::vector<Eigen::Matrix<Real,2,1>, Eigen::aligned_allocator<Eigen::Matrix<Real,2,1> > >& beta,
									const std::vector<Real>& c, const std::vector<Real>& u,
									MatrixXr& covariates, MatrixXi& incidenceMatrix,
									std::vector<UInt>& bc_indices, std::vector<Real>& bc_values, bool DOF, bool GCV, UInt search):
		RegressionData(locations, observations, num_units, order, lambdaS, covariates, incidenceMatrix, bc_indices, bc_values, DOF, GCV, search), K_(K), beta_(beta), c_(c), u_(u)
{;}

// space-time case
RegressionDataEllipticSpaceVarying::RegressionDataEllipticSpaceVarying(std::vector<Point>& locations, std::vector<Real>& time_locations, VectorXr& observations, UInt order,
												std::vector<Real>& lambdaS, std::vector<Real>& lambdaT,
									const std::vector<Eigen::Matrix<Real,2,2>, Eigen::aligned_allocator<Eigen::Matrix<Real,2,2> > >& K,
									const std::vector<Eigen::Matrix<Real,2,1>, Eigen::aligned_allocator<Eigen::Matrix<Real,2,1> > >& beta,
									const std::vector<Real>& c, const std::vector<Real>& u,
									MatrixXr& covariates, MatrixXi& incidenceMatrix,
									std::vector<UInt>& bc_indices, std::vector<Real>& bc_values, VectorXr& ic, bool flag_mass, bool flag_parabolic, bool DOF, bool GCV, UInt search):
		 RegressionData(locations, time_locations, observations, order, lambdaS, lambdaT, covariates, incidenceMatrix, bc_indices, bc_values, ic, flag_mass, flag_parabolic, DOF, GCV, search),
											K_(K), beta_(beta), c_(c), u_(u)
{;}


#ifdef R_VERSION_
// space case
RegressionData::RegressionData(SEXP Rlocations, SEXP Robservations, SEXP Rorder, SEXP RlambdaS, SEXP Rcovariates,
							SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP GCV, SEXP RGCVmethod,
							SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations)
{
	flag_SpaceTime_=false;
	flag_Mixed_=false;

	setLocations(Rlocations);
	setBaryLocations(RbaryLocations);
	setIncidenceMatrix(RincidenceMatrix);
	setObservations(Robservations);
	setCovariates(Rcovariates);
	setNrealizations(Rnrealizations);
	setDOF_matrix(RDOF_matrix);

	GCVmethod_ = INTEGER(RGCVmethod)[0];
	order_ =  INTEGER(Rorder)[0];
	search_ =  INTEGER(Rsearch)[0];
	GCV_ = INTEGER(GCV)[0];
	DOF_ = INTEGER(DOF)[0];
	UInt length_indexes = Rf_length(RBCIndices);

	bc_indices_.assign(INTEGER(RBCIndices), INTEGER(RBCIndices) +  length_indexes);

	bc_values_.assign(REAL(RBCValues),REAL(RBCValues) + Rf_length(RBCIndices));

  UInt length_lambda = Rf_length(RlambdaS);
  for (UInt i = 0; i<length_lambda; ++i)  lambdaS_.push_back(REAL(RlambdaS)[i]);

	lambdaT_.push_back(0);
}


// space-mixed case
RegressionData::RegressionData(SEXP Rlocations, SEXP Robservations, SEXP RnumUnits, SEXP Rorder, SEXP RlambdaS, SEXP Rcovariates,
							SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP GCV, SEXP RGCVmethod,
							SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations)
{
	flag_SpaceTime_=false;
	flag_Mixed_=true;

	setLocations(Rlocations);
	setBaryLocations(RbaryLocations);
	setIncidenceMatrix(RincidenceMatrix);
	setObservationsMixed(Robservations);
	setCovariates(Rcovariates);
	setNrealizations(Rnrealizations);
	setDOF_matrix(RDOF_matrix);

	GCVmethod_ = INTEGER(RGCVmethod)[0];

	num_units_ = INTEGER(RnumUnits)[0];
	order_ =  INTEGER(Rorder)[0];
	search_ =  INTEGER(Rsearch)[0];
	GCV_ = INTEGER(GCV)[0];
	DOF_ = INTEGER(DOF)[0];
	UInt length_indexes = Rf_length(RBCIndices);

	bc_indices_.assign(INTEGER(RBCIndices), INTEGER(RBCIndices) +  length_indexes);

	bc_values_.assign(REAL(RBCValues),REAL(RBCValues) + Rf_length(RBCIndices));

  UInt length_lambda = Rf_length(RlambdaS);
  for (UInt i = 0; i<length_lambda; ++i)  lambdaS_.push_back(REAL(RlambdaS)[i]);

	lambdaT_.push_back(0);
}

// space-time case
RegressionData::RegressionData(SEXP Rlocations, SEXP Rtime_locations, SEXP Robservations, SEXP Rorder, SEXP RlambdaS, SEXP RlambdaT, SEXP Rcovariates,
						SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP Rflag_mass, SEXP Rflag_parabolic, SEXP Ric, SEXP GCV, SEXP RGCVmethod,
						SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations)
{
	flag_SpaceTime_ = true;
	flag_Mixed_=false;

	setLocations(Rlocations);
	setTimeLocations(Rtime_locations);
	setBaryLocations(RbaryLocations);
	setIncidenceMatrix(RincidenceMatrix);
	setObservationsTime(Robservations);
	setCovariates(Rcovariates);
	setNrealizations(Rnrealizations);
	setDOF_matrix(RDOF_matrix);

	GCVmethod_ = INTEGER(RGCVmethod)[0];

	order_ =  INTEGER(Rorder)[0];
	search_ =  INTEGER(Rsearch)[0];
	flag_mass_ = INTEGER(Rflag_mass)[0];
	flag_parabolic_ = INTEGER(Rflag_parabolic)[0];

	GCV_ = INTEGER(GCV)[0];
	DOF_ = INTEGER(DOF)[0];
	UInt length_indexes = Rf_length(RBCIndices);

	bc_indices_.assign(INTEGER(RBCIndices), INTEGER(RBCIndices) +  length_indexes);

	bc_values_.assign(REAL(RBCValues),REAL(RBCValues) + Rf_length(RBCIndices));

	UInt length_lambdaS = Rf_length(RlambdaS);
	for (UInt i = 0; i<length_lambdaS; ++i)  lambdaS_.push_back(REAL(RlambdaS)[i]);

	UInt length_lambdaT = Rf_length(RlambdaT);
	for (UInt i = 0; i<length_lambdaT; ++i)  lambdaT_.push_back(REAL(RlambdaT)[i]);

	UInt length_ic = Rf_length(Ric);
	ic_.resize(length_ic);
	for (UInt i = 0; i<length_ic; ++i)  ic_(i)=REAL(Ric)[i];

}

// space case
RegressionDataElliptic::RegressionDataElliptic(SEXP Rlocations, SEXP Robservations, SEXP Rorder, SEXP RlambdaS, SEXP RK, SEXP Rbeta,
				 SEXP Rc, SEXP Rcovariates, SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP GCV, SEXP RGCVmethod, SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations):
	RegressionData(Rlocations, Robservations, Rorder, RlambdaS, Rcovariates, RincidenceMatrix,
					 			   RBCIndices, RBCValues, GCV, RGCVmethod, Rnrealizations, DOF, RDOF_matrix, Rsearch, RbaryLocations)
{
	K_.resize(2, 2);
	for(auto i=0; i<2; ++i)
	{
		for(auto j=0; j<2 ; ++j)
		{
			K_(i,j)=REAL(RK)[i+ 2*j];
		}
	}

	beta_.resize(2);
	for(auto i=0; i<2 ; ++i)
	{
		beta_(i)=REAL(Rbeta)[i];
	}

	c_ =  REAL(Rc)[0];
}

// space-mixed case
RegressionDataElliptic::RegressionDataElliptic(SEXP Rlocations, SEXP Robservations, SEXP RnumUnits, SEXP Rorder, SEXP RlambdaS, SEXP RK, SEXP Rbeta,
				 SEXP Rc, SEXP Rcovariates, SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP GCV, SEXP RGCVmethod, SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations):
	RegressionData(Rlocations, Robservations, RnumUnits, Rorder, RlambdaS, Rcovariates, RincidenceMatrix,
					 			   RBCIndices, RBCValues, GCV, RGCVmethod, Rnrealizations, DOF, RDOF_matrix, Rsearch, RbaryLocations)
{
	K_.resize(2, 2);
	for(auto i=0; i<2; ++i)
	{
		for(auto j=0; j<2 ; ++j)
		{
			K_(i,j)=REAL(RK)[i+ 2*j];
		}
	}

	beta_.resize(2);
	for(auto i=0; i<2 ; ++i)
	{
		beta_(i)=REAL(Rbeta)[i];
	}

	c_ =  REAL(Rc)[0];
}

// space-time case
RegressionDataElliptic::RegressionDataElliptic(SEXP Rlocations, SEXP Rtime_locations, SEXP Robservations, SEXP Rorder, SEXP RlambdaS, SEXP RlambdaT, SEXP RK,
		SEXP Rbeta, SEXP Rc, SEXP Rcovariates, SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP Rflag_mass, SEXP Rflag_parabolic, SEXP Ric,	SEXP GCV,SEXP RGCVmethod, SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations):
	RegressionData(Rlocations, Rtime_locations, Robservations, Rorder, RlambdaS, RlambdaT, Rcovariates, RincidenceMatrix, RBCIndices, RBCValues, Rflag_mass, Rflag_parabolic, Ric, GCV, RGCVmethod, Rnrealizations, DOF, RDOF_matrix, Rsearch, RbaryLocations)
{
	K_.resize(2, 2);
	for(auto i=0; i<2; ++i)
	{
		for(auto j=0; j<2 ; ++j)
		{
			K_(i,j)=REAL(RK)[i+ 2*j];
		}
	}

	beta_.resize(2);
	for(auto i=0; i<2 ; ++i)
	{
		beta_(i)=REAL(Rbeta)[i];
	}

	c_ =  REAL(Rc)[0];
}

// space case
RegressionDataEllipticSpaceVarying::RegressionDataEllipticSpaceVarying(SEXP Rlocations, SEXP Robservations, SEXP Rorder, SEXP RlambdaS, SEXP RK, SEXP Rbeta,
				 SEXP Rc, SEXP Ru, SEXP Rcovariates, SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP GCV, SEXP RGCVmethod, SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations):
					 RegressionData(Rlocations, Robservations, Rorder, RlambdaS, Rcovariates, RincidenceMatrix, RBCIndices, RBCValues, GCV,RGCVmethod, Rnrealizations, DOF, RDOF_matrix, Rsearch, RbaryLocations),
					 K_(RK), beta_(Rbeta), c_(Rc), u_(Ru)
{;}

// space case
RegressionDataEllipticSpaceVarying::RegressionDataEllipticSpaceVarying(SEXP Rlocations, SEXP Robservations, SEXP RnumUnits, SEXP Rorder, SEXP RlambdaS, SEXP RK, SEXP Rbeta,
				 SEXP Rc, SEXP Ru, SEXP Rcovariates, SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP GCV, SEXP RGCVmethod, SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations):
					 RegressionData(Rlocations, Robservations, RnumUnits, Rorder, RlambdaS, Rcovariates, RincidenceMatrix, RBCIndices, RBCValues, GCV,RGCVmethod, Rnrealizations, DOF, RDOF_matrix, Rsearch, RbaryLocations),
					 K_(RK), beta_(Rbeta), c_(Rc), u_(Ru)
{;}

// space-time case
RegressionDataEllipticSpaceVarying::RegressionDataEllipticSpaceVarying(SEXP Rlocations, SEXP Rtime_locations, SEXP Robservations, SEXP Rorder, SEXP RlambdaS, SEXP RlambdaT, SEXP RK,
		SEXP Rbeta, SEXP Rc, SEXP Ru, SEXP Rcovariates, SEXP RincidenceMatrix, SEXP RBCIndices, SEXP RBCValues, SEXP Rflag_mass, SEXP Rflag_parabolic, SEXP Ric, SEXP GCV, SEXP RGCVmethod, SEXP Rnrealizations, SEXP DOF, SEXP RDOF_matrix, SEXP Rsearch, SEXP RbaryLocations):
					 RegressionData(Rlocations, Rtime_locations, Robservations, Rorder, RlambdaS, RlambdaT, Rcovariates, RincidenceMatrix, RBCIndices, RBCValues, Rflag_mass, Rflag_parabolic, Ric, GCV, RGCVmethod, Rnrealizations, DOF, RDOF_matrix, Rsearch, RbaryLocations),
					 K_(RK), beta_(Rbeta), c_(Rc), u_(Ru)
{;}

void RegressionDataEllipticSpaceVarying::print(std::ostream & out) const
{
	for (auto i=0;i<18;i++)
		out<<K_(i);
	for (auto i=0;i<18;i++)
		out<<beta_(i);
	for (auto i=0;i<18;i++)
		out<<c_(i);
}

void RegressionData::setObservations(SEXP Robservations)
{
	UInt n_obs_ = Rf_length(Robservations);
	observations_.resize(n_obs_);
	observations_indices_.reserve(n_obs_);

	UInt count = 0;
	if(locations_.size() == 0 && nRegions_ == 0)
	{
		locations_by_nodes_ = true;
		for(auto i=0;i<n_obs_;++i)
		{
			if(!ISNA(REAL(Robservations)[i]))
			{
				observations_[count] = REAL(Robservations)[i];
				count++;
				observations_indices_.push_back(i);
			}
		}
		observations_.conservativeResize(count, Eigen::NoChange);
	}
	else // locations_.size() > 0 NOR nRegions_ > 0
	{
		locations_by_nodes_ = false;
		for(auto i=0;i<n_obs_;++i)
		{
			observations_[i] = REAL(Robservations)[i];
		}
	}

	//std::cout<<"Observations #"<<observations_.size()<<std::endl<<observations_<<std::endl;
	//for(auto i=0;i<observations_indices_.size();++i)	std::cout<<observations_indices_[i]<<std::endl;
}

void RegressionData::setObservationsMixed(SEXP Robservations)
{
	UInt n_obs_ = Rf_length(Robservations);
	observations_.resize(n_obs_);
	observations_indices_.reserve(n_obs_);

	UInt count = 0;
	locations_by_nodes_ = (locations_.size() == 0 && nRegions_ == 0) ? true : false;

	for(auto i=0;i<n_obs_;++i)
	{
		if(!ISNA(REAL(Robservations)[i]))
		{
			observations_(i) = REAL(Robservations)[i];
			observations_indices_.push_back(i);
		}
		else
		{
			observations_(i) = 0.0;
			observations_na_.push_back(i);
		}
	}
	//std::cout<<"Observations #"<<observations_.size()<<std::endl<<observations_<<std::endl;
	//for(auto i=0;i<observations_indices_.size();++i)	std::cout<<observations_indices_[i]<<std::endl;
}

void RegressionData::setObservationsTime(SEXP Robservations)
{
	UInt n_obs_ = Rf_length(Robservations);
	observations_.resize(n_obs_);
	observations_indices_.reserve(n_obs_);

	UInt count = 0;
	locations_by_nodes_ = (locations_.size() == 0 && nRegions_ == 0) ? true : false;

	for(auto i=0;i<n_obs_;++i)
	{
		if(!ISNA(REAL(Robservations)[i]))
		{
			observations_(i) = REAL(Robservations)[i];
			observations_indices_.push_back(i);
		}
		else
		{
			observations_(i) = 0.0;
			observations_na_.push_back(i);
		}
	}
	//std::cout<<"Observations #"<<observations_.size()<<std::endl<<observations_<<std::endl;
	//for(auto i=0;i<observations_indices_.size();++i)	std::cout<<observations_indices_[i]<<std::endl;
}

// void RegressionData::setCovariates(SEXP Rcovariates)
// {
// 	n_ = INTEGER(Rf_getAttrib(Rcovariates, R_DimSymbol))[0];
// 	p_ = INTEGER(Rf_getAttrib(Rcovariates, R_DimSymbol))[1];
//
// 	covariates_.resize(n_, p_);
//
// 	for(auto i=0; i<n_; ++i)
// 	{
// 		for(auto j=0; j<p_ ; ++j)
// 		{
// 			covariates_(i,j)=REAL(Rcovariates)[i+ n_*j];
// 		}
// 	}
// }

void RegressionData::setCovariates(SEXP Rcovariates)
{
	n_ = INTEGER(Rf_getAttrib(Rcovariates, R_DimSymbol))[0];
	p_ = INTEGER(Rf_getAttrib(Rcovariates, R_DimSymbol))[1];
	UInt k=0;

	covariates_.resize(n_, p_);

	for(auto i=0; i<n_; ++i)
	{
		for(auto j=0; j<p_ ; ++j)
		{
			if(observations_na_.size()>k && i==observations_na_[k])
			{
				covariates_(i,j)=0;
				k++;
			}
			else
			{
				covariates_(i,j)=REAL(Rcovariates)[i+ n_*j];
			}
		}
	}
}

void RegressionData::setDOF_matrix(SEXP RDOF_matrix)
{
	n_ = INTEGER(Rf_getAttrib(RDOF_matrix, R_DimSymbol))[0];
	p_ = INTEGER(Rf_getAttrib(RDOF_matrix, R_DimSymbol))[1];

	dof_matrix_.resize(n_, p_);

	for(auto i=0; i<n_; ++i)
	{
		for(auto j=0; j<p_ ; ++j)
		{
			dof_matrix_(i,j)=REAL(RDOF_matrix)[i+ n_*j];
		}
	}
}

void RegressionData::setLocations(SEXP Rlocations)
{
	n_ = INTEGER(Rf_getAttrib(Rlocations, R_DimSymbol))[0];
	if(n_>0){
		int ndim = INTEGER(Rf_getAttrib(Rlocations, R_DimSymbol))[1];

	  if (ndim == 2){
			for(auto i=0; i<n_; ++i)
			{
				locations_.emplace_back(REAL(Rlocations)[i+ n_*0],REAL(Rlocations)[i+ n_*1]);
			}
		}else{ //ndim == 3
			for(auto i=0; i<n_; ++i)
			{
				locations_.emplace_back(REAL(Rlocations)[i+ n_*0],REAL(Rlocations)[i+ n_*1],REAL(Rlocations)[i+ n_*2]);
			}
		}
	}
}

void RegressionData::setTimeLocations(SEXP Rtime_locations)
{
	UInt n_time_loc_ = Rf_length(Rtime_locations);
  time_locations_.resize(n_time_loc_);

	for(auto i=0;i<n_time_loc_;++i)
	{
		time_locations_[i] = REAL(Rtime_locations)[i];
	}
}

void RegressionData::setBaryLocations(SEXP RbaryLocations)
{
	//RECIEVE BARYCENTER INFORMATION FROM R
	if (TYPEOF(RbaryLocations) != 0) { //TYPEOF(RbaryLocations) == 0 means SEXPTYPE is NILSXP (Description is NULL)
		UInt* id_ 	= INTEGER(VECTOR_ELT(RbaryLocations, 1));
		Real* bary_ 	= REAL(VECTOR_ELT(RbaryLocations, 2));
		
		UInt n_ = INTEGER(Rf_getAttrib(VECTOR_ELT(RbaryLocations, 2), R_DimSymbol))[0];
		UInt p_ = INTEGER(Rf_getAttrib(VECTOR_ELT(RbaryLocations, 2), R_DimSymbol))[1]; //barycenter column dimension

		barycenters_.resize(n_, p_);
		element_ids_.resize(n_);

		if(n_>0){ 
			for(auto i=0; i<n_; ++i)
			{
				for (auto j=0; j<p_; ++j)
				{
				barycenters_(i,j)= bary_[i+ n_*j];
				}
				element_ids_(i) = id_[i];
			}
		}
		locations_by_barycenter_ =true;
	} else {
		locations_by_barycenter_ =false;
	}
}

void RegressionData::setNrealizations(SEXP Rnrealizations) {
	nrealizations_ = INTEGER(Rnrealizations)[0];
}

void RegressionData::setIncidenceMatrix(SEXP RincidenceMatrix)
{
	nRegions_ = INTEGER(Rf_getAttrib(RincidenceMatrix, R_DimSymbol))[0];
	UInt p = INTEGER(Rf_getAttrib(RincidenceMatrix, R_DimSymbol))[1];

	incidenceMatrix_.resize(nRegions_, p);

	for(auto i=0; i<nRegions_; ++i)
	{
		for(auto j=0; j<p; ++j)
		{
			incidenceMatrix_(i,j) = INTEGER(RincidenceMatrix)[i+nRegions_*j];
		}
	}
}

#endif

void RegressionData::printObservations(std::ostream & out) const
{

	for(auto i=0;i<observations_.size(); i++)
	{
		out<<i<<"\t"<<observations_(i)<<std::endl;
	}
}

void RegressionData::printCovariates(std::ostream & out) const
{

	for(auto i=0;i<covariates_.rows(); i++)
	{
		for(auto j=0; j<covariates_.cols(); j++)
		{
			out<<covariates_(i,j)<<"\t";
		}
		out<<std::endl;
	}
}

void RegressionData::printLocations(std::ostream & out) const
{

	for(std::vector<Point>::size_type i=0;i<locations_.size(); i++)
	{
		locations_[i].print(out);
		//std::cout<<std::endl;
	}
}

void RegressionData::printIncidenceMatrix(std::ostream & out) const
{
	for (auto i=0; i<incidenceMatrix_.rows(); i++)
	{
		for (auto j=0; j<incidenceMatrix_.cols(); j++)
		{
			out << incidenceMatrix_(i,j) << "\t";
		}
		out << std::endl;
	}
}

#endif
