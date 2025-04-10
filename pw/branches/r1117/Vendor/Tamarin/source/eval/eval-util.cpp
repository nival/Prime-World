/* -*- tab-width: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "avmplus.h"

#ifdef VMCFG_EVAL

#include "eval.h"

namespace avmplus
{
	namespace RTC
	{
		Allocator::Allocator(Compiler* compiler)
			: compiler(compiler)
			, free_sbchunks(NULL)
			, current_chunk(NULL)
			, current_top(NULL)
			, current_limit(NULL)
		{
			AvmAssert(offsetof(Chunk, data) % 8 == 0);
			// Do not refill yet; the first allocation is likely to be the hashtable
			// and that's sometimes large, so the first segment would sometimes
			// simply be lost.
		}
		
		Allocator::~Allocator()
		{
			while (current_chunk != NULL)
			{
				Chunk* tmp = current_chunk;
				current_chunk = current_chunk->prev;
				delete [] tmp;
			}
		}

		void Allocator::refill(size_t nbytes)
		{
			union {
				uint8_t* c_8;
				Chunk* c;
			};
			c_8 = new uint8_t[sizeof(Chunk) + nbytes - 1];
			c->prev = current_chunk;
			current_chunk = c;
			current_top = c->data;
			current_limit = c->data + nbytes;
		}
		
		void* Allocator::allocSlow(size_t nbytes)
		{
			AvmAssert(nbytes % 8 == 0);
			if (current_top + nbytes > current_limit)
				refill(nbytes);
			AvmAssert(current_top + nbytes <= current_limit);
			void *p = current_top;
			current_top += nbytes;
			return p;
		}
		
		template<class T> void SeqBuilder<T>::addAtEnd(T item)
		{
			Seq<T>* e = ALLOC(Seq<T>, (item));
			if (last == NULL)
				items = e;
			else
				last->tl = e;
			last = e;
		}
		
		// At least Xcode requires explicit instantiation.
		
		template class SeqBuilder<double>;
		template class SeqBuilder<int32_t>;
		template class SeqBuilder<uint32_t>;

		template class SeqBuilder<ABCClassInfo*>;
		template class SeqBuilder<ABCExceptionInfo*>;
		template class SeqBuilder<ABCInstanceInfo*>;
		template class SeqBuilder<ABCMetadataInfo*>;
		template class SeqBuilder<ABCMethodInfo*>;
		template class SeqBuilder<ABCMethodBodyInfo*>;
		template class SeqBuilder<ABCMultinameInfo*>;
		template class SeqBuilder<ABCNamespaceInfo*>;
		template class SeqBuilder<ABCNamespaceSetInfo*>;
		template class SeqBuilder<ABCScriptInfo*>;
		template class SeqBuilder<ABCTrait*>;
		template class SeqBuilder<Binding*>;
		template class SeqBuilder<CaseClause*>;
		template class SeqBuilder<CatchClause*>;
		template class SeqBuilder<Expr*>;
		template class SeqBuilder<FunctionDefn*>;
		template class SeqBuilder<FunctionParam*>;
		template class SeqBuilder<Label*>;
		template class SeqBuilder<LiteralField*>;
		template class SeqBuilder<NamespaceDefn*>;
		template class SeqBuilder<Stmt*>;
		template class SeqBuilder<Str*>;

		StringBuilder::StringBuilder(Compiler* compiler)
			: allocator(compiler->allocator)
			, chunk(NULL)
		{
			clear();
		}

		StringBuilder::~StringBuilder()
		{
			while (chunk != NULL)
				popChunk();
		}

		void StringBuilder::clear()
		{
			len = 0;
			nextchar = 0;
			if (chunk == NULL)
				pushChunk();
			while (chunk->next != NULL)
				popChunk();
		}

		void StringBuilder::append(StringBuilder* other)
		{
			append(other->chunk->next);
			append(other->chunk->data, other->chunk->data + other->nextchar);
		}
		
		void StringBuilder::append(Str* other)
		{
			append(other->s, other->s + other->length);
		}

		void StringBuilder::append(const char* other)
		{
			while (*other != 0)
				append(*other++);
		}

		inline uint32_t min(uint32_t a, uint32_t b) { return a < b ? a : b; }

		void StringBuilder::append(const wchar* ptr, const wchar* lim)
		{
			if (lim == NULL) {
				lim = ptr;
				while (*lim != 0)
					lim++;
			}
			while (ptr < lim) {
				uint32_t avail = SBChunk::chunksize - nextchar;
				uint32_t need = uint32_t(lim - ptr);
				uint32_t k = min(need, avail);
				memcpy(chunk->data + nextchar, ptr, k*sizeof(wchar));
				ptr += k;
				nextchar += k;
				len += k;
				if (ptr < lim) {
					pushChunk();
					nextchar = 0;
				}
			}
		}
		
		void StringBuilder::append(int c)
		{
			wchar c2 = (wchar)c;
			append(&c2, (&c2) + 1);
		}
		
		Str* StringBuilder::str()
		{
			if (chunk->next == NULL) 
				return allocator->compiler->intern(chunk->data, len);

			wchar* buf = new wchar[len];
			wchar* p = copyInto(buf, chunk->next);
			memcpy(p, chunk->data, nextchar*sizeof(wchar));
			Str* result = allocator->compiler->intern(buf, len);
			delete [] buf;
			return result;
		}

		char* StringBuilder::chardata()
		{
			char *buf = (char*)allocator->alloc(len+1);
			char *p = copyInto(buf, chunk->next);
			for ( uint32_t i=0 ; i < nextchar ; i++ )
				p[i] = (char)(chunk->data[i] & 127);
			p += nextchar;
			*p = 0;
			return buf;
		}
		
		void StringBuilder::append(SBChunk* other)
		{
			if (other != NULL) {
				append(other->next);
				append(other->data, other->data + SBChunk::chunksize);
			}
		}
		
		wchar* StringBuilder::copyInto(wchar* buf, SBChunk* c)
		{
			if (c == NULL)
				return buf;

			wchar *p = buf;
			if (c->next != NULL)
				p = copyInto(buf, c->next);
			memcpy(p, c->data, SBChunk::chunksize*sizeof(wchar));
			return p+SBChunk::chunksize;
		}
		
		char* StringBuilder::copyInto(char* buf, SBChunk* c)
		{
			if (c == NULL)
				return buf;
			
			char *p = buf;
			if (c->next != NULL)
				p = copyInto(buf, c->next);
			for ( int i=0 ; i < SBChunk::chunksize ; i++ )
				p[i] = (char)(chunk->data[i] & 127);
			return p+SBChunk::chunksize;
		}
		
		void StringBuilder::pushChunk()
		{
			SBChunk* c;
			if (allocator->free_sbchunks != NULL) {
				c = allocator->free_sbchunks;
				allocator->free_sbchunks = allocator->free_sbchunks->next;
			}
			else
				c = ALLOC(SBChunk, ());
			c->next = chunk;
			chunk = c;
		}
		
		void StringBuilder::popChunk()
		{
			SBChunk* c = chunk;
			chunk = chunk->next;
			c->next = allocator->free_sbchunks;
			allocator->free_sbchunks = c;
		}
		
#ifdef DEBUG
		
		char* getn(char* buf, const Str* s, size_t limit)
		{
			int chars = int(s->length < limit-1 ? s->length : limit-1);
			const wchar* p;
			char* q;
			for ( p=s->s, q=buf ; chars >= 0 ; chars-- )
				*q++ = (char)*p++;
			*q = 0;
			return buf;
		}
		
#endif

		uint32_t hashString(const wchar* chars, uint32_t nchars)
		{
			// See http://www.cse.yorku.ca/~oz/hash.html; this is the djb2 algorithm
			uint32_t h = 5381;
			for ( uint32_t i=0 ; i < nchars ; i++ )
				h = ((h << 5) + h) + chars[i];
			return h;
		}
		
		uint32_t lenU30(uint32_t val)
		{
			if( val < 0x80 )
				return 1;
			if ( val < 0x4000 )
				return 2;
			if ( val < 0x200000 )
				return 3;
			if ( val < 0x10000000 )
				return 4;
			return 5;
		}
		
		uint8_t* emitU32(uint8_t* out, uint32_t val)
		{
			if( val < 0x80 ) {
				*out++ = val & 0x7F;
			}
			else if ( val < 0x4000 ) {
				*out++ = (val & 0x7F) | 0x80;
				*out++ = (val >> 7) & 0x7F;
			}
			else if ( val < 0x200000 ) {
				*out++ = (val & 0x7F) | 0x80;
				*out++ = ((val >> 7) & 0x7F) | 0x80;
				*out++ = (val >> 14) & 0x7F;
			}
			else if ( val < 0x10000000 ) {
				*out++ = (val & 0x7F) | 0x80;
				*out++ = ((val >> 7) & 0x7F) | 0x80;
				*out++ = ((val >> 14) & 0x7F) | 0x80;
				*out++ = (val >> 21) & 0x7F;
			}
			else {
				*out++ = (val & 0x7F) | 0x80;
				*out++ = ((val >> 7) & 0x7F) | 0x80;
				*out++ = ((val >> 14) & 0x7F) | 0x80;
				*out++ = ((val >> 21) & 0x7F) | 0x80;
				*out++ = (val >> 28) & 0x7F;
			}
			return out;
		}
		
		uint8_t* emitDouble(uint8_t* out, double d)
		{
			union {
				uint8_t b[8];
				double d;
			} v;
			v.d = d;
#ifdef AVMPLUS_BIG_ENDIAN
			for ( int i=0 ; i < 8 ; i++ )
				out[i] = v.b[7-i];
#else
			for ( int i=0 ; i < 8 ; i++ )
				out[i] = v.b[i];
#endif
			return out + 8;
		}
		
		uint8_t* emitS24(uint8_t* out, int32_t s)
		{
			*out++ = (s & 255);
			*out++ = (s >> 8) & 255;
			*out++ = (s >> 16) & 255;
			return out;
		}
		
		uint32_t utf8length(Str* str) 
		{
			uint32_t len = 0;

			for ( wchar *s=str->s, *l=str->s + str->length ; s < l ; s++ ) {
				if (*s <= 0x7F)
					len += 1;
				else if (*s <= 0x7FF)
					len += 2;
				else
					len += 3;
			}
			return len;
		}
		
		// duplicates formatUtf8 below???
		uint8_t* emitUtf8(uint8_t* out, Str* str)
		{
			for ( wchar *s=str->s, *l=str->s + str->length ; s < l ; s++ ) {
				wchar c = *s;
				if (c <= 0x7F)
					*out++ = (uint8_t)c;
				else if (c <= 0x7FF) {
					*out++ = 0xC0 | ((c >> 6) & 0x1F);
					*out++ = 0x80 | (c & 0x3F);
				}
				else {
					*out++ = 0xE0 | ((c >> 12) & 0x0F);
					*out++ = 0x80 | ((c >> 6) & 0x3F);
					*out++ = 0x80 | (c & 0x3F);
				}
			}
			return out;
		}
		
		ByteBuffer::ByteBuffer(Allocator* allocator, uint32_t increment)
			: allocator(allocator)
			, increment(increment)
			, out(NULL)
			, limit(NULL)
			, first(NULL)
			, last(NULL)
			, size_rest(0)
		{
		}

		void ByteBuffer::makeRoomSlow(uint32_t nbytes)
		{
			if (last != NULL) {
				size_rest = size();
				last->end = out;
			}
			uint32_t k = nbytes > increment ? nbytes : increment;
			Chunk* c = (Chunk*)allocator->alloc(sizeof(Chunk) + k - 1);
			c->next = NULL;
			out = c->start;
			limit = c->start + k;
			AvmAssert( (uint32_t)(limit - out) >= nbytes );
			if (last != NULL)
				last->next = c;
			else
				first = c;
			last = c;
		}
		
		void ByteBuffer::serialize(uint8_t* b) const
		{
			if (last != NULL) {
				last->end = out;
				for ( Chunk* c = first ; c != NULL ; c = c->next ) {
					memcpy( b, c->start, c->end - c->start );
					b += c->end - c->start;
				}
			}
		}
		
		void formatUtf8(char *buf, size_t bufsiz, const wchar* s)
		{
			AvmAssert(bufsiz > 0);
			char *limit = buf + bufsiz;
			wchar c;
			while ((c = *s++) != 0)
			{
				if (c < 0x80) {
					if (buf+1 >= limit)
						break;
					*buf++ = (char)c;
				}
				else if (c < 0x800) {
					if (buf+2 >= limit)
						break;
					*buf++ = 0xC0 | ((c >> 6) & 31);
					*buf++ = 0x80 | (c & 63);
				}
				else if (c >= 0xD800 && c <= 0xDBFF) {
					wchar d = *s++;
					if (d >= 0xDC00 && d <= 0xDCFF) {
						// surrogate pair
						if (buf+4 >= limit)
							break;
						wchar u = ((c >> 6) & 15) + 1;
						*buf++ = (char)(0xF0 | (u >> 2));
						*buf++ = 0x80 | ((u & 3) << 4) | ((c >> 2) & 15);
						*buf++ = 0x80 | ((c & 3) << 4) | ((d >> 6) & 15);
						*buf++ = 0x80 | (d & 63);
					}
					else {
						// error, really
						if (buf+1 >= limit)
							break;
						*buf++ = '?';
						s--;
					}
				}
				else if (c >= 0xDC00 && c <= 0xDCFF) {
					// error, really
					if (buf+1 >= limit)
						break;
					*buf++ = '?';
				}
				else {
					if (buf+3 >= limit)
						break;
					*buf++ = 0xE0 | ((c >> 12) & 15);
					*buf++ = 0x80 | ((c >> 6) & 63);
					*buf++ = 0x80 | (c & 63);
				}
			}
			AvmAssert(buf < limit);
			*buf = 0;
		}
	}
}

#endif // VMCFG_EVAL
