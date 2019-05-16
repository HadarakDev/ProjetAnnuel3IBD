#include <Eigen/Dense>
typedef struct s_neurone
{
	Eigen::VectorXd	*weights;
}				t_neurone;

typedef struct s_layer
{

	t_neurone	*neurones;
}				t_layer;

