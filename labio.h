/**
 * @file labio.h
 * @author William Wang
 * @brief Support for lab-data I-O.
 * @date 2024-01-16
 */
#pragma once
#ifndef __LABIO_H__
#define __LABIO_H__

#include <vector>
#include <string>
#include <cmath>

#define GLOBAL_PREC_DIGITS 4

namespace physlab{

    /**
     * @brief Open a file and read a row of data.
     * 
     * @param file_dir Directory of the file from the executable.
     * @return std::vector<double> 
     */
    std::vector<double> dataOpen(std::string file_dir);

    /**
     * @brief Property table. e.g.
     *      Mean    0.70
     *      Median  0.63
     *      Mode    0.68
     *      etc.
     */
    class propTable{
        private: 
        std::vector<std::string> _tags; // Tags
        std::vector<double> _vals;  // Values
        std::vector<int> _prec;     // Precisions.

        public:
        
        /**
         * @brief Adds a property along with its value.
         * @param _precision Number of decimal places that should be kept. The value is 4 by default and can be toggled in @a labio.h
         * 
         */
        void append(std::string tag, double value, int _precision=GLOBAL_PREC_DIGITS);

        // Print the table to a markdown file.
        void writeToMarkdown(std::string file_dir, std::string title_name);
    };

    class spread_sheet{
        private:
        std::vector<std::string> _tags;     // Description of something each column of values represent.
        std::vector<int> _prec;     // Number of decimal places of each column's values.
        std::vector<std::vector<double>> _vals;     // Entries of the spreadsheet.
        int _cur_tag;   // Current tag.
        int _max_len;   // Number of entries the longest tag has.

        public: 
        spread_sheet();

        /**
         * @brief Whether the spread-sheet is empty.
         * 
         * @return true 
         * @return false 
         */
        bool isEmpty();

        /**
         * @brief Append a column with a tag to the spreadsheet.
         * 
         * @param tag 
         */
        void addTag(std::string tag, int _precision=GLOBAL_PREC_DIGITS);

        /**
         * @brief Forcibly switch to a column of the spreadsheet.
         * 
         * @param tag 
         */
        void switchTo(std::string tag);

        /**
         * @brief Switch to the next tagged column. Return the name of the column after switching.
         * 
         * @return std::string 
         */
        std::string nextTag();

        /**
         * @brief Append an entry under the current tag.
         * 
         * @param val 
         */
        void append(double val);

        /**
         * @brief Forcibly switch to and append an entry under another tag.
         * 
         * @param tag 
         * @param val 
         */
        void appendTo(std::string tag, double val);

        /**
         * @brief Forcibly switch to and append a series of entries under another tag.
         * 
         * @param tag 
         * @param vals 
         */
        void appendAllTo(std::string tag, std::vector<double> vals);

        /**
         * @brief Export the spread-sheet using .csv format.
         * 
         * @param file_dir 
         */
        void writeToCsv(std::string file_dir);

        /**
         * @brief Export the spread-sheet using .md markdown table format.
         * 
         * @param file_dir 
         */
        void writeToMarkdown(std::string file_dir, std::string title);
    };

    /**
     * @brief Class for panel request of a double value.
     * 
     */
    class value_query{
        std::string _hint;
        public:
        value_query(std::string hint);

        double doQuery();
    };
}

#endif