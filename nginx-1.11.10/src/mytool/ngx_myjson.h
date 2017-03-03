/*
* ngx_myjson.h
*
*  Created on: 2017.03.02
*      Author: lrl
*/

#ifndef NGX_MYJSON_H_
#define  NGX_MYJSON_H_

#ifdef __cplusplus
extern "C" {
#endif

 #include <ngx_config.h>
 #include <ngx_core.h>
 #include <ngx_http.h>


  typedef struct
  {
    char devip[100];
    int  devPort;
    char username[100];
    char passwd[100];
  }login_info;
 // extern ngx_module_t ngx_http_myqq_module;
  login_info* getLoginInfo(const char *sp);
  //extern void ngx_http_myqq_process_login(ngx_http_request_t *r, ngx_str_t *cmd);
  extern void ngx_http_mytest_upstream_process(ngx_http_request_t *r, ngx_str_t *cmd);


#ifdef __cplusplus
}
#endif

#endif 

