#include "ngx_myjson.h"
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_log.h>

static void ngx_http_myupstream_init();
static char* ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r);
//static void ngx_http_devlogin_process_req(ngx_http_request_t *r)
//static void ngx_recom_handler(ngx_http_request_t *r);
static void get_post_para(ngx_http_request_t *r);
static char *ngx_http_mytest_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_mytest_parse(ngx_http_request_t *r);
static void ngx_http_upstream_process_req(ngx_http_request_t *r);
static ngx_int_t ngx_http_mytest_parse(ngx_http_request_t *r);

static const ngx_str_t const vmrtool_url = ngx_string("/vmrtool");
static const ngx_str_t const devlogin_url = ngx_string("/vmrtool/login");
static const ngx_str_t const devlogout_url = ngx_string("/vmrtool/logout");

static ngx_command_t ngx_http_mytest_commands[] = {
    {
      ngx_string("vmrtool"),
      NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LMT_CONF | NGX_CONF_NOARGS,
      ngx_http_mytest,        // ����mytest������ʱ��ngx_http_mytest����������  
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL,
    },
    ngx_null_command            // ��һ���յ�ngx_command_t��Ϊ��β  
};



static char* ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
  ngx_http_core_loc_conf_t *clcf;

  // �ҵ�mytest���������������ÿ�  
  clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

  // ���ô�������ķ�����HTTP����ڴ����û�������е�NGX_HTTP_CONTENT_PHASE�׶�ʱ  
  // �������������URI��mytestģ���������ÿ�������ͬ���ͻ���ú���ngx_http_mytest_handler  
  clcf->handler = ngx_http_mytest_handler;
  //ngx_log_print(r, "enter ngx_http_mytest");
  return NGX_CONF_OK;
}


static ngx_http_module_t ngx_http_mytest_module_ctx = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};


ngx_module_t ngx_http_mytest_module = {
  NGX_MODULE_V1,      // 0,0,0,0,0,0,1  
  &ngx_http_mytest_module_ctx,
  ngx_http_mytest_commands,
  NGX_HTTP_MODULE,    // ����ģ������  

  /* Nginx���������˳�ʱ���������7���ص����� */
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NGX_MODULE_V1_PADDING,  // 0,0,0,0,0,0,0,0,�����ֶ�  
};



// �����������Ϣ������ngx_http_request_t�ṹ����  
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r)
{
  // ����ķ�������ΪGET����HEAD  
  if (!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD | NGX_HTTP_POST)))
    return NGX_HTTP_NOT_ALLOWED;

  // ���������еİ��� 
  ngx_int_t rc;
 //  ngx_int_t rc = ngx_http_discard_request_body(r);
//   if (rc != NGX_OK)
//     return rc;
  rc = ngx_http_read_client_request_body(r, ngx_http_myupstream_init);
  printf("enter ngx_http_mytest_handler.... \n");
  if (r->method &(NGX_HTTP_POST)) {
    printf("del post.... \n");

    get_post_para(r);
//     ngx_int_t rc = ngx_http_read_client_request_body(r, ngx_recom_handler);
//     if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
//       return rc;
//     }
  }
  //printf("enter uri :%s----------%d\n",r->uri.data,(int)r->uri.len);
  if (ngx_strncmp(r->uri.data, devlogin_url.data, devlogin_url.len) == NGX_OK)
  {
    printf("dev login test........... \n");
  }
  else if (ngx_strncmp(r->uri.data, devlogout_url.data, devlogout_url.len) == NGX_OK)
  {
    printf("dev logout test........... \n");
  }
  else if (ngx_strncmp(r->uri.data, vmrtool_url.data, vmrtool_url.len) == NGX_OK)
  {
    printf("first  test........... \n");
  }
  else
  {
    printf("vmtoll error\n");
  }
  //getLoginInfo("http post parming");
  

  ngx_str_t type = ngx_string("text/plain");
  ngx_str_t response = ngx_string("stone531   hello world");

  // ������Ӧ��HTTPͷ��  
  r->headers_out.status = NGX_HTTP_OK;           // ���ص���Ӧ��  
  r->headers_out.content_length_n = response.len;    // ��Ӧ���峤��  
  r->headers_out.content_type = type;                // Content-Type  

  rc = ngx_http_send_header(r); // ����HTTPͷ��  
  if (rc == NGX_ERROR || rc > NGX_OK || r->header_only)
    return rc;

  // �����Ӧ���������壬���ڴ˴�����ֱ�ӷ���rc  

  // ������Ӧ����ռ䣬��Ϊ���첽���ͣ����Բ�Ҫ��ջ�л�ÿռ�  
  ngx_buf_t *b = ngx_create_temp_buf(r->pool, response.len);

  if (b == NULL)
    return NGX_HTTP_INTERNAL_SERVER_ERROR;

  ngx_memcpy(b->pos, response.data, response.len);
  b->last = b->pos + response.len;  // ָ������ĩβ  
  b->last_buf = 1;                    // �����������һ�黺����  

  ngx_chain_t out;
  out.buf = b;
  out.next = NULL;

  return ngx_http_output_filter(r, &out);   // ���û�������Ӧ��  
}

static void get_post_para(ngx_http_request_t *r)
{
  //TODO
  printf("ent get_post_para \n");
  if (r->request_body == NULL)
  {
    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "reqeust_body:null");
    return ;
  }
  ngx_chain_t* bufs = r->request_body->bufs;
  ngx_buf_t* buf = NULL;
  uint8_t* data_buf = NULL;
  size_t content_length = 0;
  size_t body_length = 0;

  if (r->headers_in.content_length == NULL)
  {
    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "r->headers_in.content_length == NULL");
    return ;
  }

  // malloc space for data_buf
  content_length = atoi((char*)(r->headers_in.content_length->value.data));
  data_buf = (uint8_t*)ngx_palloc(r->pool, content_length + 1);
  size_t buf_length = 0;
  while (bufs)
  {
    buf = bufs->buf;
    bufs = bufs->next;
    buf_length = buf->last - buf->pos;
    if (body_length + buf_length > content_length)
    {
      memcpy(data_buf + body_length, buf->pos, content_length - body_length);
      body_length = content_length;
      break;
    }
    memcpy(data_buf + body_length, buf->pos, buf->last - buf->pos);
    body_length += buf->last - buf->pos;
  }
  if (body_length)
  {
    data_buf[body_length] = 0;
  }

  printf("lrl >>>content :%s\n", (char *)data_buf);
  return ;
}


static void ngx_http_myupstream_init()
{
  printf("lrl ngx_http_myupstream_init\n");
}


//  ___________________________convert post___________________
static void ngx_http_upstream_process_req(ngx_http_request_t *r)
{
//   ngx_str_t arg;
//   ngx_myqq_t *myqq = ngx_http_get_module_ctx(r, ngx_http_myqq_module);
// 
//  if (ngx_strncmp(r->uri.data, login_url.data, login_url.len) == NGX_OK)
//   {
//     ngx_http_myqq_process_login(r, &arg);
//     return;
//   }
//   else
//   {
//     ngx_log_print(r, "not url");
//     ngx_http_finalize_request(r, NGX_HTTP_NOT_ALLOWED);
//     return;
//   }

}

static ngx_int_t ngx_http_mytest_parse(ngx_http_request_t *r)
{
//   ngx_int_t rc;
//   ngx_myqq_t *myqq = ngx_http_get_module_ctx(r, ngx_http_myqq_module);
// 
//   if (myqq == NULL)
//   {
//     ngx_log_print(r, "is login error.");
//     return NGX_HTTP_NOT_ALLOWED;
//   }
// 
//   rc = ngx_http_read_client_request_body(r, ngx_http_upstream_process_req);
// 
//   if (rc >= NGX_HTTP_SPECIAL_RESPONSE)
//     return rc;

  return NGX_DONE;
}

static char *ngx_http_mytest_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
//   ngx_http_core_loc_conf_t *clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
//   ngx_http_myqq_loc_t *myqq = conf;
//   ngx_url_t url;
//   ngx_str_t *values;
// 
//   if (clcf->name.data[clcf->name.len - 1] == '/')
//     clcf->auto_redirect = 1;
// 
//   clcf->handler = ngx_http_myqq_parse;
//   values = (ngx_str_t *)cf->args->elts;
// 
//   url.no_resolve = 1;
//   url.url = values[1];
// 
//   myqq->upstream.upstream = ngx_http_upstream_add(cf, &url, 0);
// 
//   if (myqq->upstream.upstream == NULL)
//     return NGX_CONF_ERROR;

  return NGX_CONF_OK;
}