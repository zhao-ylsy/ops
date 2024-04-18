﻿#ifndef _common_h
#define _common_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#pragma pack(push)  // 保存当前对齐状态
#pragma pack(1)     // 设置一字节对齐
//包类型
enum ops_packet_type
{
    ops_packet_auth = 1,                    //鉴权
    ops_packet_ping,                        //延迟测试和保活
    ops_packet_info,                        //上报信息
    ops_packet_plugin,
    ops_packet_forward,                     //转发服务
    ops_packet_forward_ctl,                 //转发隧道控制包
    ops_packet_forward_data_remote,         //隧道数据
    ops_packet_forward_data_local,
    ops_packet_host,                        //域名转发
    ops_packet_host_ctl,                    //域名转发控制包
    ops_packet_host_data,
    ops_packet_vpc,                         //局域网服务
    ops_packet_vpc_data,
};
//鉴权
#define CTL_AUTH_ERR    0x01                //鉴权失败
#define CTL_AUTH_OK     0x02                //鉴权成功
#define CTL_AUTH_ONLINE 0x03                //鉴权成功,但已在线
//包定义
typedef struct _ops_packet {
    uint8_t type;                           //包类型
    uint32_t stream_id;                     //流ID
    uint32_t service_id;                    //服务编号
    uint8_t data[];                         //数据
}ops_packet;
//转发服务
#define CTL_FORWARD_ADD  0x01                //添加
#define CTL_FORWARD_DEL  0x02                //删除
//转发服务来源
typedef struct _ops_forward_src {
    uint32_t sid;                            //服务编号
    uint8_t type;                            //服务类型,1 TCP, 2 UDP
    uint16_t port;                           //服务监听端口
}ops_forward_src;
//转发服务目标
typedef struct _ops_forward_dst {
    uint32_t sid;                            //服务编号
    uint8_t type;                            //服务类型,1 TCP, 2 UDP
    char bind[256];                          //绑定的本地地址
    uint16_t port;                           //转发的目标端口
    char dst[256];                           //转发的目标地址
}ops_forward_dst;
//域名服务目标
#define CTL_HOST_ADD    0x01                 //添加
#define CTL_HOST_DEL    0x02                 //删除
typedef struct _ops_host_dst {
    uint32_t sid;                            //服务编号
    uint8_t type;                            //服务类型,1 HTTP, 2 HTTPS
    char bind[256];                          //绑定的本地地址
    uint16_t port;                           //转发的目标端口
    char dst[256];                           //转发的目标地址
}ops_host_dst;
//网络成员
#define CTL_MEMBER_ADD  0x01                //添加
#define CTL_MEMBER_DEL  0x02                //删除
typedef struct _ops_member {
    uint16_t vid;                           //VPC编号
    uint32_t id;                            //成员编号
    uint8_t ipv4[4];                        //ipv4地址
    uint8_t prefix_v4;                      //ipv4前缀
    uint8_t ipv6[16];                       //ipv6地址
    uint8_t prefix_v6;                      //ipv6前缀
}ops_member;

#pragma pack(pop)   // 恢复之前的对齐状态
#endif
