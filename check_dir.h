#include <boost/filesystem.hpp>

using namespace boost::filesystem;


int check_dir(path p){
  std::cout<< p << " is an empty directory ?\n";
  //Test du repertoire
  
  if(!exists(p) ) {
    printf("Invalid path \n");
    return -1;
  }

  if(!is_directory(p) ) {
    printf("Path is not a directory \n");
    return -1;
  }

  if(boost::filesystem::is_empty(p)){
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

std::string make_name(path p, int index, const std::string &extention) {
    std::stringstream ss;
    ss << p.string();
    ss << "/";
    ss << "out_";
    ss << std::setw(5) << std::setfill('0') << index;
    ss << extention;
    std::string s = ss.str();
    return s;
}
