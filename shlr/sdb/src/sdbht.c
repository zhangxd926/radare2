#include "sdbht.h"

SdbHash* sdb_ht_new() {
	return ht_new ((DupValue)strdup, (HtKvFreeFunc)sdb_kv_free, (CalcSize)strlen);
}

static bool sdb_ht_internal_insert(SdbHash* ht, const char* key,
				    const char* value, bool update) {
	if (!ht || !key || !value) {
		return false;
	}
	SdbKv* kvp = calloc (1, sizeof (SdbKv));
	if (kvp) {
		kvp->key = strdup ((void *)key);
		kvp->value = strdup ((void *)value);
		kvp->key_len = strlen ((void *)kvp->key);
		kvp->expire = 0;
		kvp->value_len = strlen ((void *)kvp->value);
		return ht_insert_kv (ht, (HtKv*)kvp, update);
	}
	return false;
}
bool sdb_ht_insert(SdbHash* ht, const char* key, const char* value) {
	return sdb_ht_internal_insert (ht, key, value, false);
}

bool sdb_ht_insert_kvp(SdbHash* ht, SdbKv *kvp, bool update) {
	return ht_insert_kv (ht, (HtKv*)kvp, update);
}

bool sdb_ht_update(SdbHash *ht, const char *key, const char*value) {
	return sdb_ht_internal_insert (ht, key, value, true);
}

SdbKv* sdb_ht_find_kvp(SdbHash* ht, const char* key, bool* found) {
	return (SdbKv *)ht_find_kv (ht, key, found);
}

char* sdb_ht_find(SdbHash* ht, const char* key, bool* found) {
	return (char *)ht_find (ht, key, found);
}

void sdb_ht_free(SdbHash *ht) {
	ht_free (ht);
}

bool sdb_ht_delete(SdbHash* ht, const char *key) {
	return ht_delete (ht, key);
}

void sdb_ht_free_deleted(SdbHash* ht) {
	ht_free_deleted (ht);
}
