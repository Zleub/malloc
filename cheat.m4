define(`upcase', `translit(`$*', `a-z', `A-Z')')
define(m4_map, `
	void *map_$1() {
		void * head_save = ft_malloc.$1_head;
		if (ft_malloc.$1_head) {
			((struct s_chunk_head *)ft_malloc.$1_head)->next = MMAP(INIT_SIZE);
			ft_malloc.$1_head = ((struct s_chunk_head *)ft_malloc.$1_head)->next;
		}
		else {
			ft_malloc.$1_head = MMAP(INIT_SIZE);
			ft_malloc.$1_start = ft_malloc.$1_head;
		}
		ft_malloc.$1_tail = ft_malloc.$1_head;
		*((struct s_chunk_head *)ft_malloc.$1_head) = (struct s_chunk_head){
			 .binary_heap = 0b00000000000000000000000000000001,
			 .prev = head_save,
			 .next = NULL
		};
		ft_malloc.$1_tail += upcase($1);
		return (ft_malloc.$1_tail);
	}
')

define(m4_alloc, `
	struct s_chunk_head * h;

	h = ft_malloc.$1_start;
	while (h) {
		int bail = h->binary_heap;
		int i = 0;
		while (i < 32) {
			if ((bail & 0b1) == 0)
				break;
			bail = bail >> 1;
			i += 1;
		}
		if (i != 32) {
			h->binary_heap |= 0b00000000000000000000000000000001 << i;
			return (h + i * upcase($1) / 32);
		}

		h = h->next;
	}
	return map_$1();
')

define(m4_free_loop, `{
	struct s_chunk_head * h;

	h = ft_malloc.$1_start;
	while (h) {
		if (p != NULL && p - (void*)h < INIT_SIZE && p - (void*)h > 0) {
			int i = (int)((p - (void*)h) / (float)(INIT_SIZE) * 32);
			h->binary_heap ^= 0b00000000000000000000000000000001 << (i + 1);
		}
		h = h->next;
	}
}')

define(m4_realloc_loop, `{
	struct s_chunk_head * h;

	h = ft_malloc.$1_start;
	while (h) {
		if (p != NULL && p - (void*)h < INIT_SIZE && p - (void*)h > 0)
			_size = upcase($1);
		h = h->next;
	}
}')
