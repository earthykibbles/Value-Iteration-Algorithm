// valueiteration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>


void printGrid(std::vector<std::vector<float>> &grid) {
    for (auto& row : grid) {
        for (float value : row) {
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<int> states(10);
    std::vector<int> actions(4);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    std::uniform_int_distribution<int> dist(-10, 10);

    std::vector<std::vector<float>> t_probs;
    std::vector<std::vector<float>> rewards;

    // Generate Random Transition Probabilities (0.0 - 1.0)
    for (int i = 0; i < states.size(); ++i) {
        std::vector<float> t_prob_ph(actions.size());
        float sum = 0.0;
        for (int j = 0; j < actions.size(); ++j) {
            t_prob_ph[j] = dis(gen);
            sum += t_prob_ph[j];
        }

        for (int j = 0; j < actions.size(); ++j) {
            t_prob_ph[j] /= sum;
        }
        t_probs.push_back(t_prob_ph);
        t_prob_ph.clear();
    }

    // Generate Rewards
    for (int i = 0; i < states.size(); ++i) {
        std::vector<float> rewards_ph(actions.size());
        for (int j = 0; j < actions.size(); ++j) {
            rewards_ph[j] = dist(gen);
        }
        rewards.push_back(rewards_ph);
        rewards_ph.clear();
    }

    // Initialize state values for each state
    std::vector<float> v_s;

    // Print the generated state values
    for (int k = 0; k < states.size(); k++) {
        v_s.push_back(0);
        std::cout << v_s[k] << "\t";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // Print the Transition Probability Matrix
    printGrid(t_probs);
    std::cout << std::endl;

    // Print the Rewards Matrix
    printGrid(rewards);
    std::cout << std::endl;


    // Start the algorithm
    int it = 0;
    double delta = 0;

    double theta = 0.000001;//A very small number that specifies the degree of error and convergence of our algorithm
    double gamma = 0.8; //Discount factor


    std::cout << "Start the Iteration" << "\n";

    while (true) {
        for (int i = 0; i < states.size(); i++) {
            float v = v_s[i];
            std::vector<float> v_s_k;

            for (int j = 0; j < actions.size(); j++) {
                // There should be some summation HERE
                v_s_k.push_back(t_probs[i][j] * (rewards[i][j] + (gamma * v)));
            }

            // Get the maximum state value for each action
            auto max_element_iter = std::max_element(v_s_k.begin(), v_s_k.end());
            if (max_element_iter != v_s_k.end()) {
                v_s[i] = *max_element_iter;
            }

            // Check whether new state value is greater than previous state value.
            double d = abs(v - v_s[i]);
            delta = (delta > d ? delta : d);
            std::cout << "D: " << d << "\tDelta: " << delta << "\n";
        }

        //Check for convergence to know whether to stop.
        if (delta < theta) {
            std::cout << "Final Delta: " << delta << "\n";
            break;
        }
        it++;
    }

    // Print Final Optimized Values
    for (auto val : v_s) {
        std::cout << val << "\t";
    }
    std::cout << std::endl;


    return it;
}
