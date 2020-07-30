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
#include <string.h>

#include "anticaptcha.h"
#include "http.h"

int
anti(void)
{
	float			 balance = 0;
	struct anticaptcha	 ant;
	int			 ret = 1;

	/* Get key https://anti-captcha.com/panel/settings/account */
	const char		*mykey = "my_key";

	if (anti_init(&ant) == 1)
		goto done;
	/* set client key */
	if (anti_setkey(&ant, mykey) == -1)
		goto done;
	/* get balance */
	if ((balance = anti_getbalance(&ant)) < 0)
		goto done;

	printf("My balance: %.2f\n", balance);
	ret = 0;

done:
	anti_free(&ant);
	return (ret);

}

int
main(void)
{
	struct req rq;
	const char *json_obj = "{\"clientKey\" : \"test\"}";
	http_init(&rq);
	http_seturl(&rq, "https://httpbin.org/post");
	http_setdata(&rq, json_obj);
	http_do(&rq);
	if (rq.resp.bodysz > 0)
		printf("%s\n", rq.resp.body);
	http_free(&rq);
	return (0);
}
