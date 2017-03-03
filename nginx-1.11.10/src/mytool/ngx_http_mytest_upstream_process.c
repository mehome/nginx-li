/*
* ngx_http_mytest_upstream_process.c
*
*  Created on: 2017.03.03
*      Author: stone531
*/

#include "ngx_myjson.h"
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_log.h>
#include <stdio.h>

static ngx_int_t ngx_http_mytest_create_request(ngx_http_request_t *r);
static ngx_int_t ngx_http_mytest_reinit_request(ngx_http_request_t *r);
static ngx_int_t ngx_http_mytest_process_header(ngx_http_request_t *r);
static void ngx_http_mytest_abort_request(ngx_http_request_t *r);
static void ngx_http_mytest_finalize_request(ngx_http_request_t *r, ngx_int_t rc);

static ngx_int_t ngx_http_mytest_input_filter_init(void *data);
static ngx_int_t ngx_http_mytest_input_filter(void *data, ssize_t bytes);

void ngx_http_mytest_upstream_process(ngx_http_request_t *r, ngx_str_t *cmd)
{

  printf("ngx_http_mytest_upstream_process   \n");
//   ngx_http_upstream_t *u;
//   ngx_http_myqq_loc_t *conf;
// 
//   conf = ngx_http_get_module_loc_conf(r, ngx_http_myqq_module);
// 
//   if (ngx_http_set_content_type(r) != NGX_OK)
//   {
//     ngx_log_print(r, "set content type error.");
//     ngx_http_finalize_request(r, NGX_HTTP_NOT_ALLOWED);
//     return;
//   }
// 
//   if (ngx_http_upstream_create(r) != NGX_OK)
//   {
//     ngx_log_print(r, "upstream create error.");
//     ngx_http_finalize_request(r, NGX_HTTP_NOT_ALLOWED);
//     return;
//   }
// 
//   u = r->upstream;
// 
//   ngx_str_set(&u->schema, "myqq://");
//   u->output.buf = (ngx_buf_tag_t)&ngx_http_myqq_module;
//   u->conf = &conf->upstream;
// 
//   u->create_request = ngx_http_myqq_create_request;
//   u->reinit_request = ngx_http_myqq_reinit_request;
//   u->process_header = ngx_http_myqq_process_header;
//   u->abort_request = ngx_http_myqq_abort_request;
//   u->finalize_request = ngx_http_myqq_finalize_request;
// 
//   u->input_filter_ctx = r;
//   u->input_filter_init = ngx_http_myqq_input_filter_init;
//   u->input_filter = ngx_http_myqq_input_filter;
//   r->request_body_no_buffering = 1;
// 
//   ngx_http_upstream_init(r);
  return;
}

static ngx_int_t ngx_http_mytest_create_request(ngx_http_request_t *r)
{
//   ngx_chain_t *out;
//   ngx_buf_t *b;
//   myqq_header_t *header;
//   ngx_http_upstream_t *u;
// 
//   ngx_myqq_t *myqq = ngx_http_get_module_ctx(r, ngx_http_myqq_module);
// 
//   u = r->upstream;
//   out = ngx_alloc_chain_link(r->pool);
//   b = ngx_create_temp_buf(r->pool, sizeof(*header) + r->args.len);
// 
//   if (out == NULL || b == NULL)
//   {
//     ngx_log_print(r, "no memory.");
//     return NGX_ERROR;
//   }
// 
//   b->last += sizeof(*header) + r->args.len;
// 
//   header = (myqq_header_t *)b->pos;
// 
//   header->args_len = r->args.len;
//   ngx_memcpy(header->args, r->args.data, r->args.len);
//   header->len = r->headers_in.content_length_n;
// 
//   ngx_memcpy(header->uri, r->uri.data, r->uri.len);
//   ngx_memcpy(header->id, myqq->id, sizeof(myqq->id));
// 
//   out->buf = b;
//   out->next = NULL;
// 
//   u->request_bufs = out;

  return NGX_OK;
}

static ngx_int_t ngx_http_mytest_reinit_request(ngx_http_request_t *r)
{
  ngx_log_print(r, "reinit request");
  return NGX_OK;
}

static ngx_int_t ngx_http_mytest_process_header(ngx_http_request_t *r)
{
//   ngx_http_upstream_t *u = r->upstream;
//   ngx_buf_t *b = &u->buffer;
//   myqq_header_t *header;
// 
//   if (b->last - b->pos < (off_t)sizeof(*header))
//     return NGX_AGAIN;
// 
//   header = (myqq_header_t *)b->pos;
//   b->pos += sizeof(*header);
// 
//   u->headers_in.status_n = NGX_HTTP_OK;
//   u->headers_in.content_length_n = header->len;
//   u->state->status = NGX_HTTP_OK;
//   ngx_str_set(&r->headers_out.content_type, "text/plain");

  return NGX_OK;
}

static void ngx_http_mytest_abort_request(ngx_http_request_t *r)
{
  ngx_log_print(r, "myqq exec abort request");
}

static void ngx_http_mytest_finalize_request(ngx_http_request_t *r, ngx_int_t rc)
{
  ngx_log_print(r, "myqq finalize request error");
}

static ngx_int_t ngx_http_mytest_input_filter_init(void *data)
{
//   ngx_http_request_t *r = data;
//   ngx_http_upstream_t *u = r->upstream;
// 
//   if (u->headers_in.status_n != NGX_HTTP_NOT_FOUND)
//   {
//     u->length = u->headers_in.content_length_n;
//   }
//   else
//   {
//     u->length = 0;
//   }

  return NGX_OK;
}

static ngx_int_t ngx_http_mytest_input_filter(void *data, ssize_t bytes)
{
//   ngx_http_request_t   *r = data;
// 
//   ngx_buf_t            *b;
//   ngx_chain_t          *cl, **ll;
//   ngx_http_upstream_t  *u;
// 
//   u = r->upstream;
// 
//   for (cl = u->out_bufs, ll = &u->out_bufs; cl; cl = cl->next) {
//     ll = &cl->next;
//   }
// 
//   cl = ngx_chain_get_free_buf(r->pool, &u->free_bufs);
//   if (cl == NULL) {
//     return NGX_ERROR;
//   }
// 
//   *ll = cl;
// 
//   cl->buf->flush = 1;
//   cl->buf->memory = 1;
// 
//   b = &u->buffer;
// 
//   cl->buf->pos = b->last;
//   b->last += bytes;
//   cl->buf->last = b->last;
//   cl->buf->tag = u->output.tag;
// 
//   if (u->length == -1) {
//     return NGX_OK;
//   }
// 
//   u->length -= bytes;
// 
//   if (u->length == 0) {
//     u->keepalive = !u->headers_in.connection_close;
  }

  return NGX_OK;
}
