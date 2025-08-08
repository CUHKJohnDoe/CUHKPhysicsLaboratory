#pragma once
#ifndef __LABIO_CPP__
#define __LABIO_CPP__
#include "labio.h"

#include <string>
#include <vector>
using namespace physlab;

std::vector<double> physlab::dataOpen(std::string file_dir){
    FILE* file=fopen(file_dir.c_str(), "r+");

    std::vector<double> res;
    double _cur;
    int _size;
    fscanf(file, "%d", &_size);

    for(int i=0;i<_size;++i){
        fscanf(file, "%lf", &_cur);
        res.push_back(_cur);
    }

    fclose(file);
    return res;
}

void physlab::propTable::append(std::string tag, double value, int _precision){
    _tags.push_back(tag);
    _vals.push_back(value);
    _prec.push_back(_precision);
}

void physlab::propTable::writeToMarkdown(std::string file_dir, std::string title_name){
    FILE* _md=fopen(file_dir.c_str(), "w+");
    fprintf(_md, "# %s\n\n", title_name.c_str());

    fprintf(_md, "| Item | Value |\n| --- | --- |\n");
    
    for(int i=0;i<_tags.size();++i){
        fprintf(_md,"| %s | %.*lf |\n", _tags.at(i).c_str(), _prec.at(i), _vals.at(i));
    }

    printf("Property table exported to: %s\n", file_dir.c_str());
    fclose(_md);
}

physlab::spread_sheet::spread_sheet(){
    _cur_tag=-1;
    _max_len=0;
}

bool physlab::spread_sheet::isEmpty(){
    return (_cur_tag==-1);
}

void physlab::spread_sheet::addTag(std::string tag, int _precision){
    _tags.push_back(tag);
    _prec.push_back(_precision);
    std::vector<double> _v;
    _vals.push_back(_v);
    if(_cur_tag==-1){ _cur_tag=0;}
}

void physlab::spread_sheet::switchTo(std::string tag){
    int tag_ind=-1;    // Find index of the designated tag.

    for(int i=0;i<_tags.size();++i){
        if(_tags.at(i)==tag){
            tag_ind=i;
        }
    }
    if(tag_ind==-1){return;}

    _cur_tag=tag_ind;
}

std::string physlab::spread_sheet::nextTag(){
    _cur_tag++;
    _cur_tag%=_tags.size();

    return _tags.at(_cur_tag);
}

void physlab::spread_sheet::append(double val){
    _vals.at(_cur_tag).push_back(val);  // Add an entry to current tag.
    if(_max_len<_vals.at(_cur_tag).size()){
        _max_len=_vals.at(_cur_tag).size();     // Update maximum length of the table.
    }
}

void physlab::spread_sheet::appendTo(std::string tag, double val){
    switchTo(tag);
    append(val);
}

void physlab::spread_sheet::appendAllTo(std::string tag, std::vector<double> vals){
    switchTo(tag);
    for(int i=0;i<vals.size();++i){
        append(vals.at(i));
    }
}

void physlab::spread_sheet::writeToCsv(std::string file_dir){
    FILE* _file=fopen(file_dir.c_str(), "w+");

    // Print head of the spreadsheet containing all tags.
    for(int i=0;i<_tags.size();++i){
        fprintf(_file, "%s,", _tags.at(i).c_str());
    }   fprintf(_file,"\n");

    for(int i=0;i<_tags.size();++i){
        for(int j=0;j<_max_len;++j){
            fprintf(_file, "%.*lf,", _prec.at(i), (j<_vals.at(i).size())?(_vals.at(i).at(j)):(nan("")));
        }   fprintf(_file,"\n");
    }

    fclose(_file);
}

void physlab::spread_sheet::writeToMarkdown(std::string file_dir, std::string title){
    FILE* _file=fopen(file_dir.c_str(), "w+");
    
    fprintf(_file, "# %s\n\n", title.c_str());

    for(int i=0;i<_tags.size();++i){
        fprintf(_file, "| %s ", _tags.at(i).c_str());
    }   fprintf(_file, "|\n");

    for(int i=0;i<_tags.size();++i){
        fprintf(_file, "| ---");
    }   fprintf(_file, "|\n");

    for(int i=0;i<_tags.size();++i){
        for(int j=0;j<_max_len;++j){
            fprintf(_file, "| %.*lf ", _prec.at(i), (j<_vals.at(i).size())?(_vals.at(i).at(j)):(nan("")));
        }   fprintf(_file, "|\n");
    }   fprintf(_file,"\n");

    fclose(_file);
}

physlab::value_query::value_query(std::string hint){
    _hint=hint;
}

double physlab::value_query::doQuery(){
    double _val;
    printf("[QUERY] Input %s.\n>>> ");
    scanf("%lf", &_val);
    delete this;
    return _val;
}

#endif
