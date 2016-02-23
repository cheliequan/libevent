/*
 * Copyright (c) 2000-2007 Niels Provos <provos@citi.umich.edu>
 * Copyright (c) 2007-2012 Niels Provos and Nick Mathewson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _EVENT2_BUFFEREVENT_STRUCT_H_
#define _EVENT2_BUFFEREVENT_STRUCT_H_

/** @file event2/bufferevent_struct.h

  Data structures for bufferevents.  Using these structures may hurt forward
  compatibility with later versions of Libevent: be careful!

  @deprecated Use of bufferevent_struct.h is completely deprecated; these
    structures are only exposed for backward compatibility with programs
    written before Libevent 2.0 that used them.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <event2/event-config.h>
#ifdef _EVENT_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef _EVENT_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

/* For int types. */
#include <event2/util.h>
/* For struct event */
#include <event2/event_struct.h>

struct event_watermark {
	size_t low;
	size_t high;
};

/**
  Shared implementation of a bufferevent.

  This type is exposed only because it was exposed in previous versions,
  and some people's code may rely on manipulating it.  Otherwise, you
  should really not rely on the layout, size, or contents of this structure:
  it is fairly volatile, and WILL change in future versions of the code.
**/
struct bufferevent {
	/** Event base for which this bufferevent was created. */
	struct event_base *ev_base;
	/** bufferevent���Բ���socket socketpair filter�����ݲ�������ͬ�����ò�ͬ�Ĳ����ṹ�塣 */
	const struct bufferevent_ops *be_ops;

	/** ���¼� */
	struct event ev_read;
	/** д�¼� */
	struct event ev_write;

	/** �������� */
	struct evbuffer *input;

	/** д������ */
	struct evbuffer *output;

	struct event_watermark wm_read;  /*��ˮλ*/
	struct event_watermark wm_write;  /*дˮλ*/

	bufferevent_data_cb readcb;    /*���ص�*/
	bufferevent_data_cb writecb;   /*д�ص�*/
	bufferevent_event_cb errorcb;  /*����ص�*/
	void *cbarg;                   /*�ص�����*/ 

	struct timeval timeout_read;  /*����ʱ�¼�*/
	struct timeval timeout_write; /*д��ʱ�¼�*/

	/** �򿪵� EV_READ and EV_WRITE�¼� */
	short enabled;
};

#ifdef __cplusplus
}
#endif

#endif /* _EVENT2_BUFFEREVENT_STRUCT_H_ */
