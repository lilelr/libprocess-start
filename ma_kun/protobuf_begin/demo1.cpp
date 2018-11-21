#include <iostream>
#include <SearchRequest.pb.h>

int main() {
    SearchRequest s;
    s.set_query("ee");
    std::cout<<s.query()<<std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}