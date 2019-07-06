//
//  begin_end_test.h
//  deque_project
//
//  Created by William McCarthy on 10/7/18.
//  Copyright © 2018 William McCarthy. All rights reserved.
//

#ifndef begin_end_test_h
#define begin_end_test_h

#include <iostream>


class begin_end_test {  // class that brackets and names testing function
public:
  begin_end_test(const std::string& function_name_) : function_name_(function_name_) {
    std::cout << "====================================================== Testing "
              << function_name_ << "...\n";
  }
  ~begin_end_test() {
    std::cout << "======================================================... end of Testing "
              << function_name_ << "...\n\n";
  }
private:
  std::string function_name_;
};


#endif /* begin_end_test_h */
