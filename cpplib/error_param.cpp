#pragma once
#ifndef __ERROR_PARAM_CPP__
#define __ERROR_PARAM_CPP__


int physlab::order_of_mag(physlab::param pt){
    if(pt.val<0){return order_of_mag(var_param(-pt.val,pt.sig));}
    return ( (pt.val>1.0)?(log10(pt.val)):(log10(pt.val)-1) );
}

int physlab::decimal_places(physlab::param pt){
    int _ord=order_of_mag(pt);   // order of magnitude.
    int raw_places=pt.sig-_ord-1;  // Count decimal places from [_ord] for [pt.sig] steps.
    return raw_places;
}

physlab::param physlab::keep_decimal(physlab::param pt, int _dec){
    int _pre_dec=decimal_places(pt);
    return physlab::param{pt.val, pt.sig-(_pre_dec-_dec)};
}

double physlab::raw_val(physlab::param pt){
    double _ori=pt.val/std::pow(10.0,order_of_mag(pt));
    double _clamped=std::round(_ori*std::pow(10.0, pt.sig-1)) / std::pow(10.0, pt.sig-1);
    return _clamped;
}

physlab::param physlab::operator+(physlab::param _a, physlab::param _b){
    int a_deci=decimal_places(_a);
    int b_deci=decimal_places(_b);
    int com_deci=(a_deci>b_deci)?b_deci:a_deci;  // Reserve common decimal places as minimum decimal places of the two.
    physlab::param _res=_a;
    _res.val+=_b.val;

    return keep_decimal(_res, com_deci);
}

physlab::param physlab::operator-(physlab::param _a, physlab::param _b){
    return _a+var_param(-_b.val,_b.sig);
}

physlab::param physlab::operator*(physlab::param _a, physlab::param _b){
    int com_sig=(_a.sig>_b.sig)?(_b.sig):(_a.sig);
    return var_param(_a.val*_b.val, com_sig);
}

physlab::param physlab::operator/(physlab::param _a, physlab::param _b){
    int com_sig=(_a.sig>_b.sig)?(_b.sig):(_a.sig);
    return var_param(_a.val/_b.val, com_sig);
}

physlab::param physlab::pow(physlab::param _a, physlab::param _b){
    int com_sig=(_a.sig>_b.sig)?(_b.sig):(_a.sig);
    double res_val=std::pow(_a.val, _b.val);
    return var_param(res_val, com_sig);
}

physlab::param physlab::sin(physlab::param _a){
    double _rel; // Relative precision: (d[sin _a]/d[_a])*([_a]/sin[_a])
    _rel=std::cos(_a.val)*(_a.val)/std::sin(_a.val);
    
    int _loss=order_of_mag(const_param(_rel));
    return var_param(std::sin(_a.val), _a.sig-_loss);
}

physlab::param physlab::cos(physlab::param _a){
    double _rel; // Relative precision: (d[cos _a]/d[_a])*([_a]/cos[_a])
    _rel=-_a.val*std::tan(_a.val);

    int _loss=order_of_mag(const_param(_rel));
    return var_param(std::cos(_a.val), _a.sig-_loss);
}

physlab::param physlab::tan(physlab::param _a){
    double _rel; // Relative precision: (d[tan _a]/d[_a])*([_a]/cos[_a])
    _rel=( std::tan(_a.val)*std::tan(_a.val) +1 ) * _a.val / std::tan(_a.val);

    int _loss=order_of_mag(const_param(_rel));
    return var_param(std::tan(_a.val), _a.sig-_loss);
}

physlab::param physlab::log(physlab::param _a){
    double _rel; // Relative precision: (d[log _a]/d[_a])*([_a]/log[_a])
    _rel=1.0/(std::log(_a.val));

    int _loss=order_of_mag(const_param(_rel));
    return var_param(std::log(_a.val), _a.sig-_loss);
}

physlab::param physlab::exp(physlab::param _a){
    double _rel;
    _rel=_a.val;

    int _loss=order_of_mag(const_param(_rel));
    return var_param(std::exp(_a.val), _a.sig-_loss);
}
#endif
