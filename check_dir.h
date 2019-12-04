#include <boost/filesystem.hpp>


int check_dir(const boost::filesystem::path &p);


std::string make_name(const boost::filesystem::path &p,
                      const int index, const std::string &extention);
