#include <Eigen/Dense>

typedef struct s_pmcData
{
	double	***W;
	int		*structure;
	int		lenStructure;
	double  **output;
	double  **sigma;
}				t_pmcData;

