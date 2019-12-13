//
// Created by laurent on 04/12/2019.
//

#ifndef CHAINSAW_CUT_CHECK_DIR_H
#define CHAINSAW_CUT_CHECK_DIR_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "check_dir.h"

using namespace boost::filesystem;

int check_dir(const path &p) {
    std::cout << p << " is an empty directory ?\n";
    //Test du repertoire

    if (!exists(p)) {
        printf("Invalid path \n");
        return -1;
    }

    if (!is_directory(p)) {
        printf("Path is not a directory \n");
        return -1;
    }

    if (boost::filesystem::is_empty(p)) {
        std::cout << " is empty. It's all good men !" << std::endl;
        return 1;
    } else {
        std::cout << p << " is a directory containing:\n";

        for (directory_entry &x : directory_iterator(p))
            std::cout << "    " << x.path() << '\n';
        std::cout << "Should we delete it ?" << std::endl;
        return -1;
    }
}

std::string make_name(const boost::filesystem::path &p, const int index, const std::string &extention) {
    std::stringstream ss;
    ss << p.string();
    ss << "/";
    ss << "out_";
    ss << std::setw(5) << std::setfill('0') << index;
    ss << extention;
    std::string s = ss.str();
    return s;
}

#endif //CHAINSAW_CUT_CHECK_DIR_H