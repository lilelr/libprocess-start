//
// Created by marcie on 18-11-20.
//

#include <cstdio>
#include <iostream>
#include <cstring>
#include <dmidecode.h>

using std::cout;
using std::endl;

Dmidecode::Dmidecode() {

}
Dmidecode::Dmidecode(shared_ptr<string> size, shared_ptr<string> type, shared_ptr<string> speed){
    m_size = size;
    m_type = type;
    m_speed = speed;
}

shared_ptr<string> Dmidecode::get_size() {
    return m_size;
}

void Dmidecode::set_size(const shared_ptr<string> size) {
    m_size = size;
}

shared_ptr<string> Dmidecode::get_type() {
    return m_type;
}

void Dmidecode::set_type(const shared_ptr<string>type) {
    m_type = type;
}

shared_ptr<string> Dmidecode::get_speed() {
    return m_speed;
}

void Dmidecode::set_speed(const shared_ptr<string>speed) {
    m_speed = speed;
}

Dmidecode::~Dmidecode() {

}

