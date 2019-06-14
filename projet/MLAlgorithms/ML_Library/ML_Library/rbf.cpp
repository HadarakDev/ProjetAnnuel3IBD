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
	SUPEREXPORT void* createRBFModel(int inputCountPerSample)
	{

		srand(time(NULL));

		inputCountPerSample = inputCountPerSample + 1;
		t_rbfData* RBF = new t_rbfData[1];

		RBF->inputCountPerSample = inputCountPerSample;
		RBF->W = NULL;
		RBF->X = NULL;
		return (RBF);

	}
	SUPEREXPORT void fitRBFRegression(t_rbfData * RBF, MatrixXd * X, MatrixXd * Y, double gamma)
	{
		RBF->W = new Eigen::MatrixXd(RBF->inputCountPerSample, 1);
		RBF->X = new Eigen::MatrixXd(X->rows(), X->cols());
		RBF->gamma = gamma;

		RBF->X = X;
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

	SUPEREXPORT double predictRBFRegression(t_rbfData * RBF, VectorXd * XPredict)
	{
		MatrixXd gauss(1, RBF->X->rows());
		for (int i = 0; i < RBF->X->rows(); i++)
		{
			Eigen::MatrixXd tmp(1, RBF->X->cols());
			
			tmp = (*RBF->X).block(i, 0, 1, RBF->X->cols()) - (*XPredict).transpose();
			gauss(0, i) = exp(-RBF->gamma * pow(tmp.norm(), 2));
		}
		return (gauss * (*RBF->W)).sum();
	}

	SUPEREXPORT double predictRBFClassification(t_rbfData* RBF, VectorXd* XPredict)
	{
		return predictRBFRegression(RBF, XPredict) >= 0 ? 1.0 : -1.0;
	}
}