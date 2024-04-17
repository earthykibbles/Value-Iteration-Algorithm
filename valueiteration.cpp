// valueiteration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>

int main()
{
    std::vector<int> states = { 0,1,2,3,4,5,6,7,8,9};
    std::vector<int> actions = { 0,1,2,3 };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    std::uniform_int_distribution<int> dist(-1, 1);

    std::vector<std::vector<float>> t_probs;
    std::vector<std::vector<float>> rewards;

    // Generate Random Transition Probabilities (0.0 - 1.0)
    for (int i = 0; i < states.size(); i++) {
        std::vector<float> t_prob_ph;
        for (int j = 0; j < actions.size(); j++) {
            t_prob_ph.push_back(dis(gen));
        }
        t_probs.push_back(t_prob_ph);
        t_prob_ph.clear();
    }

    // Generate Random Rewards {-1, 0, 1}
    for (int i = 0; i < states.size(); i++) {
        std::vector<float> reward_ph;
        for (int j = 0; j < actions.size(); j++) {
            reward_ph.push_back(dist(gen));
        }
        rewards.push_back(reward_ph);
        reward_ph.clear();
    }

    // Initialize state values for each state
    std::vector<float> v_s = {0,0,0,0,0,0,0,0,0,0};


    // Start the algorithm
    int it = 0;
    double delta = 0;

    double theta = 0.000001;//A very small number that specifies the degree of error and convergence of our algorithm
    double gamma = 0.8; //Discount factor

    while (true) {
        for (int i = 0; i < states.size(); ++i) {
            float v = v_s[i];
            std::vector<float> v_s_k;

            for (int j = 0; j < actions.size(); ++j) {
                v_s_k.push_back(t_probs[i][j] * (rewards[i][j] + (gamma * v_s[i])));
            }

            // Get the maximum state value for each action
            auto max_element_iter = std::max_element(v_s_k.begin(), v_s_k.end());
            if (max_element_iter != v_s_k.end()) {
                v_s[i] = *max_element_iter;
            }

            // Check whether new state value is greater than previous state value.
            double d = abs(v - v_s[i]);

            if (delta > d) {
                delta = d;
            }

            //OR (SIMPLER CODE)
            //delta = (delta > d ? delta : d);

            // You can print each iteration 
            // std::cout << "vs\t" << v_s[i] << "\n";
        }

        //check for convergence to know whether to stop.
        if (delta < theta)
            break;

        it++;
    }


    for (auto val : v_s) {
        std::cout << val << "\n";
    }
    
    return it;
}
