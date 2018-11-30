//
// Created by zyx on 18-11-21.
//

#include "GpuClass.h"

GpuClass::GpuClass(string description, string product, string vendor, string physical_id, string bus_info,
                   string version, string width, string clock, string capabilities, string configuration,
                   string resources) : m_description(description),m_product(product),m_vendor(vendor),m_physical_id(physical_id),
                   m_bus_info(bus_info), m_version(version),m_width(width),m_clock(clock),m_capabilities(capabilities),
                   m_configuration(configuration),m_resources(resources){

}

void GpuClass::set_description(string description) {
    m_description = description;
}

string GpuClass::get_description() {
    return m_description;
}

void GpuClass::set_product(string product) {
    m_product = product;
}

string GpuClass::get_product() {
    return m_product;
}

void GpuClass::set_vendor(string vendor) {
    m_vendor =  vendor;
}

string GpuClass::get_vendor() {
    return m_vendor;
}

void GpuClass::set_physical_id(string physical_id) {
    m_physical_id = physical_id;
}

string GpuClass::get_physical_id() {
    return m_physical_id;
}

void GpuClass::set_bus_info(string bus_info) {
    m_bus_info = bus_info;
}

string GpuClass::get_bus_info() {
    return m_bus_info;
}

void GpuClass::set_version(string version) {
    m_version = version;
}

string GpuClass::get_version() {
    return m_version;
}

void GpuClass::set_width(string width) {
    m_width = width;
}

string GpuClass::get_width() {
    return m_width;
}

void GpuClass::set_clock(string clock) {
    m_clock = clock;
}

string GpuClass::get_clock() {
    return m_clock;
}

void GpuClass::set_capabilities(string capabilities) {
    m_capabilities = capabilities;
}

string GpuClass::get_capabilities() {
    return m_capabilities;
}

void GpuClass::set_configuration(string configuration) {
    m_configuration = configuration;
}

string GpuClass::get_configuration() {
    return m_configuration;
}

void GpuClass::set_resources(string resources) {
    m_resources= resources;
}

string GpuClass::get_resources() {
    return m_resources;
}
