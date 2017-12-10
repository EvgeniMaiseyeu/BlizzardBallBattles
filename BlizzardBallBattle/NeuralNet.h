#pragma once
#include <vector>
#include "Neuron.h"

using namespace std;
// class Neuron;
typedef vector<Neuron> Layer;

class NeuralNet
{
public:
	NeuralNet(const vector<unsigned> &topology);
	~NeuralNet();
	void FeedForward(const vector<double> &inputVals);
	void BackProp(const vector<double> &targetVals);
	void GetResults(vector<double> &resultVals) const;
	double GetRecentAverageError(void) const { return m_recentAverageError; };

private: 
	vector<Layer> m_layers;
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};

