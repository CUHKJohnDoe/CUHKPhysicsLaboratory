#pragma once
#ifndef __DSCV_STAT_CPP__
#define __DSCV_STAT_CPP__
#include "dscv_stat.h"


double physlab::doMean(std::vector<double> arr){
    double sum=0.0;
    for(int i=0;i<arr.size();++i){
        sum+=arr.at(i);
    }

    return sum/(double)(arr.size());
}

double physlab::doStdDev(std::vector<double> arr){
    double _mean=physlab::doMean(arr);
    double _sum=0.0;

    for(int i=0;i<arr.size();++i){
        _sum+=( arr.at(i)-_mean )*( arr.at(i)-_mean );
    }

    return sqrt(_sum/(double)(arr.size()-1));
}

double physlab::doStdError(std::vector<double> arr){
    return doStdDev(arr)/sqrt((double)arr.size());
}


propTable physlab::dscv_stats(std::vector<double> arr){
    physlab::propTable _table;
    
    _table.append("Mean", doMean(arr));
    _table.append("Standard Deviation", doStdDev(arr));
    _table.append("Standard Error", doStdError(arr), 2*GLOBAL_PREC_DIGITS);

    return _table;
}

#endif
