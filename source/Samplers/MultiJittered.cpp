#include "MultiJittered.hpp"

MultiJittered::MultiJittered(const int num_samples, const int m)
	: Sampler(num_samples, m) {
	generate_samples();
}

MultiJittered::MultiJittered(const MultiJittered& rhs)			
	: Sampler(rhs) {
	generate_samples();
}

MultiJittered& MultiJittered::operator= (const MultiJittered& rhs) {
	if (this == &rhs) {		
		return (*this);
	}
	Sampler::operator=(rhs);
	generate_samples();
	return (*this);
}

MultiJittered* MultiJittered::clone() const {
	return (new MultiJittered(*this));
}

MultiJittered::~MultiJittered() 
{}

void MultiJittered::generate_samples() {
	int n = (int)sqrt((float)num_samples);
	float subcell_width = 1.0 / ((float)num_samples);

	//Set up initial diagonal sets   
	for (int p = 0; p < num_sets; p++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				Point2D sp;
				sp.x = (j * n + k) * subcell_width + rand_float() * subcell_width;  //set the X to j'th cell, k'th subcell
				sp.y = (k * n + j) * subcell_width + rand_float() * subcell_width;  //Set the Y to k'th cell, j'th subcell
				samples.push_back(sp);
			}
		}
	}
	shuffle_x_coordinates();
	shuffle_y_coordinates();
}