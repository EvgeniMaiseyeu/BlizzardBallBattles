#include "AILearning.h"
#include "TrainingData.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

AILearning::AILearning()
{
	Initiate();
} 


AILearning::~AILearning()
{
}

void AILearning::Initiate()
{
	TrainingData trainingData = TrainingData();

	vector<unsigned> topology;
	trainingData.GetTopology(topology);
	NeuralNet myNet = NeuralNet(topology);

	vector<double> inputValues, targetValues, resultValues;
	unsigned sampleSize = 10;

	for (unsigned i = 0; i < sampleSize; ++i)
	{
		// Get new input data and feed it forward
		if (trainingData.GetNextInputs(inputValues) != topology[0])
		{
			return;
		}
		PrintVectorValues("Inputs: ", inputValues);
		myNet.FeedForward(inputValues);

		// Get the Neural Net's acrual results
		myNet.GetResults(resultValues);
		PrintVectorValues("Outputs: ", resultValues);

		// Train the Neural Net what the outputs should have been
		trainingData.GetTargetOutputs(targetValues);
		PrintVectorValues("Targets: ", targetValues);
		assert(targetValues.size() == topology.back());

		myNet.BackProp(targetValues);

		cout << "Neural Net recent average error: "
			<< myNet.GetRecentAverageError() << endl;
	}
}

void AILearning::PrintVectorValues(string initialLine, const vector<double> &vectorToPrint)
{
	cout << initialLine << " ";

	for (int e = 0; e < vectorToPrint.size(); ++e)
	{
		cout << vectorToPrint[e] << " ";
	}

	cout << endl;
}
