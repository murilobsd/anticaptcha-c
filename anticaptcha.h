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

#ifndef ANTICAPTCHA_H
#define ANTICAPTCHA_H

struct anticaptcha {
	char		*client_key;
};

int	anti_init(struct anticaptcha *);
void	anti_free(struct anticaptcha *);
int	anti_setkey(struct anticaptcha *, const char *);
float	anti_getbalance(struct anticaptcha *);

/*
int http_init(struct req);
struct resp * http_post(struct req);
void http_free(kkk
*/

#endif /* ANTICAPTCHA_H */
