#pragma once
#include <vector>

using namespace std;

class Neuron
{
public:
	Neuron(unsigned numOutputs);
	~Neuron();
private:
	double m_outputVal;
	vector<double> m_outputWeights;
};

