#pragma once
#ifndef __ERROR_PARAM_H__
#define __ERROR_PARAM_H__

#include <cmath>

namespace physlab{
    // Struct for parameter used for error analysis
    struct param{
        double val; // Measured or calculated value of the parameter
        int sig;   // Number of significant digits should be reserved.
    };

    // Declare a variable parameter with given precision.
    #define var_param(value, sig_dig) param{value, sig_dig}

    // Declare a constant parameter, like maths or physics constant, that is considered to be of infinite precision.
    #define const_param(value) param{value, 65535}

    /**
     * @brief Order of magnitude of a parameter. That is, 10^order_of_mag is smaller than its value while 10^(order_of_mag+1) is larger.
     */
    int order_of_mag(param pt);

    /**
     * @brief Number of significant decimal places the parameter has. Could be below zero if sig-digs are less than integer digits.
     * 
     */
    int decimal_places(param pt);

    /**
     * @brief Keep a certain number of decimal digits for a parameter.
     * 
     * @return Resulted parameter value.
     */
    param keep_decimal(param pt, int _dec);

    /**
     * @brief Raw value used in scientific notation.
     * 
     */
    double raw_val(param pt);

    /**
     * @brief Addition of two parameters is clamped at the lesser number of decimal digits.
     */
    param operator+(param _a, param _b);

    /**
     * @brief Subtraction of two parameters is clamped at the lesser number of decimal digits.
     */
    param operator-(param _a, param _b);

    /**
     * @brief Multiplication of two parameters is clamped at the less number of significant digits.
     * 
     */
    param operator*(param _a, param _b);

    /**
     * @brief Division of two parameters is clamped at the less number of significant digits.
     * 
     */
    param operator/(param _a, param _b);

    /**
     * @brief A parameter raised to the power of another parameter is clamped at the less number of significant digits.
     * 
     */
    param pow(param _a, param _b);

    /**
     * @brief Sig. Dig. of sine of a parameter is determined by relative precision.
     */
    param sin(param _a);

    /**
     * @brief Sig. Dig. of cosine of a parameter is determined by relative precision.
     */
    param cos(param _a);

    /**
     * @brief Sig. Dig. of tangent of a parameter is determined by relative precision.
     */
    param tan(param _a);

    /**
     * @brief Sig. Dig. of natural logarithm of a parameter is determined by relative precision.
     */
    param log(param _a);

    /**
     * @brief Sig. Dig. of exponent of a parameter is determined by relative precision.
     */
    param exp(param _a);
}
#endif
