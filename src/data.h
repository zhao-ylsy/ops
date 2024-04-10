#ifndef _data_h
#define _data_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON.h>


typedef void (*data_key_add_cb) (void*, uint16_t id, const char *key);
typedef void (*data_key_del_cb) (void*, const char* key);
typedef void (*data_forward_add_cb)(void*, uint32_t id, uint16_t src_id, uint16_t dst_id, uint8_t type, uint16_t src_port, const char* dst, uint16_t dst_port);
typedef void (*data_forward_del_cb)(void*, uint32_t id);
typedef void (*data_host_add_cb)(void*, uint32_t id, const char* src_host, uint16_t dst_id, uint8_t type, const char* dst, uint16_t dst_port, const char *host_rewrite);
typedef void (*data_host_del_cb)(void*, uint32_t id);
struct data_settings {
    data_key_add_cb on_key_add;
    data_key_del_cb on_key_del;
    data_forward_add_cb on_forward_add;
    data_forward_del_cb on_forward_del;
    data_host_add_cb on_host_add;
    data_host_del_cb on_host_del;
};

int data_init(const char* file, void* userdata, struct data_settings *settings);

cJSON* data_bridge_get();
int data_bridge_add(const char* key, const char* info);
int data_bridge_del(uint16_t id);


cJSON* data_forward_get();
int data_forward_add(int src_id, int dst_id, int type, int src_port, const char* dst, uint16_t dst_port, const char* info);
int data_forward_del(uint32_t id);


cJSON* data_host_get();
int data_host_add(const char* host, int dst_id, int type, const char* dst, uint16_t dst_port, const char* host_rewrite, const char* info);
int data_host_del(uint32_t id);

#endif
