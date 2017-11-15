#include "NeuralNet.h"

NeuralNet::NeuralNet(const vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		m_layers.push_back(Layer());

		// The number of outputs is the number of Neurons in the next layer.
		// If this is the output layer (the last layer in our net), then the output Neruons are 0.
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
		// Created a new layer, now let's fill it with Neurons!
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(numOutputs));
		}
	}
}


NeuralNet::~NeuralNet()
{
}

void NeuralNet::FeedForward(const vector<double> &inputVals)
{

}

void NeuralNet::BackProp(const vector<double> &targetVals)
{

}

void NeuralNet::GetResults(vector<double> &resultVals) const
{

}