#include "include.h"

using namespace Eigen;

extern "C" {

	SUPEREXPORT void deleteRBFModel(t_rbfData* RBF)
	{
		if (RBF->W != NULL)
			delete RBF->W;
		if (RBF->X != NULL)
			delete RBF->X;
		delete RBF;

	}
	SUPEREXPORT void* createLinearModel(int inputCountPerSample)
	{

		srand(time(NULL));

		inputCountPerSample = inputCountPerSample + 1;
		t_rbfData* RBF = new t_rbfData[1];

		RBF->inputCountPerSample = inputCountPerSample;
		RBF->W = NULL;
		RBF->X = NULL;
		return (RBF);
		
	}
	SUPEREXPORT t_rbfData fitRBFRegression(t_rbfData *RBF, MatrixXd *X, MatrixXd *Y, double gamma)
	{
		RBF->W = new Eigen::MatrixXd(RBF->inputCountPerSample, 1);
		RBF->X = new Eigen::MatrixXd(X->rows(), X->cols());
		RBF->gamma = gamma;

		Eigen::MatrixXd phi(X->rows(), X->rows());

		for (int i = 0; i < X->rows(); i++)
		{
			for (int j = 0; j < X->rows(); j++)
			{
				Eigen::MatrixXd tmp(1, X->cols());
				tmp = (*X).block(i, 0, 1, X->cols()) - (*X).block(j, 0, 1, X->cols());
				phi(i, j) = exp(-RBF->gamma * pow(tmp.norm(), 2));
			}
		}
		Eigen::MatrixXd phiInv = (phi).completeOrthogonalDecomposition().pseudoInverse();
		(*RBF->W) = phiInv * (*Y);
	}

	SUPEREXPORT double predictRBFRegression(t_rbfData *RBF, )
	{
		
	}