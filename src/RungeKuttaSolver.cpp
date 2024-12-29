#include "RungeKuttaSolver.h"
#include <iostream>
#include <algorithm>
#include <cmath>

// Trim from the start (in place)
void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

// Trim from the end (in place)
void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// Trim from both ends (in place)
void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

// Trim from the start (copying)
std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// Trim from the end (copying)
std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// Trim from both ends (copying)
std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}

RungeKuttaSolver::RungeKuttaSolver()
{
}

// Solves the expression as a string using exprtk. Out vector is set to the result
void RungeKuttaSolver::Solve(const float& y0, const float& h, const float& t, const float& t0, const std::string& expr, std::vector<std::vector<float>>& out)
{
    if (t0 >= t)
    {
        return;
    }

    // Set size of output vector
    const int x = int(std::ceil((t - t0) / h)) + 1;
    out.resize(x, std::vector<float>(2));

    float w = y0;
    float k1, k2, k3, k4;
    float i = t0;
    int index = 0;

    while (i < t)
    {
        out[index] = { i, w };

        k1 = h * dydt<float>(i, w, expr);
        k2 = h * dydt<float>(i + h/2, w + k1/2, expr);
        k3 = h * dydt<float>(i + h/2, w + k2/2, expr);
        k4 = h * dydt<float>(i + h, w + k3, expr);

        w = w + (k1 + k2 + k3 + k4) / 6;

        index++;
        i += h;
    }

}

// Re-prompts with given message for input until a valid float is provided
const float GetValidFloatInput(const std::string msg)
{
    float num;
    while (true)
    {
        std::cout << msg << std::endl;

        if (std::cin >> num)
        {
            break;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid floating-point number.\n";
        }
    }

    return num;
}

// Prints dataset to csv file
void Print(const std::vector<std::vector<float>> dataset)
{
    std::ofstream outFile("solution.csv");

    // Check if the file is open.
    if (outFile.is_open())
    {
        // Write the header.
        outFile << "t,y\n";

        // Write data points as csv
        std::vector<float> point;
        for (size_t i = 0; i < dataset.size(); i++)
        {
            point = dataset[i];
            outFile << point[0] << "," << point[1] << "\n";
        }

        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file";
    }

}

int main()
{
    RungeKuttaSolver rk;

    std::string expr;
    std::cout <<R"(
______ _   __  ___    ___________ _____    _____       _                
| ___ \ | / / /   |  |  _  |  _  \  ___|  /  ___|     | |               
| |_/ / |/ / / /| |  | | | | | | | |__    \ `--.  ___ | |_   _____ _ __ 
|    /|    \/ /_| |  | | | | | | |  __|    `--. \/ _ \| \ \ / / _ \ '__|
| |\ \| |\  \___  |  \ \_/ / |/ /| |___   /\__/ / (_) | |\ V /  __/ |   
\_| \_\_| \_/   |_/   \___/|___/ \____/   \____/ \___/|_| \_/ \___|_|   
                                                                        
 
    )"<< "\n";

    std::cout << "Welcome to the RK4 ODE Solver. This tool solves First Order ODEs using the Runge-Kutta 4th order method." << std::endl;
    std::cout << "Please enter your expression for f(y,t) (e.g. t^2 + y^2)" << std::endl;
    std::cin >> expr;

    // Get valid expression
    while (!rk.IsExpressionValid<float>(expr))
    {
        std::cout << "That expression is invalid, please try again. \nEnter your equation in the form dy/dt = f(y,t) (e.q. t^2+y^2)" << std::endl;
        std::cin >> expr;
    }

    // Get valid parameters for integration
    std::string input;
    float y0 = GetValidFloatInput("Enter a value for initial state (y_0):");
    float t0 = GetValidFloatInput("Enter the start time (t_0):");
    float tf = GetValidFloatInput("Enter the final time (t_f):");
    float h = GetValidFloatInput("Enter the time step (h):");


    std::vector<std::vector<float>> output;
    try
    {
        // Solve and store results
        rk.Solve(y0, h, tf, t0, expr, output);
    }
    catch(std::runtime_error& e)
    {
        std::cout << "An error has occured. Please try again later." << std::endl;
        return 0;
    }
    

    // Display results in prompt
    std::vector<float> entry;
    for (size_t i = 0; i < output.size(); i++)
    {
        entry = output[i];
        std::cout << "t: " << entry[0]<<  "  y: " << entry[1] << std::endl;
    }

    // Determine if we should print to csv
    std::string print;
    while (true)
    {
        std::cout << "Would you like to print results (Y/N):" << std::endl;
        std::cin >> print;
        trim(print);
        if (print == "Y" || print == "y")
        {
            Print(output);
        }
        else if (print == "N" || print == "n")
        {
            break;
        }
    }
    
    return 0;
}


