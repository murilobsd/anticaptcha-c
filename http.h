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

#ifndef HTTP_H
#define HTTP_H

#include <curl/curl.h>

#define HTTP_CTY "Content-Type: application/json"
#define HTTP_ACC "Accept: application/json"
#define HTTP_UAG "anticaptcha-c/0.1"

#define HTTP_SET(x, y, z) do {		\
	curl_easy_setopt(x, y, z);	\
} while(0)

struct res {
	CURLcode	 code;
	long		 status_code;
	char		*body;
	size_t		 bodysz;
};

struct req {
	CURL			*curl;
	char			*url;
	struct curl_slist	*headers;
	struct res		 resp;
	const char		*data;
	size_t			datasz;
};


int	http_init(struct req *);
int	http_seturl(struct req *, const char *);
int	http_do(struct req *);
void	http_free(struct req *);

#endif /* HTTP_H */
