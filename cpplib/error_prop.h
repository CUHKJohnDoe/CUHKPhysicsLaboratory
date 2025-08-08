/**
 * @file error_prop.h
 * @author exomechs@yharim.org
 * @brief Propagation of Error Analysis
 * @version 0.1
 * @date 2024-01-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#ifndef __ERROR_PROP_H__
#define __ERROR_PROP_H__


#include <vector>
#include <string>
#include <functional>
#include <cmath>


#include "error_param.h"
#include "error_param.cpp"

// Used to estimate gradient. Can be set larger to reduce calculation time, or smaller for better accuracy accuracy.
#define PARTIAL_APPROX_PRECISION 0.0000001

namespace physlab{


    /**
     * @brief Error propagation algebraic system.
     *  Used to analyze error of abstractly any R_n -> R algebraic function 
     *  that could be determined output value given a set of input with uncertainty.
     * 
     */
    class error_prop{
        private:
        int x_size;     // Number of independent variables.
        std::vector<std::string> x_names;   // Names of independent variables.
        std::vector<param> x_vals;     // Measured values as assigned to independent variables.
        std::vector<double> err_vals;   // Errors associated with independent variables.
        std::string y_name; // Name of the dependent variable, or output.

        std::function <param(std::vector<param>)> _calc;

        public:
        /**
         * @brief Initialize the algebraic system.
         * 
         * @param func_name Name of the function whose uncertainty needs evaluation.
         * @param dims Number of independent variables.
         */
        error_prop(std::string func_name, std::function<param(std::vector<param>)> algebriac);

        /**
         * @brief Declare a variable's name, current value, and error.
         * 
         * @param name 
         * @param value 
         * @param err 
         */
        void declare(std::string name, param value, double err);

        /**
         * @brief Reassign a value to an existing param-name, retaining its error. 
         *  Normally used when a batch of data are obtained using the same measurements so that error is generally constant.
         * 
         * @param name 
         * @param value 
         * @return Index of the re-assigned input variable.
         */
        int reassign(std::string name, param value);

        /**
         * @brief Reassign a value and its error to an existing param-name.
         * 
         * @param name 
         * @param value 
         * @param err 
         * @return Index of the re-assigned input variable.
         */
        int reassign(std::string name, param value, double err);

        /**
         * @brief Evaluate output from given input values regardless of how values of independent variables are first assigned.
         * 
         * @param custom_input 
         * @return double 
         */
        param evaluate_custom(std::vector<param> custom_input);

        /**
         * @brief Evaluate output from set input values.
         * 
         * @param input 
         * @return double 
         */
        param evaluate();

        /**
         * @brief Assign a console-input value to an independent variable with specified name.
         * 
         * @param param_name 
         */
        void read_param(std::string param_name);

        /**
         * @brief Estimate partial derivative of the output with respect to a given input
         * 
         * @param x_des Name of the designated input value.
         * @return double 
         */
        double partial(int _des);

        /**
         * @brief Do error propagation from inputs to the output.
         * 
         *  The propgator first approximates the function as linearly and uniformly increasing on the direction, as well as by the magnitude
         *  of its gradient at the given inputs (thus its crucial to set those right in the first place), then displace all inputs by their 
         *  maximum of errors respectively
         * 
         * @return double 
         */
        double propagated_error();

        void print_error_prop_result();
    };
};
#endif
