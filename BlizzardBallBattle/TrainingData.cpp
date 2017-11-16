#include "TrainingData.h"

TrainingData::TrainingData()
{
}


TrainingData::~TrainingData()
{
}

// The topology is the size of each layer in our Neural Net.
// First layer is our input layer, then our compute layer, then our output layer.
void TrainingData::GetTopology(vector<unsigned> &topology)
{
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);
}

// This will get the data being inputted into our Neural Net.
unsigned TrainingData::GetNextInputs(vector<double> &inputValues)
{
	inputValues.clear();

	inputValues.push_back(1.0);
	inputValues.push_back(1.0);
	inputValues.push_back(1.0);

	return inputValues.size();
}

// This is for training our data. It tells our Neural Net what it should have
// predicted as output given our input.
unsigned TrainingData::GetTargetOutputs(vector<double> &targetOutputValues)
{
	targetOutputValues.clear();

	targetOutputValues.push_back(0.0);

	return targetOutputValues.size();
}