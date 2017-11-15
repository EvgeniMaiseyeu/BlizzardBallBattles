#pragma once
#include <vector>
#include "Neuron.h"

using namespace std;

typedef vector<Neuron> Layer;

class NeuralNet
{
public:
	NeuralNet(const vector<unsigned> &topology);
	~NeuralNet();
	void FeedForward(const vector<double> &inputVals);
	void BackProp(const vector<double> &targetVals);
	void GetResults(vector<double> &resultVals) const;

private: 
	vector<Layer> m_layers;
};

