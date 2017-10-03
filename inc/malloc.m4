define(`lowcase', `translit(`$*', `A-Z', `a-z')')
define(m4_map, `
	void *head_save = ft_malloc.`'lowcase($1)_head;
	if (ft_malloc.`'lowcase($1)_head) {
		((struct s_chunk_head *)ft_malloc.`'lowcase($1)_head)->next = MMAP(CHUNK_SIZE);
		if (((struct s_chunk_head *)ft_malloc.`'lowcase($1)_head)->next == MAP_FAILED)
			return (0);
		ft_malloc.`'lowcase($1)_head = ((struct s_chunk_head *)ft_malloc.`'lowcase($1)_head)->next;
	}
	else {
		ft_malloc.`'lowcase($1)_head = MMAP(CHUNK_SIZE);
		ft_malloc.`'lowcase($1)_start = ft_malloc.`'lowcase($1)_head;
	}
	ft_malloc.`'lowcase($1)_tail = ft_malloc.`'lowcase($1)_head;
	*((struct s_chunk_head *)ft_malloc.`'lowcase($1)_head) = (struct s_chunk_head){
		 .binary_heap = 0b00000000000000000000000000000001,
		 .prev = head_save,
		 .next = NULL
	};
	ft_malloc.`'lowcase($1)_tail += $1;
	return (ft_malloc.`'lowcase($1)_tail);
')

define(m4_alloc, `{
	struct s_chunk_head * h;

	h = ft_malloc.`'lowcase($1)_start;
	while (h) {
		int $ = h->binary_heap;
		int i = 0;
		while (i < 32) {
			if (($ & 0b1) == 0)
				break;
			$ = $ >> 1;
			i += 1;
		}
		if (i != 32) {
			h->binary_heap |= 0b00000000000000000000000000000001 << i;
			return (h + i * $1 / 32);
		}

		h = h->next;
	}
	return map_`'lowcase($1)();
}')

define(m4_free_loop, `{
	struct s_chunk_head * h;

	h = ft_malloc.`'lowcase($1)_start;
	while (h) {
		if (p != NULL && p - (void*)h < CHUNK_SIZE && p - (void*)h > 0) {
			int i = (int)((p - (void*)h) / (float)(CHUNK_SIZE) * 32);
			h->binary_heap ^= 0b00000000000000000000000000000001 << (i + 1);
		}
		h = h->next;
	}
}')

define(m4_realloc_loop, `{
	struct s_chunk_head * h;

	h = ft_malloc.`'lowcase($1)_start;
	while (h) {
		if (p != NULL && p - (void*)h < CHUNK_SIZE && p - (void*)h > 0)
			size_ = $1;
		h = h->next;
	}
}')
