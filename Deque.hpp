#ifndef DEQUE_HPP
#define DEQUE_HPP

#define Deque_DEFINE(t)															\
	struct Deque_##t 															\
	{																			\
		int capacity = 10;														\
		t *data;																\
		t &(*at)(Deque_##t *, int i);											\
		void (*dtor)(Deque_##t *);												\
		bool (*compFunc)(const t&, const t&);									\
		int (*size)(Deque_##t *);												\
		int s = 0;																\
		bool (*empty)(Deque_##t *);												\
		bool (*full)(Deque_##t *);												\
		char const type_name[sizeof("Deque_"#t)] = "Deque_"#t;					\
		int frontIndex = 0, backIndex = 0;										\
		void (*push_back)(Deque_##t *, t);										\
		void (*push_front)(Deque_##t *, t);										\
	};																			\
	t &Deque_##t##_at(Deque_##t *ap, int i)										\
	{																			\
		return ap->data[i];														\
	}																			\
	void Deque_##t##_dtor(Deque_##t *ap)										\
	{																			\
		free(ap);																\
	}																			\
	int Deque_##t##_size(Deque_##t *ap)											\
	{																			\
		return ap->s;															\
	}																			\
	bool Deque_##t##_empty(Deque_##t *ap)										\
	{																			\
		printf("size(): %d\n", ap->s);													\
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
		ap->at(ap, ap->backIndex) = item;										\
		ap->s++;																\
	}																			\
	void Deque_##t##_push_front(Deque_##t *ap, t item)							\
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
		ap->frontIndex = (ap->frontIndex + 1) % ap->capacity;					\
		ap->at(ap, ap->frontIndex) = item;										\
		ap->s++;																\
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
		ap->push_back = &Deque_##t##_push_back;											\
		ap->push_front = &Deque_##t##_push_front;										\
	}																					\

#endif