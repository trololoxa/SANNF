#include <iostream>

#include "SANNF.hpp"

std::vector<std::pair<std::vector<int>, int>> train_dataset =
        {
         {{0, 0, 0}, 0},
         {{1, 0, 0}, 1},
         {{0, 1, 0}, 1},
         {{0, 0, 1}, 1},
         {{1, 1, 0}, 0},
         {{1, 0, 1}, 0},
         {{1, 1, 1}, 1},
        };

std::vector<std::pair<std::vector<int>, int>> test_dataset =
        {
         {{0, 1, 0}, 1},
         {{0, 1, 1}, 0},
        };

int main()
{
   auto NN = SANNF::NeuralNetwork();
   
   //NN.SetParams();
   
   NN.AddLayer(3, None);
   NN.AddLayer(2, None);
   NN.AddLayer(1, None);
   
   auto test = NN.Run({0.3, 0.5, 1});
   
   //NN.fit(train_dataset, 10);
   
   //NN.evaluate(test_dataset);
   
   return 0;
}
