#pragma once
#include <vector>

using namespace std;

class TrainingData
{
public:
	TrainingData();
	~TrainingData();

	void GetTopology(vector<unsigned> &topology);
	unsigned GetNextInputs(vector<double> &inputValues);
	unsigned GetTargetOutputs(vector<double> &targetOutputValues);

private:
};

