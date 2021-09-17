#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <algorithm>

#define Deque_DEFINE(t)															\
	struct Deque_##t;															\
	struct Deque_##t##_Iterator													\
	{																			\
		Deque_##t *ap;															\
		int counter = -1;														\
		void (*inc)(Deque_##t##_Iterator *);									\
		void (*dec)(Deque_##t##_Iterator *);									\
		t (*deref)(Deque_##t##_Iterator *);										\
	};																			\
	struct Deque_##t 															\
	{																			\
		int capacity = 10;														\
		t *data;																\
		t &(*at)(Deque_##t *, int i);											\
		void (*dtor)(Deque_##t *);												\
		bool (*compFunc)(const t&, const t&);									\
		size_t (*size)(Deque_##t *);											\
		int s = 0;																\
		bool (*empty)(Deque_##t *);												\
		bool (*full)(Deque_##t *);												\
		char const type_name[sizeof("Deque_"#t)] = "Deque_"#t;					\
		int frontIndex = -1, backIndex = -1;									\
		t (*front)(Deque_##t *);												\
		t (*back)(Deque_##t *);													\
		void (*push_front)(Deque_##t *, t);										\
		void (*push_back)(Deque_##t *, t);										\
		void (*pop_front)(Deque_##t *);											\
		void (*pop_back)(Deque_##t *);											\
		void (*clear)(Deque_##t *);												\
		void (*sort)(Deque_##t *, Deque_##t##_Iterator, Deque_##t##_Iterator);	\
																				\
		Deque_##t##_Iterator (*begin)(Deque_##t *);								\
		Deque_##t##_Iterator (*end)(Deque_##t *);								\
	};																			\
	t &Deque_##t##_at(Deque_##t *ap, int i)										\
	{																			\
		if(ap->frontIndex < ap->backIndex)										\
			i = -i;																\
		return ap->data[(i + ap->frontIndex + ap->capacity) % ap->capacity];	\
	}																			\
	size_t Deque_##t##_size(Deque_##t *ap)										\
	{																			\
		return ap->s;															\
	}																			\
	bool Deque_##t##_empty(Deque_##t *ap)										\
	{																			\
		if(ap->s == 0)															\
			return true;														\
		return false;															\
	}																			\
	bool Deque_##t##_full(Deque_##t *ap)										\
	{																			\
		if(ap->s == ap->capacity)												\
			return true;														\
		return false;															\
	}																			\
	t Deque_##t##_front(Deque_##t *ap)											\
	{																			\
		if(ap->empty(ap))														\
		{																		\
			printf("Empty deque\n");											\
			abort();															\
		}																		\
		return ap->at(ap, 0);													\
	}																			\
	t Deque_##t##_back(Deque_##t *ap)											\
	{																			\
		if(ap->empty(ap))														\
		{																		\
			printf("Empty deque\n");											\
			abort();															\
		}																		\
		return ap->at(ap, ap->s - 1);											\
	}																			\
	void Deque_##t##_push_front(Deque_##t *ap, t item)							\
	{																			\
		if(ap->empty(ap))														\
		{																		\
			ap->frontIndex = ap->backIndex = 0;									\
			ap->at(ap, 0) = item;												\
			ap->s++;															\
			return;																\
		}																		\
		else if(ap->full(ap))													\
		{																		\
			ap->capacity *= 2;													\
			t *tempData = (t *)realloc(ap->data, sizeof(t) * ap->capacity);		\
			ap->data = tempData;												\
		}																		\
		ap->frontIndex = (ap->frontIndex + 1) % ap->capacity;					\
		ap->s++;																\
		ap->at(ap, 0) = item;													\
	}																			\
	void Deque_##t##_push_back(Deque_##t *ap, t item)							\
	{																			\
		if(ap->empty(ap))														\
		{																		\
			ap->at(ap, 0) = item;												\
			ap->s++;															\
			return;																\
		}																		\
		else if(ap->full(ap))													\
		{																		\
			ap->capacity *= 2;													\
			t *tempData = (t *)realloc(ap->data, sizeof(t) * ap->capacity);		\
			ap->data = tempData;												\
		}																		\
		ap->backIndex = (ap->backIndex - 1 + ap->capacity) % ap->capacity;		\
		ap->s++;																\
		ap->at(ap, ap->s - 1) = item;											\
	}																			\
	void Deque_##t##_pop_front(Deque_##t *ap)									\
	{																			\
		if(ap->empty(ap))														\
		{																		\
			printf("Empty deque\n");											\
			abort();															\
		}																		\
		else if(ap->size(ap) == 1)												\
		{																		\
			ap->frontIndex = ap->backIndex = -1;								\
			ap->s--;															\
		}																		\
		else																	\
		{																		\
			ap->frontIndex = (ap->frontIndex - 1 + ap->capacity) % ap->capacity;\
			ap->s--;															\
		}																		\
	}																			\
	void Deque_##t##_pop_back(Deque_##t *ap)									\
	{																			\
		if(ap->empty(ap))														\
		{																		\
			printf("Empty deque\n");											\
			abort();															\
		}																		\
		else if(ap->size(ap) == 1)												\
		{																		\
			ap->frontIndex = ap->backIndex = -1;								\
			ap->s--;															\
		}																		\
		else																	\
		{																		\
			ap->backIndex = (ap->backIndex + 1) % ap->capacity;					\
			ap->s--;															\
		}																		\
	}																			\
	void Deque_##t##_clear(Deque_##t *ap)										\
	{																			\
		ap->s = 0;																\
		ap->capacity = 10;														\
		ap->frontIndex = ap->backIndex = -1;									\
	}																			\
	void Deque_##t##_dtor(Deque_##t *ap)										\
	{																			\
		free(ap->data);															\
	}																			\
	void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *itp)					\
	{																			\
		if(itp->counter >= 0)													\
			itp->counter++;														\
	}																			\
	void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *itp)					\
	{																			\
		if(itp->counter <= itp->ap->s)											\
			itp->counter--;														\
	}																			\
	t Deque_##t##_Iterator_deref(Deque_##t##_Iterator *itp)						\
	{																			\
		if(itp->counter >= itp->ap->s)											\
		{																		\
			printf("Attempt to deref invalid index\n");							\
			abort();															\
		}																		\
		else																	\
			return itp->ap->at(itp->ap, itp->counter);							\
	}																			\
	Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *ap)						\
	{																			\
		Deque_##t##_Iterator it;												\
		it.ap = ap;																\
		it.counter = 0;															\
		it.inc = &Deque_##t##_Iterator_inc;										\
		it.dec = &Deque_##t##_Iterator_dec;										\
		it.deref = &Deque_##t##_Iterator_deref;									\
		return it;																\
	}																			\
	Deque_##t##_Iterator Deque_##t##_end(Deque_##t *ap)							\
	{																			\
		Deque_##t##_Iterator it;												\
		it.ap = ap;																\
		it.counter = ap->s;														\
		return it;																\
	}																			\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator first, Deque_##t##_Iterator second)	\
	{																			\
		if(first.counter == second.counter)										\
			return true;														\
		return false;															\
	}																			\
	void Deque_##t##_sort(Deque_##t *ap, Deque_##t##_Iterator start, Deque_##t##_Iterator finish)					\
	{																												\
		start.inc(&start);																							\
		for(auto it = start; !Deque_##t##_Iterator_equal(it, finish); it.inc(&it))									\
		{																											\
			Deque_##t##_Iterator itMinusOne = it;																	\
			itMinusOne.dec(&itMinusOne);																			\
			if(ap->compFunc(itMinusOne.deref(&itMinusOne), it.deref(&it)) == false)									\
			{																										\
				std::swap(itMinusOne.ap->at(itMinusOne.ap, itMinusOne.counter) , it.ap->at(it.ap, it.counter));		\
			}																										\
		}																											\
	}																												\
	bool Deque_##t##_equal(Deque_##t one, Deque_##t two)						\
	{																			\
		for(auto itOne = one.begin(&one), itTwo = two.begin(&two);				\
			!Deque_##t##_Iterator_equal(itOne, one.end(&one)) && !Deque_##t##_Iterator_equal(itTwo, two.end(&two));	\
			itOne.inc(&itOne), itTwo.inc(&itTwo))								\
		{																		\
			if(itOne.deref(&itOne) != itTwo.deref(&itTwo))						\
				return false;													\
		}																		\
		return (one.capacity == two.capacity) && (one.s == two.s) &&			\
				(strcmp(one.type_name, two.type_name) == 0);					\
	}																			\
	void Deque_##t##_ctor(Deque_##t *ap, bool (*compFunc)(const t &o1, const t &o2))	\
	{																					\
		ap->data = (t *)malloc(sizeof(t) * ap->capacity);								\
		ap->at = &Deque_##t##_at;														\
		ap->dtor = &Deque_##t##_dtor;													\
		ap->compFunc = compFunc;														\
		ap->size = &Deque_##t##_size;													\
		ap->empty = &Deque_##t##_empty;													\
		ap->full = &Deque_##t##_full;													\
		ap->front = &Deque_##t##_front;													\
		ap->back = &Deque_##t##_back;													\
		ap->push_front = &Deque_##t##_push_front;										\
		ap->push_back = &Deque_##t##_push_back;											\
		ap->pop_front = &Deque_##t##_pop_front;											\
		ap->pop_back = &Deque_##t##_pop_back;											\
		ap->begin = &Deque_##t##_begin;													\
		ap->end = &Deque_##t##_end;														\
		ap->clear = &Deque_##t##_clear;													\
		ap->sort = &Deque_##t##_sort;													\
	}																					\

#endif