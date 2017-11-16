#pragma once
#include "NeuralNet.h"

class AILearning
{
public:
	AILearning();
	~AILearning();

private:
	void PrintVectorValues(string initialLine, const vector<double> &vectorToPrint);
	void Initiate();
};

