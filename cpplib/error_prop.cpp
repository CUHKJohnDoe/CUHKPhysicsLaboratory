#pragma once
#ifndef __ERROR_PROP_CPP__
#define __ERROR_PROP_CPP__
#include "error_prop.h"
using namespace physlab;

physlab::error_prop::error_prop(std::string func_name, std::function<param(std::vector<param>)> algebriac){
    y_name=func_name;
    x_size=0;

    _calc=algebriac;
}

void physlab::error_prop::declare(std::string name, param value, double err){
    x_names.push_back(name);
    x_vals.push_back(value);
    err_vals.push_back(err);
    x_size++;
}

int physlab::error_prop::reassign(std::string name, param value){
    int _ind=-1;
    for(int i=0;i<x_names.size();++i){
        if(x_names.at(i)==name){
            _ind=i;
            break;
        }
    }
    if(_ind==-1){return -1;}

    x_vals.at(_ind)=value;
    return _ind;
}

int physlab::error_prop::reassign(std::string name, param value, double error){
    int _ind=this->reassign(name, value);

    err_vals.at(_ind)=error;
    return _ind;
}

param physlab::error_prop::evaluate_custom(std::vector<param> custom_input){
    return _calc(custom_input);
}

physlab::param physlab::error_prop::evaluate(){
    return _calc(this->x_vals);
}

void physlab::error_prop::read_param(std::string param_name){
    double _val, _err;
    int _digits;
    printf("%s = ", param_name.c_str());
    scanf("%lf", &_val);

    printf("Error(%s) = ", param_name.c_str());
    scanf("%lf", &_err);

    printf("Number of Sig. Digs: ", param_name.c_str());
    scanf("%d", &_digits);
    this->declare(param_name, var_param(_val, _digits), _err);
}   

double physlab::error_prop::partial(int _des){
    double _cur=evaluate().val; // Evaluate the original output value.
    std::vector<param> param_list(x_vals); // Clone the list of inputs.

    param_list.at(_des).val+=PARTIAL_APPROX_PRECISION;     // Displace only the designated input by a very small amount. (To estimate partial-x)
    double _displaced=evaluate_custom(param_list).val;      // Evaluate the output value using displaced inputs.
    double _deviat=_displaced-_cur;     // Evaluated the displacement of output as a result of that of inputs. (To estimate partial-y)
    return(_deviat/PARTIAL_APPROX_PRECISION);    // Estimation of dy/dx.

}

double physlab::error_prop::propagated_error(){
    double _sum=0.0;
    std::vector<double> _grad; // Stores approximated gradient.
    for(int i=0;i<x_size;++i){
        _grad.push_back(partial(i));
    }

    // Print the input values.
    printf("[PROPAGATION OF ERROR] Given input values:\n");
    for(int i=0;i<x_size;++i){
        printf("[%d]%s = %.9lf\n", i, x_names.at(i).c_str(), x_vals.at(i).val);
    }

    // Print the gradient.
    printf("[PROPAGATION OF ERROR] Gradient of output at given input values evaluated as below:\n");
    for(int i=0;i<_grad.size();++i){
        printf("[%d](partial)%s/(partial)%s = %.9lf\n", i, y_name.c_str(), x_names.at(i).c_str(), _grad.at(i));
    }

    printf("[PROPAGATION OF ERROR] Error(s) of input values:\n");
    for(int i=0;i<x_size;++i){
        printf("[%d]Error(%s) = %.9lf\n", i, x_names.at(i).c_str(), err_vals.at(i));
    }

    // Squared dot product of (gradient of function value at given input) and (error vector of given input).
    for(int i=0;i<x_size;++i){
        _sum+=err_vals.at(i)*err_vals.at(i)*_grad.at(i)*_grad.at(i);
    }
    printf("[PROPAGATION OF ERROR] Error(%s) = || vec(Input-Error) o vec(Gradient) ||\n", y_name.c_str());

    // Propagated error is the modulus of gradient dot error.
    return sqrt(_sum);
}

void physlab::error_prop::print_error_prop_result(){
    param y_val=evaluate();
    double y_err=propagated_error();

    printf("%s >>> (%.*lf +- %.*lf) * 10^%d\n", 
            y_name.c_str(),
            y_val.sig-1,
            physlab::raw_val(y_val),
            y_val.sig-1,
            round(y_err/std::pow(10.0,physlab::order_of_mag(y_val))*std::pow(10.0,y_val.sig-1))/std::pow(10.0,y_val.sig-1),
            physlab::order_of_mag(y_val));

}

#endif
