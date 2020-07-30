/*
 * Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"

static size_t write_cb(void *, size_t, size_t, void *);

int
http_do(struct req *rq)
{
	int ret = -1;

	/* TODO: check if body */
	rq->resp.body = malloc(1);
	rq->resp.bodysz = 0;

	/* set headers */
	/* TODO: check if headers */
	rq->headers = curl_slist_append(rq->headers, HTTP_ACC);
	rq->headers = curl_slist_append(rq->headers, HTTP_CTY);
	if (rq->headers == NULL)
		goto done;

	/* set url */
	HTTP_SET(rq->curl, CURLOPT_URL, rq->url);
	/* set post data */
	HTTP_SET(rq->curl, CURLOPT_POSTFIELDS, (const char *)rq->data);
	/* set user-agent */
	HTTP_SET(rq->curl, CURLOPT_USERAGENT, HTTP_UAG);
	/* send all data to this function  */
	HTTP_SET(rq->curl, CURLOPT_WRITEFUNCTION, write_cb);
	/* we pass our 'chunk' struct to the callback function */
	HTTP_SET(rq->curl, CURLOPT_WRITEDATA, (void *)&rq->resp);

	/* execute request */
	rq->resp.code = curl_easy_perform(rq->curl);
	if (rq->resp.code != CURLE_OK)
		goto done;

	ret = 0;
done:
	return (ret);
}

int
http_seturl(struct req *rq, const char *url)
{
	int ret = 0;
	if (rq == NULL || url == NULL)
		ret = -1;
	if ((rq->url = strdup(url)) == NULL)
		ret = -1;
	return (ret);
}

void
http_free(struct req *rq)
{
	if (rq->headers != NULL)
		curl_slist_free_all(rq->headers);
	if (rq->curl != NULL) {
		curl_easy_cleanup(rq->curl);
		curl_global_cleanup();
	}
	if (rq->resp.body != NULL)
		free(rq->resp.body);
	if (rq->url != NULL)
		free(rq->url);
	memset(rq, 0, sizeof(*rq));
}

int
http_init(struct req *rq)
{
	int ret = 0;

	memset(rq, 0, sizeof(*rq));

	curl_global_init(CURL_GLOBAL_DEFAULT);
	rq->curl = curl_easy_init();
	rq->headers = NULL;

	return (ret);
}

static size_t
write_cb(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct res *mem = (struct res *)userp;

	char *ptr = realloc(mem->body, mem->bodysz + realsize + 1);
	if(ptr == NULL) {
		/* out of body! */
		printf("not enough body (realloc returned NULL)\n");
		return 0;
	}

	mem->body = ptr;
	memcpy(&(mem->body[mem->bodysz]), contents, realsize);
	mem->bodysz += realsize;
	mem->body[mem->bodysz] = 0;

	return realsize;
}
