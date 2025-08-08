/**
 * @file dscv_stat.h
 * @author William Wang
 * @brief Descriptive statistics library for Physics Laboratory 
 * @date 2024-01-16
 * 
 */
#pragma once
#ifndef __DSCV_STAT_H__
#define __DSCV_STAT_H__

#include <vector>
#include <string>

#include <math.h>

#include "labio.h"
#include "labio.cpp"


namespace physlab{
    // Evaluate mean of an array of data.
    double doMean(std::vector<double> arr);

    // Evaluate standard deviation of an array of data.
    double doStdDev(std::vector<double> arr);

    // Evaluate standard error of an array of data.
    double doStdError(std::vector<double> arr);

    /**
     * @brief Performs descriptive statistics analysis.
     * @brief Menu: Mean, Standard-deviation, Standard-error.
     * 
     * @return physlab::propTable
     * 
     */
    propTable dscv_stats(std::vector<double> arr);
}
#endif
