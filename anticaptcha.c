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

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "anticaptcha.h"

float
anti_getbalance(struct anticaptcha *ant)
{
	const char	*url = "https://api.anti-captcha.com/getBalance";
	const char	*data = "{\"clientKey\" : \"%s\"}";
	char		 post_data[150];
	int		 res = 0;
	float		 ret = -1.0;

	memset(post_data, 0, sizeof(post_data));

	res = snprintf(post_data, sizeof(post_data), data, ant->client_key);
	if (res < 0 || res >= sizeof(post_data))
		return ret;

	/* TODO: get response and parse */
	curl_easy_setopt(ant->curl, CURLOPT_URL, url);
	curl_easy_setopt(ant->curl, CURLOPT_POSTFIELDS, (const char *)post_data);
	curl_easy_perform(ant->curl);

	ret = 0.0;

	return (ret);
}

int
anti_setkey(struct anticaptcha *ant, const char *key)
{
	int ret = -1;

	if (ant == NULL || key == NULL)
		goto done;
	if ((ant->client_key = strdup(key)) == NULL)
		goto done;
	ret = 0;

done:
	return (ret);
}

int
anti_init(struct anticaptcha *ant)
{
	int ret = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	ant->curl = curl_easy_init();
	ant->client_key = NULL;

	return (ret);
}


void
anti_free(struct anticaptcha *ant)
{
	if (ant == NULL)
		return;
	if (ant->client_key != NULL)
		free(ant->client_key);
	if (ant->curl != NULL) {
		curl_easy_cleanup(ant->curl);
		curl_global_cleanup();
	}
	memset(ant, 0, sizeof(*ant));
}
