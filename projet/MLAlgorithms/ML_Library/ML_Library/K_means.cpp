#include "include.h"

using namespace Eigen;

extern "C" {

	SUPEREXPORT MatrixXd *K_means(MatrixXd X, int K)
	{
		if (K > X.rows())
			return NULL;

		MatrixXd* centroids = new MatrixXd(K, X.cols());
		int *references = new int[X.rows()];
		Eigen::MatrixXd tmp(1, X.cols());
		double* tmpNorms = new double[K];


		//init centroids with X samples
		for (int i = 0; i < K; i++)
		{
			int tmp = (rand() % X.rows());
			(*centroids)(i) = X(tmp);
		}

		int n = 0;


		while (n < 10) // arret
		{
			// assign K centroid for each sample
			for (int i = 0; i < X.rows(); i++)
			{
				for (int j = 0; j < K; j++)
				{

					tmp = (X).block(i, 0, 1, X.cols()) - (*centroids).block(j, 0, 1, centroids->cols());
					tmpNorms[j] = tmp.norm();
				}
				references[i] = getMinInArray(tmpNorms, K);
			}

			// reassign centroids
			MatrixXd tmpAdd(1, X.cols());
			for (int i = 0; i < K; i++)
			{
				int c = 0;
				for (n = 0; n < X.cols(); n++)
					tmpAdd(0, n) = 0;

				for (int j = 0; j < X.rows(); j++)
				{
					if (references[j] == i)
					{
						for (int m = 0; m < X.cols(); m++)
						{
							tmpAdd(0, m) += X(j, m);
						}
						c++;
					}
				}
				for (int b = 0; b < X.cols(); b++)
				{
					tmpAdd(0, b) = tmpAdd(0, b) / c;
				}
				(*centroids)(i) = tmpAdd(0);
			}
			n++;
		}
		return (centroids);
	}
}

int getMinInArray(double *Arr, int size)
{
	int min = 0;
	for (int i = 1; i < size; i++)
	{
		if (Arr[i] < Arr[min])
			min = i;
	}
	return (min);
}