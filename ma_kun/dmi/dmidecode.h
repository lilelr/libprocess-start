//
// Created by marcie on 18-11-20.
//

#ifndef LIBPROCESS_START_DMIDECODE_H
#define LIBPROCESS_START_DMIDECODE_H

#include <iostream>
#include <memory>

using std::shared_ptr;
using std::string;

class Dmidecode{
protected:
    shared_ptr<string> m_size;
    shared_ptr<string> m_type;
    shared_ptr<string> m_speed;
public:
    /*构造函数*/
    Dmidecode();
    explicit Dmidecode(shared_ptr<string> size, shared_ptr<string> type, shared_ptr<string> speed);
    /*自定义拷贝、赋值运算符、移动构造函数*/
    /*Dmidecode(const Dmidecode &dmidecode);
    Dmidecode& operator = (const Dmidecode&);
    Dmidecode(Dmidecode &&dmidecode);*/
    shared_ptr<string> get_size();
    void set_size(const shared_ptr<string> size);
    shared_ptr<string> get_type();
    void set_type(const shared_ptr<string> type);
    shared_ptr<string> get_speed();
    void set_speed(const shared_ptr<string> speed);
    ~Dmidecode();

};
#endif //LIBPROCESS_START_DMIDECODE_H
