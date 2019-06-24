#include "include.h"

using namespace Eigen;

extern "C" {

	SUPEREXPORT void deleteNaiveRBFModel(t_rbfData* RBF)
	{
		if (RBF->W != NULL)
			delete RBF->W;
		if (RBF->X != NULL)
			delete RBF->X;
		delete RBF;

	}

	SUPEREXPORT void* createNaiveRBFModel(int inputCountPerSample)
	{
		srand(time(NULL));

		inputCountPerSample = inputCountPerSample + 1;
		t_rbfData* RBF = new t_rbfData[1];

		RBF->inputCountPerSample = inputCountPerSample;
		RBF->W = NULL;
		RBF->X = NULL;
		return (RBF);
	}

	SUPEREXPORT void fitNaiveRBFRegression(t_rbfData * RBF, MatrixXd * X, MatrixXd * Y, double gamma)
	{
		RBF->W = new Eigen::MatrixXd(RBF->inputCountPerSample, 1);
		RBF->X = new Eigen::MatrixXd(X->rows(), X->cols());
		RBF->gamma = gamma;
		Eigen::MatrixXd tmp(1, X->cols());

		RBF->X = X;
		Eigen::MatrixXd phi(X->rows(), X->rows());

		for (int i = 0; i < X->rows(); i++)
		{
			for (int j = 0; j < X->rows(); j++)
			{

				tmp = (*X).block(i, 0, 1, X->cols()) - (*X).block(j, 0, 1, X->cols());
				phi(i, j) = exp(-RBF->gamma * pow(tmp.norm(), 2));
			}
		}

		Eigen::MatrixXd phiInv = (phi).completeOrthogonalDecomposition().pseudoInverse();
		(*RBF->W) = phiInv * (*Y);
	}

	SUPEREXPORT void fitNaiveRBFClassification(t_rbfData* RBF, MatrixXd* X, MatrixXd* Y, double gamma)
	{
		fitNaiveRBFRegression(RBF, X, Y, gamma);
	}
	SUPEREXPORT double predictNaiveRBFRegression(t_rbfData * RBF, VectorXd * XPredict)
	{
		MatrixXd gauss(1, RBF->X->rows());
		for (int i = 0; i < RBF->X->rows(); i++)
		{
			Eigen::MatrixXd tmp(1, RBF->X->cols());
			
			//tmp = (*RBF->X).block(i, 0, 1, RBF->X->cols()) - (*XPredict).transpose();
			tmp = (*XPredict).transpose() - (*RBF->X).block(i, 0, 1, RBF->X->cols());
			gauss(0, i) = exp(-RBF->gamma * pow(tmp.norm(), 2));
		}
		return (gauss * (*RBF->W)).sum();
	}

	SUPEREXPORT double predictNaiveRBFClassification(t_rbfData* RBF, VectorXd* XPredict)
	{
		return predictNaiveRBFRegression(RBF, XPredict) >= 0 ? 1.0 : -1.0;
	}
}