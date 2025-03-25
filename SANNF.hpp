#pragma once

#include <vector>
#include <random>

/*
 * References:
 * https://www.geeksforgeeks.org/introduction-to-artificial-neutral-networks/?ref=ml_lbp
 * https://www.geeksforgeeks.org/layers-in-artificial-neural-networks-ann/
 */

enum LayerTypes
{
    Dense,
    Convolutional,
    Recurrent,
    Dropout,
    Pooling,
    BatchNormalization
};

enum ActivationFunctions
{
    None,
};

/*
 * Steps:
 * 1. Initialization
 *      Creating layers
 *      Creating/Loading weights
 *      Biases??? (rn ignore then, cuz bias - additional layer output that prevents NN from zeroing out)
 *      Setting Learning rate
 * 2. Feeding in data
 *      Splitting data into inputs and feeding it to input layer
 * 3. Forward propagation (Getting result)
 *      Using weights, activation functions and previous layer results for getting next layer results
 * 4. Calculating error
 *      Using Loss function to get measured error
 * 5. Back propagation (updating weights)
 *      Compute gradient to update weights and biases??
 */

namespace
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 1);
}

namespace SANNF
{
    class Layer
    {
        int m_Size;
        ActivationFunctions m_ActivationFunc;
    public:
        Layer(int size, ActivationFunctions activation_func)
        {
            m_Size = size;
            m_ActivationFunc = activation_func;
        }
        
        [[nodiscard]] int GetSize() const { return m_Size; }
        [[nodiscard]] ActivationFunctions GetActivationFunction() const { return m_ActivationFunc; }
        //TODO: basic neuron amount setting, activation type and just layer types
    };
    
    class Optimizer
    {
    
    };
    
    ///Neural network representation.\n
    ///Stores layers and their weights.
    class NeuralNetwork
    {
        //weight, biases, learning rate
        std::vector<Layer> m_Layers;
        std::vector<std::vector<double>> m_Weights; //First num - input neurons, second num - output neurons, from third - weights
        //TODO: layers, first is always input, last is always output
        //TODO: getting result of NN and back propagation
    public:
         ///Adds new layer to NN
         ///@param size Amount of neurons in layer
         ///@param activation_func Activation function of each neuron
        void AddLayer(int size, ActivationFunctions activation_func)
        {
            AddLayer(Layer(size, activation_func));
        }
        
         ///Adds new layer to NN
         ///@param layer Already created layer
        void AddLayer(Layer layer)
        {
            m_Layers.emplace_back(layer);
            UpdateWeights();
        }
        
        /// Updates the weights vector.\n
        /// Adds more random weights, if NN can't forward propagate
        void UpdateWeights(bool CheckCreated=false)
        {
            if (m_Layers.size() < 2) return;
            
            unsigned long long i, j;
            
            if (CheckCreated) i = 0;
            else i = m_Weights.size();
            
            for (;i < m_Layers.size() - 1; i++)
            {
                if (m_Weights.size() == i) m_Weights.emplace_back();
                for (j = m_Weights[i].size(); j < m_Layers[i].GetSize() * m_Layers[i + 1].GetSize(); j++)
                    m_Weights[i].emplace_back(dist(e2));
            }
        }
        
        std::vector<double> Run(const std::vector<double>& input)
        {
            if (input.size() != m_Layers[0].GetSize()) throw std::logic_error("Wrong input size for running NN");
             
             std::vector<double> temp1 = input, temp2 = {};
             
             //TODO: activation function
             for (int i = 1; i < m_Layers.size(); i++)
             {
                 //Clear and reallocate size
                 temp2.resize(0);
                 temp2.resize(m_Layers[i].GetSize());
                 
                 //TODO: optimize
                 //Stepping through each neurons input, multiplying it by weights and summing up
                 for (int j = 0; j < temp2.size(); j++)
                     for (int t = 0; t < m_Layers[i - 1].GetSize(); t++)
                         temp2[j] += temp1[t] * m_Weights[i - 1][m_Layers[i - 1].GetSize() * j + t];
                 
                 //Activation func
                 
                 
                 //Sending results to next neurons (or out)
                 temp1 = temp2;
             }
             
            return temp1;
        }
    };
}