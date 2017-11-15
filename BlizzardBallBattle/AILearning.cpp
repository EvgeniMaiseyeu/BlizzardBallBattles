#include "AILearning.h"
#include <iostream>

AILearning::AILearning()
{
	Initiate();
} 


AILearning::~AILearning()
{
}

void AILearning::Initiate()
{
	vector<unsigned> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);

	NeuralNet myNet = NeuralNet(topology);

	vector<double> inputVals;
	myNet.FeedForward(inputVals);

	vector<double> targetVals;
	myNet.BackProp(targetVals);

	vector<double> resultVals;
	myNet.GetResults(resultVals);
}